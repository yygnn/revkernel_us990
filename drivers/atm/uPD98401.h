/*                                                          */
 
/*                                              */
 

#ifndef DRIVERS_ATM_uPD98401_H
#define DRIVERS_ATM_uPD98401_H


#define MAX_CRAM_SIZE	(1 << 18)	/*            */
#define RAM_INCREMENT	1024		/*                          */

#define uPD98401_PORTS	0x24		/*                 */


/*
           
 */

#define uPD98401_OPEN_CHAN	0x20000000 /*              */
#define uPD98401_CHAN_ADDR	0x0003fff8 /*                 */
#define uPD98401_CHAN_ADDR_SHIFT 3
#define uPD98401_CLOSE_CHAN	0x24000000 /*               */
#define uPD98401_CHAN_RT	0x02000000 /*                    */
#define uPD98401_DEACT_CHAN	0x28000000 /*                    */
#define uPD98401_TX_READY	0x30000000 /*          */
#define uPD98401_ADD_BAT	0x34000000 /*             */
#define uPD98401_POOL		0x000f0000 /*             */
#define uPD98401_POOL_SHIFT	16
#define uPD98401_POOL_NUMBAT	0x0000ffff /*                   */
#define uPD98401_NOP		0x3f000000 /*     */
#define uPD98401_IND_ACC	0x00000000 /*                 */
#define uPD98401_IA_RW		0x10000000 /*                       */
#define uPD98401_IA_B3		0x08000000 /*                       */
#define uPD98401_IA_B2		0x04000000
#define uPD98401_IA_B1		0x02000000
#define uPD98401_IA_B0		0x01000000
#define uPD98401_IA_BALL	0x0f000000 /*                  */
#define uPD98401_IA_TGT		0x000c0000 /*        */
#define uPD98401_IA_TGT_SHIFT	18
#define uPD98401_IA_TGT_CM	0	   /*                  */
#define uPD98401_IA_TGT_SAR	1	   /*                      */
#define uPD98401_IA_TGT_PHY	3	   /*                */
#define uPD98401_IA_ADDR	0x0003ffff

/*
                          
 */

#define uPD98401_BUSY		0x80000000 /*             */
#define uPD98401_LOCKED		0x40000000 /*                            */

/*
              
 */

/*                                  */
#define uPD98401_AAL5_UINFO	0xffff0000 /*                           */
#define uPD98401_AAL5_UINFO_SHIFT 16
#define uPD98401_AAL5_SIZE	0x0000ffff /*                          */
#define uPD98401_AAL5_CHAN	0x7fff0000 /*                */
#define uPD98401_AAL5_CHAN_SHIFT	16
#define uPD98401_AAL5_ERR	0x00008000 /*                  */
#define uPD98401_AAL5_CI	0x00004000 /*                       */
#define uPD98401_AAL5_CLP	0x00002000 /*                           */
#define uPD98401_AAL5_ES	0x00000f00 /*              */
#define uPD98401_AAL5_ES_SHIFT	8
#define uPD98401_AAL5_ES_NONE	0	   /*          */
#define uPD98401_AAL5_ES_FREE	1	   /*                             */
#define uPD98401_AAL5_ES_FIFO	2	   /*                       */
#define uPD98401_AAL5_ES_TOOBIG	3	   /*                          */
#define uPD98401_AAL5_ES_CRC	4	   /*           */
#define uPD98401_AAL5_ES_ABORT	5	   /*            */
#define uPD98401_AAL5_ES_LENGTH	6	   /*                    */
#define uPD98401_AAL5_ES_T1	7	   /*                    */
#define uPD98401_AAL5_ES_DEACT	8	   /*                             */
#define uPD98401_AAL5_POOL	0x0000001f /*                         */

/*                     */
#define uPD98401_RAW_UINFO	uPD98401_AAL5_UINFO
#define uPD98401_RAW_UINFO_SHIFT uPD98401_AAL5_UINFO_SHIFT
#define uPD98401_RAW_HEC	0x000000ff /*     */
#define uPD98401_RAW_CHAN	uPD98401_AAL5_CHAN
#define uPD98401_RAW_CHAN_SHIFT uPD98401_AAL5_CHAN_SHIFT

/*                     */
#define uPD98401_TXI_CONN	0x7fff0000 /*                   */
#define uPD98401_TXI_CONN_SHIFT	16
#define uPD98401_TXI_ACTIVE	0x00008000 /*                        */
#define uPD98401_TXI_PQP	0x00007fff /*                      */

/*
                                 
 */

