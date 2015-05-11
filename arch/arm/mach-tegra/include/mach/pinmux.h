/*
 * linux/arch/arm/mach-tegra/include/mach/pinmux.h
 *
 * Copyright (C) 2010 Google, Inc.
 * Copyright (C) 2010,2011 Nvidia, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_TEGRA_PINMUX_H
#define __MACH_TEGRA_PINMUX_H

enum tegra_mux_func {
	TEGRA_MUX_RSVD = 0x8000,
	TEGRA_MUX_RSVD1 = 0x8000,
	TEGRA_MUX_RSVD2 = 0x8001,
	TEGRA_MUX_RSVD3 = 0x8002,
	TEGRA_MUX_RSVD4 = 0x8003,
	TEGRA_MUX_INVALID = 0x4000,
	TEGRA_MUX_NONE = -1,
	TEGRA_MUX_AHB_CLK,
	TEGRA_MUX_APB_CLK,
	TEGRA_MUX_AUDIO_SYNC,
	TEGRA_MUX_CRT,
	TEGRA_MUX_DAP1,
	TEGRA_MUX_DAP2,
	TEGRA_MUX_DAP3,
	TEGRA_MUX_DAP4,
	TEGRA_MUX_DAP5,
	TEGRA_MUX_DISPLAYA,
	TEGRA_MUX_DISPLAYB,
	TEGRA_MUX_EMC_TEST0_DLL,
	TEGRA_MUX_EMC_TEST1_DLL,
	TEGRA_MUX_GMI,
	TEGRA_MUX_GMI_INT,
	TEGRA_MUX_HDMI,
	TEGRA_MUX_I2C,
	TEGRA_MUX_I2C2,
	TEGRA_MUX_I2C3,
	TEGRA_MUX_IDE,
	TEGRA_MUX_IRDA,
	TEGRA_MUX_KBC,
	TEGRA_MUX_MIO,
	TEGRA_MUX_MIPI_HS,
	TEGRA_MUX_NAND,
	TEGRA_MUX_OSC,
	TEGRA_MUX_OWR,
	TEGRA_MUX_PCIE,
	TEGRA_MUX_PLLA_OUT,
	TEGRA_MUX_PLLC_OUT1,
	TEGRA_MUX_PLLM_OUT1,
	TEGRA_MUX_PLLP_OUT2,
	TEGRA_MUX_PLLP_OUT3,
	TEGRA_MUX_PLLP_OUT4,
	TEGRA_MUX_PWM,
	TEGRA_MUX_PWR_INTR,
	TEGRA_MUX_PWR_ON,
	TEGRA_MUX_RTCK,
	TEGRA_MUX_SDIO1,
	TEGRA_MUX_SDIO2,
	TEGRA_MUX_SDIO3,
	TEGRA_MUX_SDIO4,
	TEGRA_MUX_SFLASH,
	TEGRA_MUX_SPDIF,
	TEGRA_MUX_SPI1,
	TEGRA_MUX_SPI2,
	TEGRA_MUX_SPI2_ALT,
	TEGRA_MUX_SPI3,
	TEGRA_MUX_SPI4,
	TEGRA_MUX_TRACE,
	TEGRA_MUX_TWC,
	TEGRA_MUX_UARTA,
	TEGRA_MUX_UARTB,
	TEGRA_MUX_UARTC,
	TEGRA_MUX_UARTD,
	TEGRA_MUX_UARTE,
	TEGRA_MUX_ULPI,
	TEGRA_MUX_VI,
	TEGRA_MUX_VI_SENSOR_CLK,
	TEGRA_MUX_XIO,
	TEGRA_MUX_BLINK,
	TEGRA_MUX_CEC,
	TEGRA_MUX_CLK12,
	TEGRA_MUX_DAP,
	TEGRA_MUX_DAPSDMMC2,
	TEGRA_MUX_DDR,
	TEGRA_MUX_DEV3,
	TEGRA_MUX_DTV,
	TEGRA_MUX_VI_ALT1,
	TEGRA_MUX_VI_ALT2,
	TEGRA_MUX_VI_ALT3,
	TEGRA_MUX_EMC_DLL,
	TEGRA_MUX_EXTPERIPH1,
	TEGRA_MUX_EXTPERIPH2,
	TEGRA_MUX_EXTPERIPH3,
	TEGRA_MUX_GMI_ALT,
	TEGRA_MUX_HDA,
	TEGRA_MUX_HSI,
	TEGRA_MUX_I2C4,
	TEGRA_MUX_I2C5,
	TEGRA_MUX_I2CPWR,
	TEGRA_MUX_I2S0,
	TEGRA_MUX_I2S1,
	TEGRA_MUX_I2S2,
	TEGRA_MUX_I2S3,
	TEGRA_MUX_I2S4,
	TEGRA_MUX_NAND_ALT,
	TEGRA_MUX_POPSDIO4,
	TEGRA_MUX_POPSDMMC4,
	TEGRA_MUX_PWM0,
	TEGRA_MUX_PWM1,
	TEGRA_MUX_PWM2,
	TEGRA_MUX_PWM3,
	TEGRA_MUX_SATA,
	TEGRA_MUX_SPI5,
	TEGRA_MUX_SPI6,
	TEGRA_MUX_SYSCLK,
	TEGRA_MUX_VGP1,
	TEGRA_MUX_VGP2,
	TEGRA_MUX_VGP3,
	TEGRA_MUX_VGP4,
	TEGRA_MUX_VGP5,
	TEGRA_MUX_VGP6,
	TEGRA_MUX_SAFE,
	TEGRA_MAX_MUX,
};

enum tegra_pullupdown {
	TEGRA_PUPD_NORMAL = 0,
	TEGRA_PUPD_PULL_DOWN,
	TEGRA_PUPD_PULL_UP,
};

enum tegra_tristate {
	TEGRA_TRI_NORMAL = 0,
	TEGRA_TRI_TRISTATE = 1,
};

enum tegra_pin_io {
	TEGRA_PIN_OUTPUT = 0,
	TEGRA_PIN_INPUT = 1,
};

enum tegra_vddio {
	TEGRA_VDDIO_BB = 0,
	TEGRA_VDDIO_LCD,
	TEGRA_VDDIO_VI,
	TEGRA_VDDIO_UART,
	TEGRA_VDDIO_DDR,
	TEGRA_VDDIO_NAND,
	TEGRA_VDDIO_SYS,
	TEGRA_VDDIO_AUDIO,
	TEGRA_VDDIO_SD,
	TEGRA_VDDIO_CAM,
	TEGRA_VDDIO_GMI,
	TEGRA_VDDIO_PEXCTL,
	TEGRA_VDDIO_SDMMC1,
	TEGRA_VDDIO_SDMMC3,
	TEGRA_VDDIO_SDMMC4,
};

struct tegra_pingroup_config {
	int pingroup;
	enum tegra_mux_func	func;
	enum tegra_pullupdown	pupd;
	enum tegra_tristate	tristate;
};

enum tegra_slew {
	TEGRA_SLEW_FASTEST = 0,
	TEGRA_SLEW_FAST,
	TEGRA_SLEW_SLOW,
	TEGRA_SLEW_SLOWEST,
	TEGRA_MAX_SLEW,
};

enum tegra_pull_strength {
	TEGRA_PULL_0 = 0,
	TEGRA_PULL_1,
	TEGRA_PULL_2,
	TEGRA_PULL_3,
	TEGRA_PULL_4,
	TEGRA_PULL_5,
	TEGRA_PULL_6,
	TEGRA_PULL_7,
	TEGRA_PULL_8,
	TEGRA_PULL_9,
	TEGRA_PULL_10,
	TEGRA_PULL_11,
	TEGRA_PULL_12,
	TEGRA_PULL_13,
	TEGRA_PULL_14,
	TEGRA_PULL_15,
	TEGRA_PULL_16,
	TEGRA_PULL_17,
	TEGRA_PULL_18,
	TEGRA_PULL_19,
	TEGRA_PULL_20,
	TEGRA_PULL_21,
	TEGRA_PULL_22,
	TEGRA_PULL_23,
	TEGRA_PULL_24,
	TEGRA_PULL_25,
	TEGRA_PULL_26,
	TEGRA_PULL_27,
	TEGRA_PULL_28,
	TEGRA_PULL_29,
	TEGRA_PULL_30,
	TEGRA_PULL_31,
	TEGRA_MAX_PULL,
};

enum tegra_drive {
	TEGRA_DRIVE_DIV_8 = 0,
	TEGRA_DRIVE_DIV_4,
	TEGRA_DRIVE_DIV_2,
	TEGRA_DRIVE_DIV_1,
	TEGRA_MAX_DRIVE,
};

enum tegra_hsm {
	TEGRA_HSM_DISABLE = 0,
	TEGRA_HSM_ENABLE,
};

enum tegra_schmitt {
	TEGRA_SCHMITT_DISABLE = 0,
	TEGRA_SCHMITT_ENABLE,
};

struct tegra_drive_pingroup_config {
	int pingroup;
	enum tegra_hsm hsm;
	enum tegra_schmitt schmitt;
	enum tegra_drive drive;
	enum tegra_pull_strength pull_down;
	enum tegra_pull_strength pull_up;
	enum tegra_slew slew_rising;
	enum tegra_slew slew_falling;
};

struct tegra_drive_pingroup_desc {
	const char *name;
	s16 reg_bank;
	s16 reg;
};

struct tegra_pingroup_desc {
	const char *name;
	int funcs[4];
	int func_safe;
	int vddio;
	enum tegra_pin_io io_default;
	s16 tri_bank;	/*                                         */
	s16 mux_bank;	/*                                         */
	s16 pupd_bank;	/*                                          */
	s16 tri_reg; 	/*                                              */
	s16 mux_reg;	/*                                             */
	s16 pupd_reg;	/*                                                 */
	s8 tri_bit; 	/*                                             */
	s8 mux_bit;	/*                                            */
	s8 pupd_bit;	/*                                                */
	s8 lock_bit;	/*                                              */
	s8 od_bit;	/*                                            */
	s8 ioreset_bit;	/*                                                  */
};

