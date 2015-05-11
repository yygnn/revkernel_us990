#ifndef _ASM_POWERPC_KEYLARGO_H
#define _ASM_POWERPC_KEYLARGO_H
#ifdef __KERNEL__
/*
                                                                        
  
 */

/*                                                          
                                                             
                                                         
 */
#define KL_PANGEA_REV		0x100

/*                                                */
#define KEYLARGO_MBCR		0x34	/*                                   */
#define KEYLARGO_FCR0		0x38
#define KEYLARGO_FCR1		0x3c
#define KEYLARGO_FCR2		0x40
#define KEYLARGO_FCR3		0x44
#define KEYLARGO_FCR4		0x48
#define KEYLARGO_FCR5		0x4c	/*             */

/*                    */
#define K2_FCR6			0x34
#define K2_FCR7			0x30
#define K2_FCR8			0x2c
#define K2_FCR9			0x28
#define K2_FCR10		0x24

/*                */
#define KEYLARGO_GPIO_LEVELS0		0x50
#define KEYLARGO_GPIO_LEVELS1		0x54
#define KEYLARGO_GPIO_EXTINT_0		0x58
#define KEYLARGO_GPIO_EXTINT_CNT	18
#define KEYLARGO_GPIO_0			0x6A
#define KEYLARGO_GPIO_CNT		17
#define KEYLARGO_GPIO_EXTINT_DUAL_EDGE	0x80
#define KEYLARGO_GPIO_OUTPUT_ENABLE	0x04
#define KEYLARGO_GPIO_OUTOUT_DATA	0x01
#define KEYLARGO_GPIO_INPUT_DATA	0x02

/*                                               */
#define K2_GPIO_EXTINT_0		0x58
#define K2_GPIO_EXTINT_CNT		51

/*                    */

#define KL_GPIO_MODEM_RESET		(KEYLARGO_GPIO_0+0x03)
#define KL_GPIO_MODEM_POWER		(KEYLARGO_GPIO_0+0x02) /*        */

#define KL_GPIO_SOUND_POWER		(KEYLARGO_GPIO_0+0x05)

/*                                                              
                                                             
                          
 */
#define KL_GPIO_FW_CABLE_POWER		(KEYLARGO_GPIO_0+0x09)
#define KL_GPIO_TB_ENABLE		(KEYLARGO_GPIO_0+0x09)

#define KL_GPIO_ETH_PHY_RESET		(KEYLARGO_GPIO_0+0x10)

#define KL_GPIO_EXTINT_CPU1		(KEYLARGO_GPIO_0+0x0a)
#define KL_GPIO_EXTINT_CPU1_ASSERT	0x04
#define KL_GPIO_EXTINT_CPU1_RELEASE	0x38

#define KL_GPIO_RESET_CPU0		(KEYLARGO_GPIO_EXTINT_0+0x03)
#define KL_GPIO_RESET_CPU1		(KEYLARGO_GPIO_EXTINT_0+0x04)
#define KL_GPIO_RESET_CPU2		(KEYLARGO_GPIO_EXTINT_0+0x0f)
#define KL_GPIO_RESET_CPU3		(KEYLARGO_GPIO_EXTINT_0+0x10)

#define KL_GPIO_PMU_MESSAGE_IRQ		(KEYLARGO_GPIO_EXTINT_0+0x09)
#define KL_GPIO_PMU_MESSAGE_BIT		KEYLARGO_GPIO_INPUT_DATA

#define KL_GPIO_MEDIABAY_IRQ		(KEYLARGO_GPIO_EXTINT_0+0x0e)

#define KL_GPIO_AIRPORT_0		(KEYLARGO_GPIO_EXTINT_0+0x0a)
#define KL_GPIO_AIRPORT_1		(KEYLARGO_GPIO_EXTINT_0+0x0d)
#define KL_GPIO_AIRPORT_2		(KEYLARGO_GPIO_0+0x0d)
#define KL_GPIO_AIRPORT_3		(KEYLARGO_GPIO_0+0x0e)
#define KL_GPIO_AIRPORT_4		(KEYLARGO_GPIO_0+0x0f)

/*
                                                                    
                    
 */