#define uPD98401_GMR	0x00	/*                       */
#define uPD98401_GSR	0x01	/*                         */
#define uPD98401_IMR	0x02	/*                         */
#define uPD98401_RQU	0x03	/*                        */
#define uPD98401_RQA	0x04	/*                     */
#define uPD98401_ADDR	0x05	/*                    */
#define uPD98401_VER	0x06	/*                */
#define uPD98401_SWR	0x07	/*                */
#define uPD98401_CMR	0x08	/*                  */
#define uPD98401_CMR_L	0x09	/*                                  */
#define uPD98401_CER	0x0a	/*                            */
#define uPD98401_CER_L	0x0b	/*                                 */

#define uPD98401_MSH(n) (0x10+(n))	/*                              */
#define uPD98401_MSL(n) (0x14+(n))	/*                              */
#define uPD98401_MBA(n) (0x18+(n))	/*                          */
#define uPD98401_MTA(n) (0x1c+(n))	/*                        */
#define uPD98401_MWA(n) (0x20+(n))	/*                         */

/*                */
#define uPD98401_GMR_ONE	0x80000000 /*                    */
#define uPD98401_GMR_SLM	0x40000000 /*                               */
#define uPD98401_GMR_CPE	0x00008000 /*                              */
#define uPD98401_GMR_LP		0x00004000 /*          */
#define uPD98401_GMR_WA		0x00002000 /*                           */
#define uPD98401_GMR_RA		0x00001000 /*                      */
#define uPD98401_GMR_SZ		0x00000f00 /*                   */
#define uPD98401_BURST16	0x00000800 /*               */
#define uPD98401_BURST8		0x00000400 /*               */
#define uPD98401_BURST4		0x00000200 /*               */
#define uPD98401_BURST2		0x00000100 /*               */
#define uPD98401_GMR_AD		0x00000080 /*                                    */
#define uPD98401_GMR_BO		0x00000040 /*                              */
#define uPD98401_GMR_PM		0x00000020 /*                                 */
#define uPD98401_GMR_PC		0x00000010 /*                                 */
#define uPD98401_GMR_BPE	0x00000008 /*                   */
#define uPD98401_GMR_DR		0x00000004 /*                                 */
#define uPD98401_GMR_SE		0x00000002 /*                */
#define uPD98401_GMR_RE		0x00000001 /*                 */

/*                                */
#define uPD98401_INT_PI		0x80000000 /*               */
#define uPD98401_INT_RQA	0x40000000 /*                     */
#define uPD98401_INT_RQU	0x20000000 /*                        */
#define uPD98401_INT_RD		0x10000000 /*                      */
#define uPD98401_INT_SPE	0x08000000 /*                     */
#define uPD98401_INT_CPE	0x04000000 /*                             */
#define uPD98401_INT_SBE	0x02000000 /*                  */
#define uPD98401_INT_IND	0x01000000 /*                     */
#define uPD98401_INT_RCR	0x0000ff00 /*                   */
#define uPD98401_INT_RCR_SHIFT	8
#define uPD98401_INT_MF		0x000000f0 /*              */
#define uPD98401_INT_MF_SHIFT	4
#define uPD98401_INT_MM		0x0000000f /*                  */

/*                */
#define uPD98401_MAJOR		0x0000ff00 /*                */
#define uPD98401_MAJOR_SHIFT	8
#define uPD98401_MINOR		0x000000ff /*                */

/*
                                   
 */

#define uPD98401_IM(n)	(0x40000+(n))	/*                     */
#define uPD98401_X(n)	(0x40010+(n))	/*               */
#define uPD98401_Y(n)	(0x40020+(n))	/*               */
#define uPD98401_PC(n)	(0x40030+(n))	/*                           */
#define uPD98401_PS(n)	(0x40040+(n))	/*                                 */

/*             */
#define uPD98401_IM_I		0xff000000 /*   */
#define uPD98401_IM_I_SHIFT	24
#define uPD98401_IM_M		0x00ffffff /*   */

/*             */
#define uPD98401_PC_P		0xff000000 /*   */
#define uPD98401_PC_P_SHIFT	24
#define uPD98401_PC_C		0x00ff0000 /*   */
#define uPD98401_PC_C_SHIFT	16
#define uPD98401_PC_p		0x0000ff00 /*   */
#define uPD98401_PC_p_SHIFT	8
#define uPD98401_PC_c		0x000000ff /*   */

/*             */
#define uPD98401_PS_PRIO	0xf0	/*                                 */
#define uPD98401_PS_PRIO_SHIFT	4
#define uPD98401_PS_S		0x08	/*                             */
#define uPD98401_PS_R		0x04	/*                        */
#define uPD98401_PS_A		0x02	/*                   */
#define uPD98401_PS_E		0x01	/*         */

