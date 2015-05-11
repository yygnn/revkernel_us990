/*****************************************************************************
	Copyright(c) 2013 FCI Inc. All Rights Reserved

	File name : fci_tun.h

	Description : tuner control driver header file

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA


	History :
	----------------------------------------------------------------------
*******************************************************************************/

#ifndef __FCI_TUN_H__
#define __FCI_TUN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fci_types.h"

enum i2c_type {
	FCI_HPI_TYPE
};

enum band_type {
	BAND3_TYPE
};

enum product_type {
	FC8080_TUNER
};

extern fci_s32 tuner_i2c_init(HANDLE handle, fci_s32 speed, fci_s32 slaveaddr);
extern fci_s32 tuner_i2c_deinit(HANDLE handle);
extern fci_s32 tuner_i2c_read(HANDLE handle, fci_u8 addr, fci_u8 addr_len, fci_u8 *data,
				fci_u8 len);
extern fci_s32 tuner_i2c_write(HANDLE handle, fci_u8 addr, fci_u8 addr_len, fci_u8 *data,
				fci_u8 len);
extern fci_s32 tuner_select(HANDLE handle, enum product_type product,
				enum band_type band);
extern fci_s32 tuner_set_freq(HANDLE handle, fci_u32 freq);
extern fci_s32 tuner_get_rssi(HANDLE handle, fci_s32 *rssi);

#ifdef __cplusplus
}
#endif

#endif /*               */

