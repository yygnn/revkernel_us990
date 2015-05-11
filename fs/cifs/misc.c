/*
 *   fs/cifs/misc.c
 *
 *   Copyright (C) International Business Machines  Corp., 2002,2008
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this library; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <linux/slab.h>
#include <linux/ctype.h>
#include <linux/mempool.h>
#include "cifspdu.h"
#include "cifsglob.h"
#include "cifsproto.h"
#include "cifs_debug.h"
#include "smberr.h"
#include "nterr.h"
#include "cifs_unicode.h"

extern mempool_t *cifs_sm_req_poolp;
extern mempool_t *cifs_req_poolp;

/*                                                                     
                                                                      
                                                                 
                                                                      
                                 */

unsigned int
_GetXid(void)
{
	unsigned int xid;

	spin_lock(&GlobalMid_Lock);
	GlobalTotalActiveXid++;

	/*                                                                   */
	if (GlobalTotalActiveXid > GlobalMaxActiveXid)
		GlobalMaxActiveXid = GlobalTotalActiveXid;
	if (GlobalTotalActiveXid > 65000)
		cFYI(1, "warning: more than 65000 requests active");
	xid = GlobalCurrentXid++;
	spin_unlock(&GlobalMid_Lock);
	return xid;
}

void
_FreeXid(unsigned int xid)
{
	spin_lock(&GlobalMid_Lock);
	/*                               
         */
	GlobalTotalActiveXid--;
	spin_unlock(&GlobalMid_Lock);
}

struct cifs_ses *
sesInfoAlloc(void)
{
	struct cifs_ses *ret_buf;

	ret_buf = kzalloc(sizeof(struct cifs_ses), GFP_KERNEL);
	if (ret_buf) {
		atomic_inc(&sesInfoAllocCount);
		ret_buf->status = CifsNew;
		++ret_buf->ses_count;
		INIT_LIST_HEAD(&ret_buf->smb_ses_list);
		INIT_LIST_HEAD(&ret_buf->tcon_list);
		mutex_init(&ret_buf->session_mutex);
	}
	return ret_buf;
}

void
sesInfoFree(struct cifs_ses *buf_to_free)
{
	if (buf_to_free == NULL) {
		cFYI(1, "Null buffer passed to sesInfoFree");
		return;
	}

	atomic_dec(&sesInfoAllocCount);
	kfree(buf_to_free->serverOS);
	kfree(buf_to_free->serverDomain);
	kfree(buf_to_free->serverNOS);
	if (buf_to_free->password) {
		memset(buf_to_free->password, 0, strlen(buf_to_free->password));
		kfree(buf_to_free->password);
	}
	kfree(buf_to_free->user_name);
	kfree(buf_to_free->domainName);
	kfree(buf_to_free);
}

struct cifs_tcon *
tconInfoAlloc(void)
{
	struct cifs_tcon *ret_buf;
	ret_buf = kzalloc(sizeof(struct cifs_tcon), GFP_KERNEL);
	if (ret_buf) {
		atomic_inc(&tconInfoAllocCount);
		ret_buf->tidStatus = CifsNew;
		++ret_buf->tc_count;
		INIT_LIST_HEAD(&ret_buf->openFileList);
		INIT_LIST_HEAD(&ret_buf->tcon_list);
#ifdef CONFIG_CIFS_STATS
		spin_lock_init(&ret_buf->stat_lock);
#endif
	}
	return ret_buf;
}

void
tconInfoFree(struct cifs_tcon *buf_to_free)
{
	if (buf_to_free == NULL) {
		cFYI(1, "Null buffer passed to tconInfoFree");
		return;
	}
	atomic_dec(&tconInfoAllocCount);
	kfree(buf_to_free->nativeFileSystem);
	if (buf_to_free->password) {
		memset(buf_to_free->password, 0, strlen(buf_to_free->password));
		kfree(buf_to_free->password);
	}
	kfree(buf_to_free);
}

struct smb_hdr *
cifs_buf_get(void)
{
	struct smb_hdr *ret_buf = NULL;

/*                                                      
                                                         
                                                          
                                          */
	ret_buf = mempool_alloc(cifs_req_poolp, GFP_NOFS);

	/*                                  */
	/*                                                    */
	if (ret_buf) {
		memset(ret_buf, 0, sizeof(struct smb_hdr) + 3);
		atomic_inc(&bufAllocCount);
#ifdef CONFIG_CIFS_STATS2
		atomic_inc(&totBufAllocCount);
#endif /*                    */
	}

	return ret_buf;
}

