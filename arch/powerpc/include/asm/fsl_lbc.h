/* Freescale Local Bus Controller
 *
 * Copyright © 2006-2007, 2010 Freescale Semiconductor
 *
 * Authors: Nick Spence <nick.spence@freescale.com>,
 *          Scott Wood <scottwood@freescale.com>
 *          Jack Lan <jack.lan@freescale.com>
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

#ifndef __ASM_FSL_LBC_H
#define __ASM_FSL_LBC_H

#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/spinlock.h>

struct fsl_lbc_bank {
	__be32 br;             /*                  */
#define BR_BA           0xFFFF8000
#define BR_BA_SHIFT             15
#define BR_PS           0x00001800
#define BR_PS_SHIFT             11
#define BR_PS_8         0x00000800  /*                 */
#define BR_PS_16        0x00001000  /*                  */
#define BR_PS_32        0x00001800  /*                  */
#define BR_DECC         0x00000600
#define BR_DECC_SHIFT            9
#define BR_DECC_OFF     0x00000000  /*                                    */
#define BR_DECC_CHK     0x00000200  /*                                    */
#define BR_DECC_CHK_GEN 0x00000400  /*                                   */
#define BR_WP           0x00000100
#define BR_WP_SHIFT              8
#define BR_MSEL         0x000000E0
#define BR_MSEL_SHIFT            5
#define BR_MS_GPCM      0x00000000  /*      */
#define BR_MS_FCM       0x00000020  /*     */
#define BR_MS_SDRAM     0x00000060  /*       */
#define BR_MS_UPMA      0x00000080  /*      */
#define BR_MS_UPMB      0x000000A0  /*      */
#define BR_MS_UPMC      0x000000C0  /*      */
#define BR_V            0x00000001
#define BR_V_SHIFT               0
#define BR_RES          ~(BR_BA|BR_PS|BR_DECC|BR_WP|BR_MSEL|BR_V)

	__be32 or;             /*                  */
#define OR0 0x5004
#define OR1 0x500C
#define OR2 0x5014
#define OR3 0x501C
#define OR4 0x5024
#define OR5 0x502C
#define OR6 0x5034
#define OR7 0x503C

#define OR_FCM_AM               0xFFFF8000
#define OR_FCM_AM_SHIFT                 15
#define OR_FCM_BCTLD            0x00001000
#define OR_FCM_BCTLD_SHIFT              12
#define OR_FCM_PGS              0x00000400
#define OR_FCM_PGS_SHIFT                10
#define OR_FCM_CSCT             0x00000200
#define OR_FCM_CSCT_SHIFT                9
#define OR_FCM_CST              0x00000100
#define OR_FCM_CST_SHIFT                 8
#define OR_FCM_CHT              0x00000080
#define OR_FCM_CHT_SHIFT                 7
#define OR_FCM_SCY              0x00000070
#define OR_FCM_SCY_SHIFT                 4
#define OR_FCM_SCY_1            0x00000010
#define OR_FCM_SCY_2            0x00000020
#define OR_FCM_SCY_3            0x00000030
#define OR_FCM_SCY_4            0x00000040
#define OR_FCM_SCY_5            0x00000050
#define OR_FCM_SCY_6            0x00000060
#define OR_FCM_SCY_7            0x00000070
#define OR_FCM_RST              0x00000008
#define OR_FCM_RST_SHIFT                 3
#define OR_FCM_TRLX             0x00000004
#define OR_FCM_TRLX_SHIFT                2
#define OR_FCM_EHTR             0x00000002
#define OR_FCM_EHTR_SHIFT                1
};

