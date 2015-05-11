/*
 * KwikByte CAM60 (KB9260)
 *
 * based on board-sam9260ek.c
 *   Copyright (C) 2005 SAN People
 *   Copyright (C) 2006 Atmel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/types.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/spi/flash.h>

#include <mach/hardware.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/irq.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/board.h>
#include <mach/at91sam9_smc.h>

#include "sam9_smc.h"
#include "generic.h"


static void __init cam60_init_early(void)
{
	/*                                      */
	at91_initialize(10000000);

	/*                               */
	at91_register_uart(0, 0, 0);

	/*                                        */
	at91_set_serial_console(0);
}

/*
           
 */
static struct at91_usbh_data __initdata cam60_usbh_data = {
	.ports		= 1,
	.vbus_pin	= {-EINVAL, -EINVAL},
	.overcurrent_pin= {-EINVAL, -EINVAL},
};


/*
               
 */
#if defined(CONFIG_MTD_DATAFLASH)
static struct mtd_partition cam60_spi_partitions[] = {
	{
		.name	= "BOOT1",
		.offset	= 0,
		.size	= 4 * 1056,
	},
	{
		.name	= "BOOT2",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= 256 * 1056,
	},
	{
		.name	= "kernel",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= 2222 * 1056,
	},
	{
		.name	= "file system",
		.offset	= MTDPART_OFS_NXTBLK,
		.size	= MTDPART_SIZ_FULL,
	},
};

static struct flash_platform_data cam60_spi_flash_platform_data = {
	.name		= "spi_flash",
	.parts		= cam60_spi_partitions,
	.nr_parts	= ARRAY_SIZE(cam60_spi_partitions)
};
#endif

static struct spi_board_info cam60_spi_devices[] __initdata = {
#if defined(CONFIG_MTD_DATAFLASH)
	{	/*                */
		.modalias	= "mtd_dataflash",
		.chip_select	= 0,
		.max_speed_hz	= 15 * 1000 * 1000,
		.bus_num	= 0,
		.platform_data	= &cam60_spi_flash_platform_data
	},
#endif
};


/*
                       
 */
static struct __initdata macb_platform_data cam60_macb_data = {
	.phy_irq_pin	= AT91_PIN_PB5,
	.is_rmii	= 0,
};


/*
             
 */
static struct mtd_partition __initdata cam60_nand_partition[] = {
	{
		.name	= "nand_fs",
		.offset	= 0,
		.size	= MTDPART_SIZ_FULL,
	},
};

static struct atmel_nand_data __initdata cam60_nand_data = {
	.ale		= 21,
	.cle		= 22,
	.det_pin	= -EINVAL,
	.rdy_pin	= AT91_PIN_PA9,
	.enable_pin	= AT91_PIN_PA7,
	.ecc_mode	= NAND_ECC_SOFT,
	.parts		= cam60_nand_partition,
	.num_parts	= ARRAY_SIZE(cam60_nand_partition),
};

static struct sam9_smc_config __initdata cam60_nand_smc_config = {
	.ncs_read_setup		= 0,
	.nrd_setup		= 1,
	.ncs_write_setup	= 0,
	.nwe_setup		= 1,

	.ncs_read_pulse		= 3,
	.nrd_pulse		= 3,
	.ncs_write_pulse	= 3,
	.nwe_pulse		= 3,

	.read_cycle		= 5,
	.write_cycle		= 5,

	.mode			= AT91_SMC_READMODE | AT91_SMC_WRITEMODE | AT91_SMC_EXNWMODE_DISABLE | AT91_SMC_DBW_8,
	.tdf_cycles		= 2,
};

static void __init cam60_add_device_nand(void)
{
	/*                                */
	sam9_smc_configure(0, 3, &cam60_nand_smc_config);

	at91_add_device_nand(&cam60_nand_data);
}


static void __init cam60_board_init(void)
{
	/*        */
	at91_add_device_serial();
	/*     */
	at91_add_device_spi(cam60_spi_devices, ARRAY_SIZE(cam60_spi_devices));
	/*          */
	at91_add_device_eth(&cam60_macb_data);
	/*          */
	/*                                 */
	at91_set_gpio_output(AT91_PIN_PB18, 1);
	at91_add_device_usbh(&cam60_usbh_data);
	/*      */
	cam60_add_device_nand();
}

MACHINE_START(CAM60, "KwikByte CAM60")
	/*                      */
	.timer		= &at91sam926x_timer,
	.map_io		= at91_map_io,
	.init_early	= cam60_init_early,
	.init_irq	= at91_init_irq_default,
	.init_machine	= cam60_board_init,
MACHINE_END