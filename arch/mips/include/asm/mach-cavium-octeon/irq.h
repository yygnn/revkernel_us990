/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2004-2008 Cavium Networks
 */
#ifndef __OCTEON_IRQ_H__
#define __OCTEON_IRQ_H__

#define NR_IRQS OCTEON_IRQ_LAST
#define MIPS_CPU_IRQ_BASE OCTEON_IRQ_SW0

enum octeon_irq {
/*                                                       */
	OCTEON_IRQ_SW0 = 1,
	OCTEON_IRQ_SW1,
/*                              */
	OCTEON_IRQ_5 = 6,
	OCTEON_IRQ_PERF,
	OCTEON_IRQ_TIMER,
/*                         */
	OCTEON_IRQ_WORKQ0,
	OCTEON_IRQ_GPIO0 = OCTEON_IRQ_WORKQ0 + 16,
	OCTEON_IRQ_WDOG0 = OCTEON_IRQ_GPIO0 + 16,
	OCTEON_IRQ_WDOG15 = OCTEON_IRQ_WDOG0 + 15,
	OCTEON_IRQ_MBOX0 = OCTEON_IRQ_WDOG0 + 16,
	OCTEON_IRQ_MBOX1,
	OCTEON_IRQ_UART0,
	OCTEON_IRQ_UART1,
	OCTEON_IRQ_UART2,
	OCTEON_IRQ_PCI_INT0,
	OCTEON_IRQ_PCI_INT1,
	OCTEON_IRQ_PCI_INT2,
	OCTEON_IRQ_PCI_INT3,
	OCTEON_IRQ_PCI_MSI0,
	OCTEON_IRQ_PCI_MSI1,
	OCTEON_IRQ_PCI_MSI2,
	OCTEON_IRQ_PCI_MSI3,

	OCTEON_IRQ_TWSI,
	OCTEON_IRQ_TWSI2,
	OCTEON_IRQ_RML,
	OCTEON_IRQ_TRACE0,
	OCTEON_IRQ_GMX_DRP0 = OCTEON_IRQ_TRACE0 + 4,
	OCTEON_IRQ_IPD_DRP = OCTEON_IRQ_GMX_DRP0 + 5,
	OCTEON_IRQ_KEY_ZERO,
	OCTEON_IRQ_TIMER0,
	OCTEON_IRQ_TIMER1,
	OCTEON_IRQ_TIMER2,
	OCTEON_IRQ_TIMER3,
	OCTEON_IRQ_USB0,
	OCTEON_IRQ_USB1,
	OCTEON_IRQ_PCM,
	OCTEON_IRQ_MPI,
	OCTEON_IRQ_POWIQ,
	OCTEON_IRQ_IPDPPTHR,
	OCTEON_IRQ_MII0,
	OCTEON_IRQ_MII1,
	OCTEON_IRQ_BOOTDMA,

	OCTEON_IRQ_NAND,
	OCTEON_IRQ_MIO,		/*                         */
	OCTEON_IRQ_IOB,		/*                        */
	OCTEON_IRQ_FPA,		/*                        */
	OCTEON_IRQ_POW,		/*                        */
	OCTEON_IRQ_L2C,		/*                         */
	OCTEON_IRQ_IPD,		/*                        */
	OCTEON_IRQ_PIP,		/*                        */
	OCTEON_IRQ_PKO,		/*                          */
	OCTEON_IRQ_ZIP,		/*                      */
	OCTEON_IRQ_TIM,		/*                          */
	OCTEON_IRQ_RAD,		/*                          */
	OCTEON_IRQ_KEY,		/*                        */
	OCTEON_IRQ_DFA,		/*                */
	OCTEON_IRQ_USBCTL,	/*                          */
	OCTEON_IRQ_SLI,		/*                        */
	OCTEON_IRQ_DPI,		/*                        */
	OCTEON_IRQ_AGX0,	/*                                */
	OCTEON_IRQ_AGL  = OCTEON_IRQ_AGX0 + 5,
	OCTEON_IRQ_PTP,
	OCTEON_IRQ_PEM0,
	OCTEON_IRQ_PEM1,
	OCTEON_IRQ_SRIO0,
	OCTEON_IRQ_SRIO1,
	OCTEON_IRQ_LMC0,
	OCTEON_IRQ_DFM = OCTEON_IRQ_LMC0 + 4,		/*                */
	OCTEON_IRQ_RST,
};

#ifdef CONFIG_PCI_MSI
/*                                              */
#define OCTEON_IRQ_MSI_BIT0	(OCTEON_IRQ_RST + 1)

#define OCTEON_IRQ_MSI_LAST      (OCTEON_IRQ_MSI_BIT0 + 255)
#define OCTEON_IRQ_LAST          (OCTEON_IRQ_MSI_LAST + 1)
#else
#define OCTEON_IRQ_LAST         (OCTEON_IRQ_RST + 1)
#endif

#endif
