/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License version 2.
 */

#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/completion.h>
#include <linux/buffer_head.h>
#include <linux/pagemap.h>
#include <linux/pagevec.h>
#include <linux/mpage.h>
#include <linux/fs.h>
#include <linux/writeback.h>
#include <linux/swap.h>
#include <linux/gfs2_ondisk.h>
#include <linux/backing-dev.h>

#include "gfs2.h"
#include "incore.h"
#include "bmap.h"
#include "glock.h"
#include "inode.h"
#include "log.h"
#include "meta_io.h"
#include "quota.h"
#include "trans.h"
#include "rgrp.h"
#include "super.h"
#include "util.h"
#include "glops.h"


void gfs2_page_add_databufs(struct gfs2_inode *ip, struct page *page,
			    unsigned int from, unsigned int to)
{
	struct buffer_head *head = page_buffers(page);
	unsigned int bsize = head->b_size;
	struct buffer_head *bh;
	unsigned int start, end;

	for (bh = head, start = 0; bh != head || !start;
	     bh = bh->b_this_page, start = end) {
		end = start + bsize;
		if (end <= from || start >= to)
			continue;
		if (gfs2_is_jdata(ip))
			set_buffer_uptodate(bh);
		gfs2_trans_add_bh(ip->i_gl, bh, 0);
	}
}

/* 
                                                                             
                    
                                       
                                                      
                                                    
  
                 
 */

static int gfs2_get_block_noalloc(struct inode *inode, sector_t lblock,
				  struct buffer_head *bh_result, int create)
{
	int error;

	error = gfs2_block_map(inode, lblock, bh_result, 0);
	if (error)
		return error;
	if (!buffer_mapped(bh_result))
		return -EIO;
	return 0;
}

static int gfs2_get_block_direct(struct inode *inode, sector_t lblock,
				 struct buffer_head *bh_result, int create)
{
	return gfs2_block_map(inode, lblock, bh_result, 0);
}

/* 
                                                   
                                
                              
  
                                                                              
 */

static int gfs2_writepage_common(struct page *page,
				 struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	loff_t i_size = i_size_read(inode);
	pgoff_t end_index = i_size >> PAGE_CACHE_SHIFT;
	unsigned offset;

	if (gfs2_assert_withdraw(sdp, gfs2_glock_is_held_excl(ip->i_gl)))
		goto out;
	if (current->journal_info)
		goto redirty;
	/*                                                          */
	offset = i_size & (PAGE_CACHE_SIZE-1);
	if (page->index > end_index || (page->index == end_index && !offset)) {
		page->mapping->a_ops->invalidatepage(page, 0);
		goto out;
	}
	return 1;
redirty:
	redirty_page_for_writepage(wbc, page);
out:
	unlock_page(page);
	return 0;
}

/* 
                                                               
                  
                              
  
 */

static int gfs2_writeback_writepage(struct page *page,
				    struct writeback_control *wbc)
{
	int ret;

	ret = gfs2_writepage_common(page, wbc);
	if (ret <= 0)
		return ret;

	return nobh_writepage(page, gfs2_get_block_noalloc, wbc);
}

/* 
                                                             
                           
                              
  
 */

static int gfs2_ordered_writepage(struct page *page,
				  struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	int ret;

	ret = gfs2_writepage_common(page, wbc);
	if (ret <= 0)
		return ret;

	if (!page_has_buffers(page)) {
		create_empty_buffers(page, inode->i_sb->s_blocksize,
				     (1 << BH_Dirty)|(1 << BH_Uptodate));
	}
	gfs2_page_add_databufs(ip, page, 0, inode->i_sb->s_blocksize-1);
	return block_write_full_page(page, gfs2_get_block_noalloc, wbc);
}

/* 
                                                       
                           
                              
  
                                                                     
                                                                     
                                                               
                                              
 */

static int __gfs2_jdata_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);

	if (PageChecked(page)) {
		ClearPageChecked(page);
		if (!page_has_buffers(page)) {
			create_empty_buffers(page, inode->i_sb->s_blocksize,
					     (1 << BH_Dirty)|(1 << BH_Uptodate));
		}
		gfs2_page_add_databufs(ip, page, 0, sdp->sd_vfs->s_blocksize-1);
	}
	return block_write_full_page(page, gfs2_get_block_noalloc, wbc);
}