void
cifs_buf_release(void *buf_to_free)
{
	if (buf_to_free == NULL) {
		/*                                                   */
		return;
	}
	mempool_free(buf_to_free, cifs_req_poolp);

	atomic_dec(&bufAllocCount);
	return;
}

struct smb_hdr *
cifs_small_buf_get(void)
{
	struct smb_hdr *ret_buf = NULL;

/*                                                      
                                                         
                                                          
                                          */
	ret_buf = mempool_alloc(cifs_sm_req_poolp, GFP_NOFS);
	if (ret_buf) {
	/*                                                          */
	/*                                                 */
		atomic_inc(&smBufAllocCount);
#ifdef CONFIG_CIFS_STATS2
		atomic_inc(&totSmBufAllocCount);
#endif /*                    */

	}
	return ret_buf;
}

void
cifs_small_buf_release(void *buf_to_free)
{

	if (buf_to_free == NULL) {
		cFYI(1, "Null buffer passed to cifs_small_buf_release");
		return;
	}
	mempool_free(buf_to_free, cifs_sm_req_poolp);

	atomic_dec(&smBufAllocCount);
	return;
}

/*
                                                               
                                                                
                                                                 
                                                                 
                                                            
                                                          
                                                       
                                                         
                                                            
                                             
                                                       
                                                    
                                                      
                                                       
                                                               
                                                                
                                                         
                                                             
                                                
 */
__u64 GetNextMid(struct TCP_Server_Info *server)
{
	__u64 mid = 0;
	__u16 last_mid, cur_mid;
	bool collision;

	spin_lock(&GlobalMid_Lock);

	/*                                 */
	cur_mid = (__u16)((server->CurrentMid) & 0xffff);
	/*                                */
	last_mid = cur_mid;
	cur_mid++;

	/*
                                                     
                                                      
                                                       
                                                          
                                                        
                                                       
                      
  */
	while (cur_mid != last_mid) {
		struct mid_q_entry *mid_entry;
		unsigned int num_mids;

		collision = false;
		if (cur_mid == 0)
			cur_mid++;

		num_mids = 0;
		list_for_each_entry(mid_entry, &server->pending_mid_q, qhead) {
			++num_mids;
			if (mid_entry->mid == cur_mid &&
			    mid_entry->mid_state == MID_REQUEST_SUBMITTED) {
				/*                                         */
				collision = true;
				break;
			}
		}

		/*
                                                              
                                                              
                                                               
                                                          
                                 
    
                                                                 
                                                          
   */
		if (num_mids > 32768)
			server->tcpStatus = CifsNeedReconnect;

		if (!collision) {
			mid = (__u64)cur_mid;
			server->CurrentMid = mid;
			break;
		}
		cur_mid++;
	}
	spin_unlock(&GlobalMid_Lock);
	return mid;
}

/*                                                         
                                                     */