#define KL_MBCR_MB0_PCI_ENABLE		0x00000800	/*         */
#define KL_MBCR_MB0_IDE_ENABLE		0x00001000
#define KL_MBCR_MB0_FLOPPY_ENABLE	0x00002000	/*         */
#define KL_MBCR_MB0_SOUND_ENABLE	0x00004000	/*        */
#define KL_MBCR_MB0_DEV_MASK		0x00007800
#define KL_MBCR_MB0_DEV_POWER		0x00000400
#define KL_MBCR_MB0_DEV_RESET		0x00000200
#define KL_MBCR_MB0_ENABLE		0x00000100
#define KL_MBCR_MB1_PCI_ENABLE		0x08000000	/*         */
#define KL_MBCR_MB1_IDE_ENABLE		0x10000000
#define KL_MBCR_MB1_FLOPPY_ENABLE	0x20000000	/*         */
#define KL_MBCR_MB1_SOUND_ENABLE	0x40000000	/*        */
#define KL_MBCR_MB1_DEV_MASK		0x78000000
#define KL_MBCR_MB1_DEV_POWER		0x04000000
#define KL_MBCR_MB1_DEV_RESET		0x02000000
#define KL_MBCR_MB1_ENABLE		0x01000000

#define KL0_SCC_B_INTF_ENABLE		0x00000001	/*           */
#define KL0_SCC_A_INTF_ENABLE		0x00000002
#define KL0_SCC_SLOWPCLK		0x00000004
#define KL0_SCC_RESET			0x00000008
#define KL0_SCCA_ENABLE			0x00000010
#define KL0_SCCB_ENABLE			0x00000020
#define KL0_SCC_CELL_ENABLE		0x00000040
#define KL0_IRDA_HIGH_BAND		0x00000100	/*           */
#define KL0_IRDA_SOURCE2_SEL		0x00000200	/*           */
#define KL0_IRDA_SOURCE1_SEL		0x00000400	/*           */
#define KL0_PG_USB0_PMI_ENABLE		0x00000400	/*                        */
#define KL0_IRDA_RESET			0x00000800	/*           */
#define KL0_PG_USB0_REF_SUSPEND_SEL	0x00000800	/*                        */
#define KL0_IRDA_DEFAULT1		0x00001000	/*           */
#define KL0_PG_USB0_REF_SUSPEND		0x00001000	/*                        */
#define KL0_IRDA_DEFAULT0		0x00002000	/*           */
#define KL0_PG_USB0_PAD_SUSPEND		0x00002000	/*                        */
#define KL0_IRDA_FAST_CONNECT		0x00004000	/*           */
#define KL0_PG_USB1_PMI_ENABLE		0x00004000	/*                        */
#define KL0_IRDA_ENABLE			0x00008000	/*           */
#define KL0_PG_USB1_REF_SUSPEND_SEL	0x00008000	/*                        */
#define KL0_IRDA_CLK32_ENABLE		0x00010000	/*           */
#define KL0_PG_USB1_REF_SUSPEND		0x00010000	/*                        */
#define KL0_IRDA_CLK19_ENABLE		0x00020000	/*           */
#define KL0_PG_USB1_PAD_SUSPEND		0x00020000	/*                        */
#define KL0_USB0_PAD_SUSPEND0		0x00040000
#define KL0_USB0_PAD_SUSPEND1		0x00080000
#define KL0_USB0_CELL_ENABLE		0x00100000
#define KL0_USB1_PAD_SUSPEND0		0x00400000
#define KL0_USB1_PAD_SUSPEND1		0x00800000
#define KL0_USB1_CELL_ENABLE		0x01000000
#define KL0_USB_REF_SUSPEND		0x10000000	/*           */

#define KL0_SERIAL_ENABLE		(KL0_SCC_B_INTF_ENABLE | \
					KL0_SCC_SLOWPCLK | \
					KL0_SCC_CELL_ENABLE | KL0_SCCA_ENABLE)