/* 
                                             
                       
  
                 
  
 */

static int gfs2_jdata_writepage(struct page *page, struct writeback_control *wbc)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	int ret;
	int done_trans = 0;

	if (PageChecked(page)) {
		if (wbc->sync_mode != WB_SYNC_ALL)
			goto out_ignore;
		ret = gfs2_trans_begin(sdp, RES_DINODE + 1, 0);
		if (ret)
			goto out_ignore;
		done_trans = 1;
	}
	ret = gfs2_writepage_common(page, wbc);
	if (ret > 0)
		ret = __gfs2_jdata_writepage(page, wbc);
	if (done_trans)
		gfs2_trans_end(sdp);
	return ret;

out_ignore:
	redirty_page_for_writepage(wbc, page);
	unlock_page(page);
	return 0;
}

/* 
                                                                        
                                 
                           
  
                                                                 
                                                                  
                                                                          
 */
static int gfs2_writeback_writepages(struct address_space *mapping,
				     struct writeback_control *wbc)
{
	return mpage_writepages(mapping, wbc, gfs2_get_block_noalloc);
}

/* 
                                                                   
                        
                              
                                                           
                             
                                          
  
                                                             
 */

static int gfs2_write_jdata_pagevec(struct address_space *mapping,
				    struct writeback_control *wbc,
				    struct pagevec *pvec,
				    int nr_pages, pgoff_t end)
{
	struct inode *inode = mapping->host;
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	loff_t i_size = i_size_read(inode);
	pgoff_t end_index = i_size >> PAGE_CACHE_SHIFT;
	unsigned offset = i_size & (PAGE_CACHE_SIZE-1);
	unsigned nrblocks = nr_pages * (PAGE_CACHE_SIZE/inode->i_sb->s_blocksize);
	int i;
	int ret;

	ret = gfs2_trans_begin(sdp, nrblocks, nrblocks);
	if (ret < 0)
		return ret;

	for(i = 0; i < nr_pages; i++) {
		struct page *page = pvec->pages[i];

		lock_page(page);

		if (unlikely(page->mapping != mapping)) {
			unlock_page(page);
			continue;
		}

		if (!wbc->range_cyclic && page->index > end) {
			ret = 1;
			unlock_page(page);
			continue;
		}

		if (wbc->sync_mode != WB_SYNC_NONE)
			wait_on_page_writeback(page);

		if (PageWriteback(page) ||
		    !clear_page_dirty_for_io(page)) {
			unlock_page(page);
			continue;
		}

		/*                                                          */
		if (page->index > end_index || (page->index == end_index && !offset)) {
			page->mapping->a_ops->invalidatepage(page, 0);
			unlock_page(page);
			continue;
		}

		ret = __gfs2_jdata_writepage(page, wbc);

		if (ret || (--(wbc->nr_to_write) <= 0))
			ret = 1;
	}
	gfs2_trans_end(sdp);
	return ret;
}

/* 
                                                                
                                 
                              
                                             
                                       
  
                                                                  
                                                               
                             
 */

static int gfs2_write_cache_jdata(struct address_space *mapping,
				  struct writeback_control *wbc)
{
	int ret = 0;
	int done = 0;
	struct pagevec pvec;
	int nr_pages;
	pgoff_t index;
	pgoff_t end;
	int scanned = 0;
	int range_whole = 0;

	pagevec_init(&pvec, 0);
	if (wbc->range_cyclic) {
		index = mapping->writeback_index; /*                        */
		end = -1;
	} else {
		index = wbc->range_start >> PAGE_CACHE_SHIFT;
		end = wbc->range_end >> PAGE_CACHE_SHIFT;
		if (wbc->range_start == 0 && wbc->range_end == LLONG_MAX)
			range_whole = 1;
		scanned = 1;
	}

retry:
	 while (!done && (index <= end) &&
		(nr_pages = pagevec_lookup_tag(&pvec, mapping, &index,
					       PAGECACHE_TAG_DIRTY,
					       min(end - index, (pgoff_t)PAGEVEC_SIZE-1) + 1))) {
		scanned = 1;
		ret = gfs2_write_jdata_pagevec(mapping, wbc, &pvec, nr_pages, end);
		if (ret)
			done = 1;
		if (ret > 0)
			ret = 0;

		pagevec_release(&pvec);
		cond_resched();
	}