#define uPD98401_TOS	0x40100	/*                                     */
#define uPD98401_SMA	0x40200	/*                                      */
#define uPD98401_PMA	0x40201	/*                                           */
#define uPD98401_T1R	0x40300	/*             */
#define uPD98401_VRR	0x40301	/*                                           */
#define uPD98401_TSR	0x40302	/*                     */

/*                   */
#define uPD98401_VRR_SDM	0x80000000 /*               */
#define uPD98401_VRR_SHIFT	0x000f0000 /*               */
#define uPD98401_VRR_SHIFT_SHIFT 16
#define uPD98401_VRR_MASK	0x0000ffff /*              */

/*
                       
 */

#define uPD98401_TXPD_SIZE	16	   /*                            */

#define uPD98401_TXPD_V		0x80000000 /*           */
#define uPD98401_TXPD_DP	0x40000000 /*                               */
#define uPD98401_TXPD_SM	0x20000000 /*                            */
#define uPD98401_TXPD_CLPM	0x18000000 /*          */
#define uPD98401_CLPM_0		0	   /*            */
#define uPD98401_CLPM_1		3	   /*            */
#define uPD98401_CLPM_LAST	1	   /*                         */
#define uPD98401_TXPD_CLPM_SHIFT 27
#define uPD98401_TXPD_PTI	0x07000000 /*             */
#define uPD98401_TXPD_PTI_SHIFT	24
#define uPD98401_TXPD_GFC	0x00f00000 /*             */
#define uPD98401_TXPD_GFC_SHIFT	20
#define uPD98401_TXPD_C10	0x00040000 /*               */
#define uPD98401_TXPD_AAL5	0x00020000 /*                 */
#define uPD98401_TXPD_MB	0x00010000 /*                   */
#define uPD98401_TXPD_UU	0x0000ff00 /*         */
#define uPD98401_TXPD_UU_SHIFT	8
#define uPD98401_TXPD_CPI	0x000000ff /*     */

/*
                       
 */

#define uPD98401_TXBD_SIZE	8	   /*                            */

#define uPD98401_TXBD_LAST	0x80000000 /*                       */

/*
              
 */

/*                                                              */
#define uPD98401_TXVC_L		0x80000000 /*             */
#define uPD98401_TXVC_SHP	0x0f000000 /*               */
#define uPD98401_TXVC_SHP_SHIFT	24
#define uPD98401_TXVC_VPI	0x00ff0000 /*     */
#define uPD98401_TXVC_VPI_SHIFT	16
#define uPD98401_TXVC_VCI	0x0000ffff /*     */
#define uPD98401_TXVC_QRP	6	   /*                                 */

/*
                                  
 */

#define uPD98401_RXFP_ALERT	0x70000000 /*                */
#define uPD98401_RXFP_ALERT_SHIFT 28
#define uPD98401_RXFP_BFSZ	0x0f000000 /*                     */
#define uPD98401_RXFP_BFSZ_SHIFT 24
#define uPD98401_RXFP_BTSZ	0x00ff0000 /*                 */
#define uPD98401_RXFP_BTSZ_SHIFT 16
#define uPD98401_RXFP_REMAIN	0x0000ffff /*                           */

/*
              
 */

#define uPD98401_RXVC_BTSZ	0xff000000 /*                                 */
#define uPD98401_RXVC_BTSZ_SHIFT 24
#define uPD98401_RXVC_MB	0x00200000 /*                   */
#define uPD98401_RXVC_POOL	0x001f0000 /*                         */
#define uPD98401_RXVC_POOL_SHIFT 16
#define uPD98401_RXVC_UINFO	0x0000ffff /*                           */
#define uPD98401_RXVC_T1	0xffff0000 /*              */
#define uPD98401_RXVC_T1_SHIFT	16
#define uPD98401_RXVC_PR	0x00008000 /*                             */
#define uPD98401_RXVC_DR	0x00004000 /*           */
#define uPD98401_RXVC_OD	0x00001000 /*                */
#define uPD98401_RXVC_AR	0x00000800 /*                             */
#define uPD98401_RXVC_MAXSEG	0x000007ff /*                                */
#define uPD98401_RXVC_REM	0xfffe0000 /*                                */
#define uPD98401_RXVC_REM_SHIFT	17
#define uPD98401_RXVC_CLP	0x00010000 /*              */
#define uPD98401_RXVC_BFA	0x00008000 /*                 */
#define uPD98401_RXVC_BTA	0x00004000 /*                */
#define uPD98401_RXVC_CI	0x00002000 /*                       */
#define uPD98401_RXVC_DD	0x00001000 /*                         */
#define uPD98401_RXVC_DP	0x00000800 /*           */
#define uPD98401_RXVC_CURSEG	0x000007ff /*                       */

/*
                  
 */

#define uPD98401_RXLT_ENBL	0x8000	   /*        */

#endif
