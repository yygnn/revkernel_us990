
/*
 *  linux/mm/page_io.c
 *
 *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds
 *
 *  Swap reorganised 29.12.95, 
 *  Asynchronous swapping added 30.12.95. Stephen Tweedie
 *  Removed race in async swapping. 14.4.1996. Bruno Haible
 *  Add swap of shared pages through the page cache. 20.2.1998. Stephen Tweedie
 *  Always use brw_page, life becomes simpler. 12 May 1998 Eric Biederman
 */

#include <linux/mm.h>
#include <linux/kernel_stat.h>
#include <linux/gfp.h>
#include <linux/pagemap.h>
#include <linux/swap.h>
#include <linux/bio.h>
#include <linux/swapops.h>
#include <linux/writeback.h>
#include <linux/blkdev.h>
#include <linux/ratelimit.h>
#include <asm/pgtable.h>

/*
                                                                         
                               
 */
#define SWAP_ERROR_LOG_RATE_MS 1000

static struct bio *get_swap_bio(gfp_t gfp_flags,
				struct page *page, bio_end_io_t end_io)
{
	struct bio *bio;

	bio = bio_alloc(gfp_flags, 1);
	if (bio) {
		bio->bi_sector = map_swap_page(page, &bio->bi_bdev);
		bio->bi_sector <<= PAGE_SHIFT - 9;
		bio->bi_io_vec[0].bv_page = page;
		bio->bi_io_vec[0].bv_len = PAGE_SIZE;
		bio->bi_io_vec[0].bv_offset = 0;
		bio->bi_vcnt = 1;
		bio->bi_idx = 0;
		bio->bi_size = PAGE_SIZE;
		bio->bi_end_io = end_io;
	}
	return bio;
}

static void end_swap_bio_write(struct bio *bio, int err)
{
	const int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct page *page = bio->bi_io_vec[0].bv_page;
	static unsigned long swap_error_rs_time;

	if (!uptodate) {
		SetPageError(page);
		/*
                                                   
                                                            
                                                           
                  
    
                                                             
   */
		set_page_dirty(page);
		if (printk_timed_ratelimit(&swap_error_rs_time,
					   SWAP_ERROR_LOG_RATE_MS))
			printk(KERN_ALERT "Write-error on swap-device (%u:%u:%Lu)\n",
				imajor(bio->bi_bdev->bd_inode),
				iminor(bio->bi_bdev->bd_inode),
				(unsigned long long)bio->bi_sector);
		ClearPageReclaim(page);
	}
	end_page_writeback(page);
	bio_put(bio);
}

void end_swap_bio_read(struct bio *bio, int err)
{
	const int uptodate = test_bit(BIO_UPTODATE, &bio->bi_flags);
	struct page *page = bio->bi_io_vec[0].bv_page;

	if (!uptodate) {
		SetPageError(page);
		ClearPageUptodate(page);
		printk(KERN_ALERT "Read-error on swap-device (%u:%u:%Lu)\n",
				imajor(bio->bi_bdev->bd_inode),
				iminor(bio->bi_bdev->bd_inode),
				(unsigned long long)bio->bi_sector);
		goto out;
	}

	SetPageUptodate(page);

	/*
                                                                       
                                                                   
                                                                         
                      
  */
	if (likely(PageSwapCache(page))) {
		struct swap_info_struct *sis;

		sis = page_swap_info(page);
		if (sis->flags & SWP_BLKDEV) {
			/*
                                                         
                                                        
                                                      
                      
                                                       
                                                      
                                              
                                                     
                                                        
                                                    
                                                         
                                                      
                                                          
                                  
    */
			struct gendisk *disk = sis->bdev->bd_disk;
			if (disk->fops->swap_slot_free_notify) {
				swp_entry_t entry;
				unsigned long offset;

				entry.val = page_private(page);
				offset = swp_offset(entry);

				SetPageDirty(page);
				disk->fops->swap_slot_free_notify(sis->bdev,
						offset);
			}
		}
	}

out:
	unlock_page(page);
	bio_put(bio);
}

/*
                                                       
                                                        
 */
int swap_writepage(struct page *page, struct writeback_control *wbc)
{
	struct bio *bio;
	int ret = 0, rw = WRITE;

	if (try_to_free_swap(page)) {
		unlock_page(page);
		goto out;
	}
	bio = get_swap_bio(GFP_NOIO, page, end_swap_bio_write);
	if (bio == NULL) {
		set_page_dirty(page);
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	if (wbc->sync_mode == WB_SYNC_ALL)
		rw |= REQ_SYNC;
	count_vm_event(PSWPOUT);
	set_page_writeback(page);
	unlock_page(page);
	submit_bio(rw, bio);
out:
	return ret;
}

int swap_readpage(struct page *page)
{
	struct bio *bio;
	int ret = 0;

	VM_BUG_ON(!PageLocked(page));
	VM_BUG_ON(PageUptodate(page));
	bio = get_swap_bio(GFP_KERNEL, page, end_swap_bio_read);
	if (bio == NULL) {
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	count_vm_event(PSWPIN);
	submit_bio(READ, bio);
out:
	return ret;
}