	if (!scanned && !done) {
		/*
                                                                 
                                  
   */
		scanned = 1;
		index = 0;
		goto retry;
	}

	if (wbc->range_cyclic || (range_whole && wbc->nr_to_write > 0))
		mapping->writeback_index = index;
	return ret;
}


/* 
                                                                    
                                 
                              
   
 */

static int gfs2_jdata_writepages(struct address_space *mapping,
				 struct writeback_control *wbc)
{
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_sbd *sdp = GFS2_SB(mapping->host);
	int ret;

	ret = gfs2_write_cache_jdata(mapping, wbc);
	if (ret == 0 && wbc->sync_mode == WB_SYNC_ALL) {
		gfs2_log_flush(sdp, ip->i_gl);
		ret = gfs2_write_cache_jdata(mapping, wbc);
	}
	return ret;
}

/* 
                                                                 
                 
                  
  
                 
 */

static int stuffed_readpage(struct gfs2_inode *ip, struct page *page)
{
	struct buffer_head *dibh;
	u64 dsize = i_size_read(&ip->i_inode);
	void *kaddr;
	int error;

	/*
                                                                 
                                                                       
                                                           
  */
	if (unlikely(page->index)) {
		zero_user(page, 0, PAGE_CACHE_SIZE);
		SetPageUptodate(page);
		return 0;
	}

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		return error;

	kaddr = kmap_atomic(page);
	if (dsize > (dibh->b_size - sizeof(struct gfs2_dinode)))
		dsize = (dibh->b_size - sizeof(struct gfs2_dinode));
	memcpy(kaddr, dibh->b_data + sizeof(struct gfs2_dinode), dsize);
	memset(kaddr + dsize, 0, PAGE_CACHE_SIZE - dsize);
	kunmap_atomic(kaddr);
	flush_dcache_page(page);
	brelse(dibh);
	SetPageUptodate(page);

	return 0;
}


/* 
                             
                                     
                          
  
                                                                     
                                                                   
                                                                     
  
 */

static int __gfs2_readpage(void *file, struct page *page)
{
	struct gfs2_inode *ip = GFS2_I(page->mapping->host);
	struct gfs2_sbd *sdp = GFS2_SB(page->mapping->host);
	int error;

	if (gfs2_is_stuffed(ip)) {
		error = stuffed_readpage(ip, page);
		unlock_page(page);
	} else {
		error = mpage_readpage(page, gfs2_block_map);
	}

	if (unlikely(test_bit(SDF_SHUTDOWN, &sdp->sd_flags)))
		return -EIO;

	return error;
}

/* 
                                        
                          
                              
  
                                                              
                                                           
         
 */

static int gfs2_readpage(struct file *file, struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_holder gh;
	int error;

	unlock_page(page);
	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	error = gfs2_glock_nq(&gh);
	if (unlikely(error))
		goto out;
	error = AOP_TRUNCATED_PAGE;
	lock_page(page);
	if (page->mapping == mapping && !PageUptodate(page))
		error = __gfs2_readpage(file, page);
	else
		unlock_page(page);
	gfs2_glock_dq(&gh);
out:
	gfs2_holder_uninit(&gh);
	if (error && error != AOP_TRUNCATED_PAGE)
		lock_page(page);
	return error;
}

/* 
                                             
                      
                                                            
                           
                          
                            
  
 */

int gfs2_internal_read(struct gfs2_inode *ip, struct file_ra_state *ra_state,
                       char *buf, loff_t *pos, unsigned size)
{
	struct address_space *mapping = ip->i_inode.i_mapping;
	unsigned long index = *pos / PAGE_CACHE_SIZE;
	unsigned offset = *pos & (PAGE_CACHE_SIZE - 1);
	unsigned copied = 0;
	unsigned amt;
	struct page *page;
	void *p;

	do {
		amt = size - copied;
		if (offset + size > PAGE_CACHE_SIZE)
			amt = PAGE_CACHE_SIZE - offset;
		page = read_cache_page(mapping, index, __gfs2_readpage, NULL);
		if (IS_ERR(page))
			return PTR_ERR(page);
		p = kmap_atomic(page);
		memcpy(buf + copied, p + offset, amt);
		kunmap_atomic(p);
		mark_page_accessed(page);
		page_cache_release(page);
		copied += amt;
		index++;
		offset = 0;
	} while(copied < size);
	(*pos) += size;
	return size;
}