struct fsl_lbc_regs {
	struct fsl_lbc_bank bank[12];
	u8 res0[0x8];
	__be32 mar;             /*                        */
	u8 res1[0x4];
	__be32 mamr;            /*                      */
#define MxMR_OP_NO	(0 << 28) /*                    */
#define MxMR_OP_WA	(1 << 28) /*               */
#define MxMR_OP_RA	(2 << 28) /*              */
#define MxMR_OP_RP	(3 << 28) /*               */
#define MxMR_MAD	0x3f      /*                   */
	__be32 mbmr;            /*                      */
	__be32 mcmr;            /*                      */
	u8 res2[0x8];
	__be32 mrtpr;           /*                                           */
	__be32 mdr;             /*                     */
	u8 res3[0x4];
	__be32 lsor;            /*                                         */
	__be32 lsdmr;           /*                       */
	u8 res4[0x8];
	__be32 lurt;            /*                     */
	__be32 lsrt;            /*                       */
	u8 res5[0x8];
	__be32 ltesr;           /*                                  */
#define LTESR_BM   0x80000000
#define LTESR_FCT  0x40000000
#define LTESR_PAR  0x20000000
#define LTESR_WP   0x04000000
#define LTESR_ATMW 0x00800000
#define LTESR_ATMR 0x00400000
#define LTESR_CS   0x00080000
#define LTESR_UPM  0x00000002
#define LTESR_CC   0x00000001
#define LTESR_NAND_MASK (LTESR_FCT | LTESR_PAR | LTESR_CC)
#define LTESR_MASK      (LTESR_BM | LTESR_FCT | LTESR_PAR | LTESR_WP \
			 | LTESR_ATMW | LTESR_ATMR | LTESR_CS | LTESR_UPM \
			 | LTESR_CC)
#define LTESR_CLEAR	0xFFFFFFFF
#define LTECCR_CLEAR	0xFFFFFFFF
#define LTESR_STATUS	LTESR_MASK
#define LTEIR_ENABLE	LTESR_MASK
#define LTEDR_ENABLE	0x00000000
	__be32 ltedr;           /*                                   */
	__be32 lteir;           /*                                     */
	__be32 lteatr;          /*                                      */
	__be32 ltear;           /*                                   */
	__be32 lteccr;          /*                               */
	u8 res6[0x8];
	__be32 lbcr;            /*                          */
#define LBCR_LDIS  0x80000000
#define LBCR_LDIS_SHIFT    31
#define LBCR_BCTLC 0x00C00000
#define LBCR_BCTLC_SHIFT   22
#define LBCR_AHD   0x00200000
#define LBCR_LPBSE 0x00020000
#define LBCR_LPBSE_SHIFT   17
#define LBCR_EPAR  0x00010000
#define LBCR_EPAR_SHIFT    16
#define LBCR_BMT   0x0000FF00
#define LBCR_BMT_SHIFT      8
#define LBCR_BMTPS 0x0000000F
#define LBCR_BMTPS_SHIFT    0
#define LBCR_INIT  0x00040000
	__be32 lcrr;            /*                        */
#define LCRR_DBYP    0x80000000
#define LCRR_DBYP_SHIFT      31
#define LCRR_BUFCMDC 0x30000000
#define LCRR_BUFCMDC_SHIFT   28
#define LCRR_ECL     0x03000000
#define LCRR_ECL_SHIFT       24
#define LCRR_EADC    0x00030000
#define LCRR_EADC_SHIFT      16
#define LCRR_CLKDIV  0x0000000F
#define LCRR_CLKDIV_SHIFT     0
	u8 res7[0x8];
	__be32 fmr;             /*                       */
#define FMR_CWTO     0x0000F000
#define FMR_CWTO_SHIFT       12
#define FMR_BOOT     0x00000800
#define FMR_ECCM     0x00000100
#define FMR_AL       0x00000030
#define FMR_AL_SHIFT          4
#define FMR_OP       0x00000003
#define FMR_OP_SHIFT          0
	__be32 fir;             /*                              */