void
header_assemble(struct smb_hdr *buffer, char smb_command /*         */ ,
		const struct cifs_tcon *treeCon, int word_count
		/*                                                         */)
{
	struct list_head *temp_item;
	struct cifs_ses *ses;
	char *temp = (char *) buffer;

	memset(temp, 0, 256); /*                               */

	buffer->smb_buf_length = cpu_to_be32(
	    (2 * word_count) + sizeof(struct smb_hdr) -
	    4 /*                                       */  +
	    2 /*                      */) ;

	buffer->Protocol[0] = 0xFF;
	buffer->Protocol[1] = 'S';
	buffer->Protocol[2] = 'M';
	buffer->Protocol[3] = 'B';
	buffer->Command = smb_command;
	buffer->Flags = 0x00;	/*                */
	buffer->Flags2 = SMBFLG2_KNOWS_LONG_NAMES;
	buffer->Pid = cpu_to_le16((__u16)current->tgid);
	buffer->PidHigh = cpu_to_le16((__u16)(current->tgid >> 16));
	if (treeCon) {
		buffer->Tid = treeCon->tid;
		if (treeCon->ses) {
			if (treeCon->ses->capabilities & CAP_UNICODE)
				buffer->Flags2 |= SMBFLG2_UNICODE;
			if (treeCon->ses->capabilities & CAP_STATUS32)
				buffer->Flags2 |= SMBFLG2_ERR_STATUS;

			/*                      */
			buffer->Uid = treeCon->ses->Suid;
			buffer->Mid = GetNextMid(treeCon->ses->server);
			if (multiuser_mount != 0) {
		/*                                                            */
		/*                                                            */
		/*                                              */
		/*                                                        */
		/*                                                        */
		/*                                                            */
		/*                                                        */
		/*                                                            */
		/*                                                            */
		/*                                                            */
		/*                       */
		/*                                                  */
		/*                                                       */
		/*                                                       */
		/*                                                            */
		/*                                                        */
		/*                                                        */
		/*                                                            */
		/*                                                        */
		/*                          */

		/*                                                            */
		/*                                                            */
		/*                                           */
				if (current_fsuid() != treeCon->ses->linux_uid) {
					cFYI(1, "Multiuser mode and UID "
						 "did not match tcon uid");
					spin_lock(&cifs_tcp_ses_lock);
					list_for_each(temp_item, &treeCon->ses->server->smb_ses_list) {
						ses = list_entry(temp_item, struct cifs_ses, smb_ses_list);
						if (ses->linux_uid == current_fsuid()) {
							if (ses->server == treeCon->ses->server) {
								cFYI(1, "found matching uid substitute right smb_uid");
								buffer->Uid = ses->Suid;
								break;
							} else {
				/*                                            */
								cFYI(1, "local UID found but no smb sess with this server exists");
							}
						}
					}
					spin_unlock(&cifs_tcp_ses_lock);
				}
			}
		}
		if (treeCon->Flags & SMB_SHARE_IS_IN_DFS)
			buffer->Flags2 |= SMBFLG2_DFS;
		if (treeCon->nocase)
			buffer->Flags  |= SMBFLG_CASELESS;
		if ((treeCon->ses) && (treeCon->ses->server))
			if (treeCon->ses->server->sec_mode &
			  (SECMODE_SIGN_REQUIRED | SECMODE_SIGN_ENABLED))
				buffer->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;
	}

/*                                                             */
	buffer->WordCount = (char) word_count;
	return;
}

static int
check_smb_hdr(struct smb_hdr *smb, __u16 mid)
{
	/*                                          */
	if (*(__le32 *) smb->Protocol != cpu_to_le32(0x424d53ff)) {
		cERROR(1, "Bad protocol string signature header 0x%x",
			*(unsigned int *)smb->Protocol);
		return 1;
	}

	/*                                  */
	if (mid != smb->Mid) {
		cERROR(1, "Mids do not match. received=%u expected=%u",
			smb->Mid, mid);
		return 1;
	}

	/*                                */
	if (smb->Flags & SMBFLG_RESPONSE)
		return 0;

	/*                                                   */
	if (smb->Command == SMB_COM_LOCKING_ANDX)
		return 0;

	cERROR(1, "Server sent request, not response. mid=%u", smb->Mid);
	return 1;
}