/* 
                                                 
  
              
                                                                    
                                                                        
                                                                     
                                                                     
                                                                     
                                                                        
                                                                          
                                                                             
 */

static int gfs2_readpages(struct file *file, struct address_space *mapping,
			  struct list_head *pages, unsigned nr_pages)
{
	struct inode *inode = mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_holder gh;
	int ret;

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	if (unlikely(ret))
		goto out_uninit;
	if (!gfs2_is_stuffed(ip))
		ret = mpage_readpages(mapping, pages, nr_pages, gfs2_block_map);
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	if (unlikely(test_bit(SDF_SHUTDOWN, &sdp->sd_flags)))
		ret = -EIO;
	return ret;
}

/* 
                                              
                              
                                          
                                                  
                            
                        
                                     
                                                      
  
                 
 */

static int gfs2_write_begin(struct file *file, struct address_space *mapping,
			    loff_t pos, unsigned len, unsigned flags,
			    struct page **pagep, void **fsdata)
{
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_sbd *sdp = GFS2_SB(mapping->host);
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	unsigned int data_blocks = 0, ind_blocks = 0, rblocks;
	int alloc_required;
	int error = 0;
	struct gfs2_qadata *qa = NULL;
	pgoff_t index = pos >> PAGE_CACHE_SHIFT;
	unsigned from = pos & (PAGE_CACHE_SIZE - 1);
	struct page *page;

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &ip->i_gh);
	error = gfs2_glock_nq(&ip->i_gh);
	if (unlikely(error))
		goto out_uninit;
	if (&ip->i_inode == sdp->sd_rindex) {
		error = gfs2_glock_nq_init(m_ip->i_gl, LM_ST_EXCLUSIVE,
					   GL_NOCACHE, &m_ip->i_gh);
		if (unlikely(error)) {
			gfs2_glock_dq(&ip->i_gh);
			goto out_uninit;
		}
	}

	alloc_required = gfs2_write_alloc_required(ip, pos, len);

	if (alloc_required || gfs2_is_jdata(ip))
		gfs2_write_calc_reserv(ip, len, &data_blocks, &ind_blocks);

	if (alloc_required) {
		qa = gfs2_qadata_get(ip);
		if (!qa) {
			error = -ENOMEM;
			goto out_unlock;
		}

		error = gfs2_quota_lock_check(ip);
		if (error)
			goto out_alloc_put;

		error = gfs2_inplace_reserve(ip, data_blocks + ind_blocks);
		if (error)
			goto out_qunlock;
	}

	rblocks = RES_DINODE + ind_blocks;
	if (gfs2_is_jdata(ip))
		rblocks += data_blocks ? data_blocks : 1;
	if (ind_blocks || data_blocks)
		rblocks += RES_STATFS + RES_QUOTA;
	if (&ip->i_inode == sdp->sd_rindex)
		rblocks += 2 * RES_STATFS;
	if (alloc_required)
		rblocks += gfs2_rg_blocks(ip);

	error = gfs2_trans_begin(sdp, rblocks,
				 PAGE_CACHE_SIZE/sdp->sd_sb.sb_bsize);
	if (error)
		goto out_trans_fail;

	error = -ENOMEM;
	flags |= AOP_FLAG_NOFS;
	page = grab_cache_page_write_begin(mapping, index, flags);
	*pagep = page;
	if (unlikely(!page))
		goto out_endtrans;

	if (gfs2_is_stuffed(ip)) {
		error = 0;
		if (pos + len > sdp->sd_sb.sb_bsize - sizeof(struct gfs2_dinode)) {
			error = gfs2_unstuff_dinode(ip, page);
			if (error == 0)
				goto prepare_write;
		} else if (!PageUptodate(page)) {
			error = stuffed_readpage(ip, page);
		}
		goto out;
	}

prepare_write:
	error = __block_write_begin(page, from, len, gfs2_block_map);
out:
	if (error == 0)
		return 0;

	unlock_page(page);
	page_cache_release(page);

	gfs2_trans_end(sdp);
	if (pos + len > ip->i_inode.i_size)
		gfs2_trim_blocks(&ip->i_inode);
	goto out_trans_fail;

out_endtrans:
	gfs2_trans_end(sdp);
out_trans_fail:
	if (alloc_required) {
		gfs2_inplace_release(ip);
out_qunlock:
		gfs2_quota_unlock(ip);
out_alloc_put:
		gfs2_qadata_put(ip);
	}