#define KL1_USB2_PMI_ENABLE		0x00000001	/*               */
#define KL1_AUDIO_SEL_22MCLK		0x00000002	/*                */
#define KL1_USB2_REF_SUSPEND_SEL	0x00000002	/*               */
#define KL1_USB2_REF_SUSPEND		0x00000004	/*               */
#define KL1_AUDIO_CLK_ENABLE_BIT	0x00000008	/*                */
#define KL1_USB2_PAD_SUSPEND_SEL	0x00000008	/*               */
#define KL1_USB2_PAD_SUSPEND0		0x00000010	/*               */
#define KL1_AUDIO_CLK_OUT_ENABLE	0x00000020	/*                */
#define KL1_USB2_PAD_SUSPEND1		0x00000020	/*               */
#define KL1_AUDIO_CELL_ENABLE		0x00000040	/*                */
#define KL1_USB2_CELL_ENABLE		0x00000040	/*               */
#define KL1_AUDIO_CHOOSE		0x00000080	/*                */
#define KL1_I2S0_CHOOSE			0x00000200	/*         */
#define KL1_I2S0_CELL_ENABLE		0x00000400
#define KL1_I2S0_CLK_ENABLE_BIT		0x00001000
#define KL1_I2S0_ENABLE			0x00002000
#define KL1_I2S1_CELL_ENABLE		0x00020000
#define KL1_I2S1_CLK_ENABLE_BIT		0x00080000
#define KL1_I2S1_ENABLE			0x00100000
#define KL1_EIDE0_ENABLE		0x00800000	/*                  */
#define KL1_EIDE0_RESET_N		0x01000000	/*                  */
#define KL1_EIDE1_ENABLE		0x04000000	/*         */
#define KL1_EIDE1_RESET_N		0x08000000	/*         */
#define KL1_UIDE_ENABLE			0x20000000	/*                */
#define KL1_UIDE_RESET_N		0x40000000	/*                */

#define KL2_IOBUS_ENABLE		0x00000002
#define KL2_SLEEP_STATE_BIT		0x00000100	/*         */
#define KL2_PG_STOP_ALL_CLOCKS		0x00000100	/*             */
#define KL2_MPIC_ENABLE			0x00020000
#define KL2_CARDSLOT_RESET		0x00040000	/*                      */
#define KL2_ALT_DATA_OUT		0x02000000	/*             */
#define KL2_MEM_IS_BIG			0x04000000
#define KL2_CARDSEL_16			0x08000000

#define KL3_SHUTDOWN_PLL_TOTAL		0x00000001	/*                */
#define KL3_SHUTDOWN_PLLKW6		0x00000002	/*                */
#define KL3_IT_SHUTDOWN_PLL3		0x00000002	/*               */
#define KL3_SHUTDOWN_PLLKW4		0x00000004	/*                */
#define KL3_IT_SHUTDOWN_PLL2		0x00000004	/*               */
#define KL3_SHUTDOWN_PLLKW35		0x00000008	/*                */
#define KL3_IT_SHUTDOWN_PLL1		0x00000008	/*               */
#define KL3_SHUTDOWN_PLLKW12		0x00000010	/*         */
#define KL3_IT_ENABLE_PLL3_SHUTDOWN	0x00000010	/*               */
#define KL3_PLL_RESET			0x00000020	/*                */
#define KL3_IT_ENABLE_PLL2_SHUTDOWN	0x00000020	/*               */
#define KL3_IT_ENABLE_PLL1_SHUTDOWN	0x00000010	/*               */
#define KL3_SHUTDOWN_PLL2X		0x00000080	/*         */
#define KL3_CLK66_ENABLE		0x00000100	/*         */
#define KL3_CLK49_ENABLE		0x00000200
#define KL3_CLK45_ENABLE		0x00000400
#define KL3_CLK31_ENABLE		0x00000800	/*                */
#define KL3_TIMER_CLK18_ENABLE		0x00001000
#define KL3_I2S1_CLK18_ENABLE		0x00002000
#define KL3_I2S0_CLK18_ENABLE		0x00004000
#define KL3_VIA_CLK16_ENABLE		0x00008000	/*                */
#define KL3_IT_VIA_CLK32_ENABLE		0x00008000	/*               */
#define KL3_STOPPING33_ENABLED		0x00080000	/*         */
#define KL3_PG_PLL_ENABLE_TEST		0x00080000	/*             */

