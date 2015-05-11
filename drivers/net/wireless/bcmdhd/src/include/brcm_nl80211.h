/*
 * Definitions for nl80211 vendor command/event access to host driver
 *
 * Copyright (C) 1999-2014, Broadcom Corporation
 * 
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 * $Id: brcm_nl80211.h 515139 2014-11-13 08:47:48Z $
 *
 */

#ifndef _brcm_nl80211_h_
#define _brcm_nl80211_h_

struct bcm_nlmsg_hdr {
	uint cmd;	/*                         */
	uint len;	/*                               */
	uint offset;	/*                    */
	uint set;	/*                             */
	uint magic;	/*                               */
};

enum bcmnl_attrs {
	BCM_NLATTR_UNSPEC,

	BCM_NLATTR_LEN,
	BCM_NLATTR_DATA,

	__BCM_NLATTR_AFTER_LAST,
	BCM_NLATTR_MAX = __BCM_NLATTR_AFTER_LAST - 1
};

struct nl_prv_data {
	int err;			/*               */
	void *data;			/*                             */
	uint len;			/*                            */
	struct bcm_nlmsg_hdr *nlioc;	/*                              */
};

#endif /*                  */