out_unlock:
	if (&ip->i_inode == sdp->sd_rindex) {
		gfs2_glock_dq(&m_ip->i_gh);
		gfs2_holder_uninit(&m_ip->i_gh);
	}
	gfs2_glock_dq(&ip->i_gh);
out_uninit:
	gfs2_holder_uninit(&ip->i_gh);
	return error;
}

/* 
                                                                      
                           
 */
static void adjust_fs_space(struct inode *inode)
{
	struct gfs2_sbd *sdp = inode->i_sb->s_fs_info;
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	struct gfs2_inode *l_ip = GFS2_I(sdp->sd_sc_inode);
	struct gfs2_statfs_change_host *m_sc = &sdp->sd_statfs_master;
	struct gfs2_statfs_change_host *l_sc = &sdp->sd_statfs_local;
	struct buffer_head *m_bh, *l_bh;
	u64 fs_total, new_free;

	/*                                                                 */
	fs_total = gfs2_ri_total(sdp);
	if (gfs2_meta_inode_buffer(m_ip, &m_bh) != 0)
		return;

	spin_lock(&sdp->sd_statfs_spin);
	gfs2_statfs_change_in(m_sc, m_bh->b_data +
			      sizeof(struct gfs2_dinode));
	if (fs_total > (m_sc->sc_total + l_sc->sc_total))
		new_free = fs_total - (m_sc->sc_total + l_sc->sc_total);
	else
		new_free = 0;
	spin_unlock(&sdp->sd_statfs_spin);
	fs_warn(sdp, "File system extended by %llu blocks.\n",
		(unsigned long long)new_free);
	gfs2_statfs_change(sdp, new_free, new_free, 0);

	if (gfs2_meta_inode_buffer(l_ip, &l_bh) != 0)
		goto out;
	update_statfs(sdp, m_bh, l_bh);
	brelse(l_bh);
out:
	brelse(m_bh);
}

/* 
                                                       
                    
                                                      
                          
                                
                                                   
                  
  
                                                                
                                   
  
                 
 */
static int gfs2_stuffed_write_end(struct inode *inode, struct buffer_head *dibh,
				  loff_t pos, unsigned len, unsigned copied,
				  struct page *page)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	u64 to = pos + copied;
	void *kaddr;
	unsigned char *buf = dibh->b_data + sizeof(struct gfs2_dinode);

	BUG_ON((pos + len) > (dibh->b_size - sizeof(struct gfs2_dinode)));
	kaddr = kmap_atomic(page);
	memcpy(buf + pos, kaddr + pos, copied);
	memset(kaddr + pos + copied, 0, len - copied);
	flush_dcache_page(page);
	kunmap_atomic(kaddr);

	if (!PageUptodate(page))
		SetPageUptodate(page);
	unlock_page(page);
	page_cache_release(page);

	if (copied) {
		if (inode->i_size < to)
			i_size_write(inode, to);
		mark_inode_dirty(inode);
	}

	if (inode == sdp->sd_rindex) {
		adjust_fs_space(inode);
		sdp->sd_rindex_uptodate = 0;
	}

	brelse(dibh);
	gfs2_trans_end(sdp);
	if (inode == sdp->sd_rindex) {
		gfs2_glock_dq(&m_ip->i_gh);
		gfs2_holder_uninit(&m_ip->i_gh);
	}
	gfs2_glock_dq(&ip->i_gh);
	gfs2_holder_uninit(&ip->i_gh);
	return copied;
}

/* 
                 
                              
                                          
                          
                               
           
                                        
                                       
  
                                                                   
                                                                  
                                                     
  
                 
 */

static int gfs2_write_end(struct file *file, struct address_space *mapping,
			  loff_t pos, unsigned len, unsigned copied,
			  struct page *page, void *fsdata)
{
	struct inode *inode = page->mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);
	struct buffer_head *dibh;
	struct gfs2_qadata *qa = ip->i_qadata;
	unsigned int from = pos & (PAGE_CACHE_SIZE - 1);
	unsigned int to = from + len;
	int ret;

	BUG_ON(gfs2_glock_is_locked_by_me(ip->i_gl) == NULL);

	ret = gfs2_meta_inode_buffer(ip, &dibh);
	if (unlikely(ret)) {
		unlock_page(page);
		page_cache_release(page);
		goto failed;
	}

	gfs2_trans_add_bh(ip->i_gl, dibh, 1);

	if (gfs2_is_stuffed(ip))
		return gfs2_stuffed_write_end(inode, dibh, pos, len, copied, page);

	if (!gfs2_is_writeback(ip))
		gfs2_page_add_databufs(ip, page, from, to);

	ret = generic_write_end(file, mapping, pos, len, copied, page, fsdata);

	if (inode == sdp->sd_rindex) {
		adjust_fs_space(inode);
		sdp->sd_rindex_uptodate = 0;
	}

	brelse(dibh);