typedef void (*pinmux_init) (const struct tegra_pingroup_desc **pg,
	int *pg_max, const struct tegra_drive_pingroup_desc **pgdrive,
	int *pgdrive_max);

void tegra20_pinmux_init(const struct tegra_pingroup_desc **pg, int *pg_max,
	const struct tegra_drive_pingroup_desc **pgdrive, int *pgdrive_max);

void tegra30_pinmux_init(const struct tegra_pingroup_desc **pg, int *pg_max,
	const struct tegra_drive_pingroup_desc **pgdrive, int *pgdrive_max);

int tegra_pinmux_set_tristate(int pg, enum tegra_tristate tristate);
int tegra_pinmux_set_pullupdown(int pg, enum tegra_pullupdown pupd);

void tegra_pinmux_config_table(const struct tegra_pingroup_config *config,
	int len);

void tegra_drive_pinmux_config_table(struct tegra_drive_pingroup_config *config,
	int len);
void tegra_pinmux_set_safe_pinmux_table(const struct tegra_pingroup_config *config,
	int len);
void tegra_pinmux_config_pinmux_table(const struct tegra_pingroup_config *config,
	int len);
void tegra_pinmux_config_tristate_table(const struct tegra_pingroup_config *config,
	int len, enum tegra_tristate tristate);
void tegra_pinmux_config_pullupdown_table(const struct tegra_pingroup_config *config,
	int len, enum tegra_pullupdown pupd);
#endif
