/* src/p80211/p80211req.c
*
* Request/Indication/MacMgmt interface handling functions
*
* Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
* --------------------------------------------------------------------
*
* linux-wlan
*
*   The contents of this file are subject to the Mozilla Public
*   License Version 1.1 (the "License"); you may not use this file
*   except in compliance with the License. You may obtain a copy of
*   the License at http://www.mozilla.org/MPL/
*
*   Software distributed under the License is distributed on an "AS
*   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
*   implied. See the License for the specific language governing
*   rights and limitations under the License.
*
*   Alternatively, the contents of this file may be used under the
*   terms of the GNU Public License version 2 (the "GPL"), in which
*   case the provisions of the GPL are applicable instead of the
*   above.  If you wish to allow the use of your version of this file
*   only under the terms of the GPL and not to allow others to use
*   your version of this file under the MPL, indicate your decision
*   by deleting the provisions above and replace them with the notice
*   and other provisions required by the GPL.  If you do not delete
*   the provisions above, a recipient may use your version of this
*   file under either the MPL or the GPL.
*
* --------------------------------------------------------------------
*
* Inquiries regarding the linux-wlan Open Source project can be
* made directly to:
*
* AbsoluteValue Systems Inc.
* info@linux-wlan.com
* http://www.linux-wlan.com
*
* --------------------------------------------------------------------
*
* Portions of the development of this software were funded by
* Intersil Corporation as part of PRISM(R) chipset product development.
*
* --------------------------------------------------------------------
*
* This file contains the functions, types, and macros to support the
* MLME request interface that's implemented via the device ioctls.
*
* --------------------------------------------------------------------
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/skbuff.h>
#include <linux/wireless.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <net/sock.h>
#include <linux/netlink.h>

#include "p80211types.h"
#include "p80211hdr.h"
#include "p80211mgmt.h"
#include "p80211conv.h"
#include "p80211msg.h"
#include "p80211netdev.h"
#include "p80211ioctl.h"
#include "p80211metadef.h"
#include "p80211metastruct.h"
#include "p80211req.h"

static void p80211req_handlemsg(wlandevice_t *wlandev, struct p80211msg *msg);
static int p80211req_mibset_mibget(wlandevice_t *wlandev,
				   struct p80211msg_dot11req_mibget *mib_msg,
				   int isget);

/*                                                                
                     
 
                                         
 
            
                             
                                             
 
          
                                  
 
               
                                                       
                                                   
                                                                */
int p80211req_dorequest(wlandevice_t *wlandev, u8 *msgbuf)
{
	int result = 0;
	struct p80211msg *msg = (struct p80211msg *) msgbuf;

	/*                                       */
	if (!((wlandev->msdstate == WLAN_MSD_HWPRESENT &&
	       msg->msgcode == DIDmsg_lnxreq_ifstate) ||
	      wlandev->msdstate == WLAN_MSD_RUNNING ||
	      wlandev->msdstate == WLAN_MSD_FWLOAD)) {
		return -ENODEV;
	}

	/*                   */
	if (!capable(CAP_NET_ADMIN) &&
	(msg->msgcode != DIDmsg_dot11req_mibget)) {
		printk(KERN_ERR
		       "%s: only dot11req_mibget allowed for non-root.\n",
		       wlandev->name);
		return -EPERM;
	}

	/*                       */
	if (test_and_set_bit(1, &(wlandev->request_pending)))
		return -EBUSY;

	/*                                                    */
	/*                                                                 */
	/*                  */
	p80211req_handlemsg(wlandev, msg);

	/*                                                  */
	if (wlandev->mlmerequest != NULL)
		wlandev->mlmerequest(wlandev, msg);

	clear_bit(1, &(wlandev->request_pending));
	return result;	/*                                                    */
}

/*                                                                
                     
 
                                                            
                                                                
                                                              
                                       
 
            
                             
                        
 
          
                                                              
 
               
                
                                                                */