failed:
	gfs2_trans_end(sdp);
	if (ip->i_res)
		gfs2_inplace_release(ip);
	if (qa) {
		gfs2_quota_unlock(ip);
		gfs2_qadata_put(ip);
	}
	if (inode == sdp->sd_rindex) {
		gfs2_glock_dq(&m_ip->i_gh);
		gfs2_holder_uninit(&m_ip->i_gh);
	}
	gfs2_glock_dq(&ip->i_gh);
	gfs2_holder_uninit(&ip->i_gh);
	return ret;
}

/* 
                                               
                           
  
                                                    
 */
 
static int gfs2_set_page_dirty(struct page *page)
{
	SetPageChecked(page);
	return __set_page_dirty_buffers(page);
}

/* 
                                 
                               
                            
  
                                                                
 */

static sector_t gfs2_bmap(struct address_space *mapping, sector_t lblock)
{
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_holder i_gh;
	sector_t dblock = 0;
	int error;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
	if (error)
		return 0;

	if (!gfs2_is_stuffed(ip))
		dblock = generic_block_bmap(mapping, lblock, gfs2_block_map);

	gfs2_glock_dq_uninit(&i_gh);

	return dblock;
}

static void gfs2_discard(struct gfs2_sbd *sdp, struct buffer_head *bh)
{
	struct gfs2_bufdata *bd;

	lock_buffer(bh);
	gfs2_log_lock(sdp);
	clear_buffer_dirty(bh);
	bd = bh->b_private;
	if (bd) {
		if (!list_empty(&bd->bd_le.le_list) && !buffer_pinned(bh))
			list_del_init(&bd->bd_le.le_list);
		else
			gfs2_remove_from_journal(bh, current->journal_info, 0);
	}
	bh->b_bdev = NULL;
	clear_buffer_mapped(bh);
	clear_buffer_req(bh);
	clear_buffer_new(bh);
	gfs2_log_unlock(sdp);
	unlock_buffer(bh);
}

static void gfs2_invalidatepage(struct page *page, unsigned long offset)
{
	struct gfs2_sbd *sdp = GFS2_SB(page->mapping->host);
	struct buffer_head *bh, *head;
	unsigned long pos = 0;

	BUG_ON(!PageLocked(page));
	if (offset == 0)
		ClearPageChecked(page);
	if (!page_has_buffers(page))
		goto out;

	bh = head = page_buffers(page);
	do {
		if (offset <= pos)
			gfs2_discard(sdp, bh);
		pos += bh->b_size;
		bh = bh->b_this_page;
	} while (bh != head);
out:
	if (offset == 0)
		try_to_release_page(page, 0);
}

/* 
                                                         
                 
                     
                                                         
  
                                                                            
                                         
 */
static int gfs2_ok_for_dio(struct gfs2_inode *ip, int rw, loff_t offset)
{
	/*
                                                                 
                                                               
                        
  */
	if (gfs2_is_stuffed(ip))
		return 0;

	if (offset >= i_size_read(&ip->i_inode))
		return 0;
	return 1;
}



static ssize_t gfs2_direct_IO(int rw, struct kiocb *iocb,
			      const struct iovec *iov, loff_t offset,
			      unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder gh;
	int rv;

	/*
                                                                 
                                                                 
                                                                    
                                                              
                                                               
                 
  */
	gfs2_holder_init(ip->i_gl, LM_ST_DEFERRED, 0, &gh);
	rv = gfs2_glock_nq(&gh);
	if (rv)
		return rv;
	rv = gfs2_ok_for_dio(ip, rw, offset);
	if (rv != 1)
		goto out; /*                                          */

	rv = __blockdev_direct_IO(rw, iocb, inode, inode->i_sb->s_bdev, iov,
				  offset, nr_segs, gfs2_get_block_direct,
				  NULL, NULL, 0);
out:
	gfs2_glock_dq_m(1, &gh);
	gfs2_holder_uninit(&gh);
	return rv;
}