int
checkSMB(char *buf, unsigned int total_read)
{
	struct smb_hdr *smb = (struct smb_hdr *)buf;
	__u16 mid = smb->Mid;
	__u32 rfclen = be32_to_cpu(smb->smb_buf_length);
	__u32 clc_len;  /*                   */
	cFYI(0, "checkSMB Length: 0x%x, smb_buf_length: 0x%x",
		total_read, rfclen);

	/*                                               */
	if (total_read < 2 + sizeof(struct smb_hdr)) {
		if ((total_read >= sizeof(struct smb_hdr) - 1)
			    && (smb->Status.CifsError != 0)) {
			/*                      */
			smb->WordCount = 0;
			/*                                            */
			return 0;
		} else if ((total_read == sizeof(struct smb_hdr) + 1) &&
				(smb->WordCount == 0)) {
			char *tmp = (char *)smb;
			/*                                               */
			/*                                                    */
			if (tmp[sizeof(struct smb_hdr)] == 0) {
				/*                                     
                                               
                                      
                                          
                                              
     */
				/*                  */
				tmp[sizeof(struct smb_hdr)+1] = 0;
				return 0;
			}
			cERROR(1, "rcvd invalid byte count (bcc)");
		} else {
			cERROR(1, "Length less than smb header size");
		}
		return -EIO;
	}

	/*                                              */
	if (check_smb_hdr(smb, mid))
		return -EIO;
	clc_len = smbCalcSize(smb);

	if (4 + rfclen != total_read) {
		cERROR(1, "Length read does not match RFC1001 length %d",
				rfclen);
		return -EIO;
	}

	if (4 + rfclen != clc_len) {
		/*                                                      */
		if ((rfclen > 64 * 1024) && (rfclen > clc_len)) {
			/*                                */
			if (((4 + rfclen) & 0xFFFF) == (clc_len & 0xFFFF))
				return 0; /*             */
		}
		cFYI(1, "Calculated size %u vs length %u mismatch for mid=%u",
				clc_len, 4 + rfclen, smb->Mid);

		if (4 + rfclen < clc_len) {
			cERROR(1, "RFC1001 size %u smaller than SMB for mid=%u",
					rfclen, smb->Mid);
			return -EIO;
		} else if (rfclen > clc_len + 512) {
			/*
                                                       
                                                   
                                                     
                                                       
                                                    
                                                        
                        
    */
			cERROR(1, "RFC1001 size %u more than 512 bytes larger "
				  "than SMB for mid=%u", rfclen, smb->Mid);
			return -EIO;
		}
	}
	return 0;
}

bool
is_valid_oplock_break(char *buffer, struct TCP_Server_Info *srv)
{
	struct smb_hdr *buf = (struct smb_hdr *)buffer;
	struct smb_com_lock_req *pSMB = (struct smb_com_lock_req *)buf;
	struct list_head *tmp, *tmp1, *tmp2;
	struct cifs_ses *ses;
	struct cifs_tcon *tcon;
	struct cifsInodeInfo *pCifsInode;
	struct cifsFileInfo *netfile;

	cFYI(1, "Checking for oplock break or dnotify response");
	if ((pSMB->hdr.Command == SMB_COM_NT_TRANSACT) &&
	   (pSMB->hdr.Flags & SMBFLG_RESPONSE)) {
		struct smb_com_transaction_change_notify_rsp *pSMBr =
			(struct smb_com_transaction_change_notify_rsp *)buf;
		struct file_notify_information *pnotify;
		__u32 data_offset = 0;
		if (get_bcc(buf) > sizeof(struct file_notify_information)) {
			data_offset = le32_to_cpu(pSMBr->DataOffset);

			pnotify = (struct file_notify_information *)
				((char *)&pSMBr->hdr.Protocol + data_offset);
			cFYI(1, "dnotify on %s Action: 0x%x",
				 pnotify->FileName, pnotify->Action);
			/*                                          
                                */
			return true;
		}
		if (pSMBr->hdr.Status.CifsError) {
			cFYI(1, "notify err 0x%d",
				pSMBr->hdr.Status.CifsError);
			return true;
		}
		return false;
	}
	if (pSMB->hdr.Command != SMB_COM_LOCKING_ANDX)
		return false;
	if (pSMB->hdr.Flags & SMBFLG_RESPONSE) {
		/*                                                   
                                                           
                                                             
                                            */
		if ((NT_STATUS_INVALID_HANDLE) ==
		   le32_to_cpu(pSMB->hdr.Status.CifsError)) {
			cFYI(1, "invalid handle on oplock break");
			return true;
		} else if (ERRbadfid ==
		   le16_to_cpu(pSMB->hdr.Status.DosError.Error)) {
			return true;
		} else {
			return false; /*                                      */
		}
	}
	if (pSMB->hdr.WordCount != 8)
		return false;

	cFYI(1, "oplock type 0x%d level 0x%d",
		 pSMB->LockType, pSMB->OplockLevel);
	if (!(pSMB->LockType & LOCKING_ANDX_OPLOCK_RELEASE))
		return false;

	/*                                 */
	spin_lock(&cifs_tcp_ses_lock);
	list_for_each(tmp, &srv->smb_ses_list) {
		ses = list_entry(tmp, struct cifs_ses, smb_ses_list);
		list_for_each(tmp1, &ses->tcon_list) {
			tcon = list_entry(tmp1, struct cifs_tcon, tcon_list);
			if (tcon->tid != buf->Tid)
				continue;

			cifs_stats_inc(&tcon->num_oplock_brks);
			spin_lock(&cifs_file_list_lock);
			list_for_each(tmp2, &tcon->openFileList) {
				netfile = list_entry(tmp2, struct cifsFileInfo,
						     tlist);
				if (pSMB->Fid != netfile->netfid)
					continue;

				cFYI(1, "file id match, oplock break");
				pCifsInode = CIFS_I(netfile->dentry->d_inode);

				cifs_set_oplock_level(pCifsInode,
					pSMB->OplockLevel ? OPLOCK_READ : 0);
				queue_work(cifsiod_wq,
					   &netfile->oplock_break);
				netfile->oplock_break_cancelled = false;

				spin_unlock(&cifs_file_list_lock);
				spin_unlock(&cifs_tcp_ses_lock);
				return true;
			}
			spin_unlock(&cifs_file_list_lock);
			spin_unlock(&cifs_tcp_ses_lock);
			cFYI(1, "No matching file for oplock break");
			return true;
		}
	}
	spin_unlock(&cifs_tcp_ses_lock);
	cFYI(1, "Can not process oplock break for non-existent connection");
	return true;
}