#define FIR_OP0      0xF0000000
#define FIR_OP0_SHIFT        28
#define FIR_OP1      0x0F000000
#define FIR_OP1_SHIFT        24
#define FIR_OP2      0x00F00000
#define FIR_OP2_SHIFT        20
#define FIR_OP3      0x000F0000
#define FIR_OP3_SHIFT        16
#define FIR_OP4      0x0000F000
#define FIR_OP4_SHIFT        12
#define FIR_OP5      0x00000F00
#define FIR_OP5_SHIFT         8
#define FIR_OP6      0x000000F0
#define FIR_OP6_SHIFT         4
#define FIR_OP7      0x0000000F
#define FIR_OP7_SHIFT         0
#define FIR_OP_NOP   0x0	/*                                  */
#define FIR_OP_CA    0x1        /*                              */
#define FIR_OP_PA    0x2        /*                                  */
#define FIR_OP_UA    0x3        /*                            */
#define FIR_OP_CM0   0x4        /*                              */
#define FIR_OP_CM1   0x5        /*                              */
#define FIR_OP_CM2   0x6        /*                              */
#define FIR_OP_CM3   0x7        /*                              */
#define FIR_OP_WB    0x8        /*                                  */
#define FIR_OP_WS    0x9        /*                                 */
#define FIR_OP_RB    0xA        /*                               */
#define FIR_OP_RS    0xB        /*                              */
#define FIR_OP_CW0   0xC        /*                           */
#define FIR_OP_CW1   0xD        /*                           */
#define FIR_OP_RBW   0xE        /*                           */
#define FIR_OP_RSW   0xE        /*                             */
	__be32 fcr;             /*                          */
#define FCR_CMD0     0xFF000000
#define FCR_CMD0_SHIFT       24
#define FCR_CMD1     0x00FF0000
#define FCR_CMD1_SHIFT       16
#define FCR_CMD2     0x0000FF00
#define FCR_CMD2_SHIFT        8
#define FCR_CMD3     0x000000FF
#define FCR_CMD3_SHIFT        0
	__be32 fbar;            /*                                */
#define FBAR_BLK     0x00FFFFFF
	__be32 fpar;            /*                               */
#define FPAR_SP_PI   0x00007C00
#define FPAR_SP_PI_SHIFT     10
#define FPAR_SP_MS   0x00000200
#define FPAR_SP_CI   0x000001FF
#define FPAR_SP_CI_SHIFT      0
#define FPAR_LP_PI   0x0003F000
#define FPAR_LP_PI_SHIFT     12
#define FPAR_LP_MS   0x00000800
#define FPAR_LP_CI   0x000007FF
#define FPAR_LP_CI_SHIFT      0
	__be32 fbcr;            /*                             */
#define FBCR_BC      0x00000FFF
};

/*
                   
 */
struct fsl_upm {
	__be32 __iomem *mxmr;
	int width;
};

extern u32 fsl_lbc_addr(phys_addr_t addr_base);
extern int fsl_lbc_find(phys_addr_t addr_base);
extern int fsl_upm_find(phys_addr_t addr_base, struct fsl_upm *upm);

/* 
                                                       
                                                                   
                                                                 
  
                                                                         
                                                          
 */
static inline void fsl_upm_start_pattern(struct fsl_upm *upm, u8 pat_offset)
{
	clrsetbits_be32(upm->mxmr, MxMR_MAD, MxMR_OP_RP | pat_offset);
}

/* 
                                                   
                                                                   
  
                                                     
 */
static inline void fsl_upm_end_pattern(struct fsl_upm *upm)
{
	clrbits32(upm->mxmr, MxMR_OP_RP);

	while (in_be32(upm->mxmr) & MxMR_OP_RP)
		cpu_relax();
}

/*                                    */

struct fsl_lbc_ctrl {
	/*             */
	struct device			*dev;
	struct fsl_lbc_regs __iomem	*regs;
	int				irq;
	wait_queue_head_t		irq_wait;
	spinlock_t			lock;
	void				*nand;

	/*                                       */
	unsigned int			irq_status;

#ifdef CONFIG_SUSPEND
	/*                                        */
	struct fsl_lbc_regs		*saved_regs;
#endif
};

extern int fsl_upm_run_pattern(struct fsl_upm *upm, void __iomem *io_base,
			       u32 mar);
extern struct fsl_lbc_ctrl *fsl_lbc_ctrl_dev;

#endif /*                 */