/* 
                                                              
                                        
                                                  
  
                                                                
            
  
             
 */

int gfs2_releasepage(struct page *page, gfp_t gfp_mask)
{
	struct address_space *mapping = page->mapping;
	struct gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	struct buffer_head *bh, *head;
	struct gfs2_bufdata *bd;

	if (!page_has_buffers(page))
		return 0;

	gfs2_log_lock(sdp);
	spin_lock(&sdp->sd_ail_lock);
	head = bh = page_buffers(page);
	do {
		if (atomic_read(&bh->b_count))
			goto cannot_release;
		bd = bh->b_private;
		if (bd && bd->bd_ail)
			goto cannot_release;
		if (buffer_pinned(bh) || buffer_dirty(bh))
			goto not_possible;
		bh = bh->b_this_page;
	} while(bh != head);
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);

	head = bh = page_buffers(page);
	do {
		gfs2_log_lock(sdp);
		bd = bh->b_private;
		if (bd) {
			gfs2_assert_warn(sdp, bd->bd_bh == bh);
			gfs2_assert_warn(sdp, list_empty(&bd->bd_list_tr));
			if (!list_empty(&bd->bd_le.le_list)) {
				if (!buffer_pinned(bh))
					list_del_init(&bd->bd_le.le_list);
				else
					bd = NULL;
			}
			if (bd)
				bd->bd_bh = NULL;
			bh->b_private = NULL;
		}
		gfs2_log_unlock(sdp);
		if (bd)
			kmem_cache_free(gfs2_bufdata_cachep, bd);

		bh = bh->b_this_page;
	} while (bh != head);

	return try_to_free_buffers(page);

not_possible: /*                     */
	WARN_ON(buffer_dirty(bh));
	WARN_ON(buffer_pinned(bh));
cannot_release:
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);
	return 0;
}

static const struct address_space_operations gfs2_writeback_aops = {
	.writepage = gfs2_writeback_writepage,
	.writepages = gfs2_writeback_writepages,
	.readpage = gfs2_readpage,
	.readpages = gfs2_readpages,
	.write_begin = gfs2_write_begin,
	.write_end = gfs2_write_end,
	.bmap = gfs2_bmap,
	.invalidatepage = gfs2_invalidatepage,
	.releasepage = gfs2_releasepage,
	.direct_IO = gfs2_direct_IO,
	.migratepage = buffer_migrate_page,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_remove_page = generic_error_remove_page,
};

static const struct address_space_operations gfs2_ordered_aops = {
	.writepage = gfs2_ordered_writepage,
	.readpage = gfs2_readpage,
	.readpages = gfs2_readpages,
	.write_begin = gfs2_write_begin,
	.write_end = gfs2_write_end,
	.set_page_dirty = gfs2_set_page_dirty,
	.bmap = gfs2_bmap,
	.invalidatepage = gfs2_invalidatepage,
	.releasepage = gfs2_releasepage,
	.direct_IO = gfs2_direct_IO,
	.migratepage = buffer_migrate_page,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_remove_page = generic_error_remove_page,
};

static const struct address_space_operations gfs2_jdata_aops = {
	.writepage = gfs2_jdata_writepage,
	.writepages = gfs2_jdata_writepages,
	.readpage = gfs2_readpage,
	.readpages = gfs2_readpages,
	.write_begin = gfs2_write_begin,
	.write_end = gfs2_write_end,
	.set_page_dirty = gfs2_set_page_dirty,
	.bmap = gfs2_bmap,
	.invalidatepage = gfs2_invalidatepage,
	.releasepage = gfs2_releasepage,
	.is_partially_uptodate = block_is_partially_uptodate,
	.error_remove_page = generic_error_remove_page,
};

void gfs2_set_aops(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);

	if (gfs2_is_writeback(ip))
		inode->i_mapping->a_ops = &gfs2_writeback_aops;
	else if (gfs2_is_ordered(ip))
		inode->i_mapping->a_ops = &gfs2_ordered_aops;
	else if (gfs2_is_jdata(ip))
		inode->i_mapping->a_ops = &gfs2_jdata_aops;
	else
		BUG();
}