void
dump_smb(void *buf, int smb_buf_length)
{
	int i, j;
	char debug_line[17];
	unsigned char *buffer = buf;

	if (traceSMB == 0)
		return;

	for (i = 0, j = 0; i < smb_buf_length; i++, j++) {
		if (i % 8 == 0) {
			/*                                    */
			printk(KERN_DEBUG "| ");
			j = 0;
		}
		printk("%0#4x ", buffer[i]);
		debug_line[2 * j] = ' ';
		if (isprint(buffer[i]))
			debug_line[1 + (2 * j)] = buffer[i];
		else
			debug_line[1 + (2 * j)] = '_';

		if (i % 8 == 7) {
			/*                                          */
			debug_line[16] = 0;
			printk(" | %s\n", debug_line);
		}
	}
	for (; j < 8; j++) {
		printk("     ");
		debug_line[2 * j] = ' ';
		debug_line[1 + (2 * j)] = ' ';
	}
	printk(" | %s\n", debug_line);
	return;
}

void
cifs_autodisable_serverino(struct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) {
		cifs_sb->mnt_cifs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		cERROR(1, "Autodisabling the use of server inode numbers on "
			   "%s. This server doesn't seem to support them "
			   "properly. Hardlinks will not be recognized on this "
			   "mount. Consider mounting with the \"noserverino\" "
			   "option to silence this message.",
			   cifs_sb_master_tcon(cifs_sb)->treeName);
	}
}

void cifs_set_oplock_level(struct cifsInodeInfo *cinode, __u32 oplock)
{
	oplock &= 0xF;

	if (oplock == OPLOCK_EXCLUSIVE) {
		cinode->clientCanCacheAll = true;
		cinode->clientCanCacheRead = true;
		cFYI(1, "Exclusive Oplock granted on inode %p",
		     &cinode->vfs_inode);
	} else if (oplock == OPLOCK_READ) {
		cinode->clientCanCacheAll = false;
		cinode->clientCanCacheRead = true;
		cFYI(1, "Level II Oplock granted on inode %p",
		    &cinode->vfs_inode);
	} else {
		cinode->clientCanCacheAll = false;
		cinode->clientCanCacheRead = false;
	}
}

bool
backup_cred(struct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPUID) {
		if (cifs_sb->mnt_backupuid == current_fsuid())
			return true;
	}
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_CIFS_BACKUPGID) {
		if (in_group_p(cifs_sb->mnt_backupgid))
			return true;
	}

	return false;
}

void
cifs_add_credits(struct TCP_Server_Info *server, const unsigned int add)
{
	spin_lock(&server->req_lock);
	server->credits += add;
	server->in_flight--;
	spin_unlock(&server->req_lock);
	wake_up(&server->request_q);
}

void
cifs_set_credits(struct TCP_Server_Info *server, const int val)
{
	spin_lock(&server->req_lock);
	server->credits = val;
	server->oplocks = val > 1 ? enable_oplocks : false;
	spin_unlock(&server->req_lock);
}