/*                              */
#define KL3_IT_PORT_WAKEUP_ENABLE(p)		(0x00080000 << ((p)<<3))
#define KL3_IT_PORT_RESUME_WAKE_EN(p)		(0x00040000 << ((p)<<3))
#define KL3_IT_PORT_CONNECT_WAKE_EN(p)		(0x00020000 << ((p)<<3))
#define KL3_IT_PORT_DISCONNECT_WAKE_EN(p)	(0x00010000 << ((p)<<3))
#define KL3_IT_PORT_RESUME_STAT(p)		(0x00300000 << ((p)<<3))
#define KL3_IT_PORT_CONNECT_STAT(p)		(0x00200000 << ((p)<<3))
#define KL3_IT_PORT_DISCONNECT_STAT(p)		(0x00100000 << ((p)<<3))

/*                                    */
#define KL4_PORT_WAKEUP_ENABLE(p)	(0x00000008 << ((p)<<3))
#define KL4_PORT_RESUME_WAKE_EN(p)	(0x00000004 << ((p)<<3))
#define KL4_PORT_CONNECT_WAKE_EN(p)	(0x00000002 << ((p)<<3))
#define KL4_PORT_DISCONNECT_WAKE_EN(p)	(0x00000001 << ((p)<<3))
#define KL4_PORT_RESUME_STAT(p)		(0x00000040 << ((p)<<3))
#define KL4_PORT_CONNECT_STAT(p)	(0x00000020 << ((p)<<3))
#define KL4_PORT_DISCONNECT_STAT(p)	(0x00000010 << ((p)<<3))

/*                          */
#define KL5_VIA_USE_CLK31		0000000001	/*             */
#define KL5_SCC_USE_CLK31		0x00000002	/*             */
#define KL5_PWM_CLK32_EN		0x00000004
#define KL5_CLK3_68_EN			0x00000010
#define KL5_CLK32_EN			0x00000020


/*                */
#define K2_FCR0_USB0_SWRESET		0x00200000
#define K2_FCR0_USB1_SWRESET		0x02000000
#define K2_FCR0_RING_PME_DISABLE	0x08000000

#define K2_FCR1_PCI1_BUS_RESET_N	0x00000010
#define K2_FCR1_PCI1_SLEEP_RESET_EN	0x00000020
#define K2_FCR1_I2S0_CELL_ENABLE	0x00000400
#define K2_FCR1_I2S0_RESET		0x00000800
#define K2_FCR1_I2S0_CLK_ENABLE_BIT	0x00001000
#define K2_FCR1_I2S0_ENABLE    		0x00002000
#define K2_FCR1_PCI1_CLK_ENABLE		0x00004000
#define K2_FCR1_FW_CLK_ENABLE		0x00008000
#define K2_FCR1_FW_RESET_N		0x00010000
#define K2_FCR1_I2S1_CELL_ENABLE	0x00020000
#define K2_FCR1_I2S1_CLK_ENABLE_BIT	0x00080000
#define K2_FCR1_I2S1_ENABLE		0x00100000
#define K2_FCR1_GMAC_CLK_ENABLE		0x00400000
#define K2_FCR1_GMAC_POWER_DOWN		0x00800000
#define K2_FCR1_GMAC_RESET_N		0x01000000
#define K2_FCR1_SATA_CLK_ENABLE		0x02000000
#define K2_FCR1_SATA_POWER_DOWN		0x04000000
#define K2_FCR1_SATA_RESET_N		0x08000000
#define K2_FCR1_UATA_CLK_ENABLE		0x10000000
#define K2_FCR1_UATA_RESET_N		0x40000000
#define K2_FCR1_UATA_CHOOSE_CLK66	0x80000000

/*                    */
#define SH_FCR1_I2S2_CELL_ENABLE	0x00000010
#define SH_FCR1_I2S2_CLK_ENABLE_BIT	0x00000040
#define SH_FCR1_I2S2_ENABLE		0x00000080
#define SH_FCR3_I2S2_CLK18_ENABLE	0x00008000

#endif /*            */
#endif /*                         */
