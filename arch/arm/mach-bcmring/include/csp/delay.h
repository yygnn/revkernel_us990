/*****************************************************************************
* Copyright 2003 - 2008 Broadcom Corporation.  All rights reserved.
*
* Unless you and Broadcom execute a separate written software license
* agreement governing use of this software, this software is licensed to you
* under the terms of the GNU General Public License version 2, available at
* http://www.broadcom.com/licenses/GPLv2.php (the "GPL").
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a
* license other than the GPL, without Broadcom's express prior written
* consent.
*****************************************************************************/


#ifndef CSP_DELAY_H
#define CSP_DELAY_H

/*                                                                         */

/*                                                                           */
/*                                                                */
/*                                   */
/*                                   */

#if defined(__KERNEL__) && !defined(STANDALONE)
   #include <linux/delay.h>
#else
   #include <mach/csp/delay.h>
#endif

/*                                                                         */
/*                                                                         */
/*                                                                         */

#endif /*              */