static void p80211req_handlemsg(wlandevice_t *wlandev, struct p80211msg *msg)
{
	switch (msg->msgcode) {

	case DIDmsg_lnxreq_hostwep:{
			struct p80211msg_lnxreq_hostwep *req =
			    (struct p80211msg_lnxreq_hostwep *) msg;
			wlandev->hostwep &=
			    ~(HOSTWEP_DECRYPT | HOSTWEP_ENCRYPT);
			if (req->decrypt.data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_DECRYPT;
			if (req->encrypt.data == P80211ENUM_truth_true)
				wlandev->hostwep |= HOSTWEP_ENCRYPT;

			break;
		}
	case DIDmsg_dot11req_mibget:
	case DIDmsg_dot11req_mibset:{
			int isget = (msg->msgcode == DIDmsg_dot11req_mibget);
			struct p80211msg_dot11req_mibget *mib_msg =
			    (struct p80211msg_dot11req_mibget *) msg;
			p80211req_mibset_mibget(wlandev, mib_msg, isget);
		}
	default:
		;
	}			/*                     */

	return;
}

static int p80211req_mibset_mibget(wlandevice_t *wlandev,
				   struct p80211msg_dot11req_mibget *mib_msg,
				   int isget)
{
	p80211itemd_t *mibitem = (p80211itemd_t *) mib_msg->mibattribute.data;
	p80211pstrd_t *pstr = (p80211pstrd_t *) mibitem->data;
	u8 *key = mibitem->data + sizeof(p80211pstrd_t);

	switch (mibitem->did) {
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey0:{
			if (!isget)
				wep_change_key(wlandev, 0, key, pstr->len);
			break;
		}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey1:{
			if (!isget)
				wep_change_key(wlandev, 1, key, pstr->len);
			break;
		}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey2:{
			if (!isget)
				wep_change_key(wlandev, 2, key, pstr->len);
			break;
		}
	case DIDmib_dot11smt_dot11WEPDefaultKeysTable_dot11WEPDefaultKey3:{
			if (!isget)
				wep_change_key(wlandev, 3, key, pstr->len);
			break;
		}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11WEPDefaultKeyID:{
			u32 *data = (u32 *) mibitem->data;

			if (isget) {
				*data =
				    wlandev->hostwep & HOSTWEP_DEFAULTKEY_MASK;
			} else {
				wlandev->hostwep &= ~(HOSTWEP_DEFAULTKEY_MASK);

				wlandev->hostwep |=
				    (*data & HOSTWEP_DEFAULTKEY_MASK);
			}
			break;
		}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11PrivacyInvoked:{
			u32 *data = (u32 *) mibitem->data;

			if (isget) {
				if (wlandev->hostwep & HOSTWEP_PRIVACYINVOKED)
					*data = P80211ENUM_truth_true;
				else
					*data = P80211ENUM_truth_false;
			} else {
				wlandev->hostwep &= ~(HOSTWEP_PRIVACYINVOKED);
				if (*data == P80211ENUM_truth_true)
					wlandev->hostwep |=
					    HOSTWEP_PRIVACYINVOKED;
			}
			break;
		}
	case DIDmib_dot11smt_dot11PrivacyTable_dot11ExcludeUnencrypted:{
			u32 *data = (u32 *) mibitem->data;

			if (isget) {
				if (wlandev->hostwep &
				    HOSTWEP_EXCLUDEUNENCRYPTED)
					*data = P80211ENUM_truth_true;
				else
					*data = P80211ENUM_truth_false;
			} else {
				wlandev->hostwep &=
				    ~(HOSTWEP_EXCLUDEUNENCRYPTED);
				if (*data == P80211ENUM_truth_true)
					wlandev->hostwep |=
					    HOSTWEP_EXCLUDEUNENCRYPTED;
			}
			break;
		}
	default:
		;
	}

	return 0;
}