/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (c) 2003-2005 Silicon Graphics, Inc. All rights reserved.
 */

#ifndef _ASM_IA64_SN_TIO_CA_AGP_PROVIDER_H
#define _ASM_IA64_SN_TIO_CA_AGP_PROVIDER_H

#include <asm/sn/tioca.h>

/*
              
                                                               
                                                               
                                    
 */

#define TIOCA_WAR_ENABLED(pv, tioca_common) \
	((1 << tioca_common->ca_rev) & pv)

  /*                                                                        */
#define PV907908 (1 << 1)
  /*                                                       */
#define PV908234 (1 << 1)
  /*                                                         */
#define PV895469 (1 << 1)
  /*                                                                           */
#define PV910244 (1 << 1)

struct tioca_dmamap{
	struct list_head	cad_list;	/*                   */

	dma_addr_t		cad_dma_addr;	/*                  */
	uint			cad_gart_entry; /*                                */
	uint			cad_gart_size;	/*                       */
};

/*
                                                                       
                                                           
 */

struct tioca_common ;

struct tioca_kernel {
	struct tioca_common	*ca_common;	/*                       */
	struct list_head	ca_list;	/*                  */
	struct list_head	ca_dmamaps;
	spinlock_t		ca_lock;	/*             */
	cnodeid_t		ca_closest_node;
	struct list_head	*ca_devices;	/*              */

	/*
                      
  */
	u64	ca_ap_size;		/*                            */
	u32	ca_gart_entries;	/*                       */
	u32	ca_ap_pagesize; 	/*                              */
	u64	ca_ap_bus_base; 	/*                             */
	u64	ca_gart_size;		/*                    */
	u64	*ca_gart;		/*                  */
	u64	ca_gart_coretalk_addr;	/*                    */
	u8		ca_gart_iscoherent;	/*                        */

	/*                             */
	u64	ca_pciap_base;		/*                                */
	u64	ca_pciap_size;		/*                            */
	u64	ca_pcigart_base;	/*                           */
	u64	*ca_pcigart;		/*                     */
	u32	ca_pcigart_entries;
	u32	ca_pcigart_start;	/*                            */
	void		*ca_pcigart_pagemap;

	/*                             */
	u64	ca_gfxap_base;		/*                                */
	u64	ca_gfxap_size;		/*                            */
	u64	ca_gfxgart_base;	/*                           */
	u64	*ca_gfxgart;		/*                     */
	u32	ca_gfxgart_entries;
	u32	ca_gfxgart_start;	/*                                */
};

/*
                                                   
  
                                                                 
                       
 */

struct tioca_common {
	struct pcibus_bussoft	ca_common;	/*                     */

	u32		ca_rev;
	u32		ca_closest_nasid;

	u64		ca_prom_private;
	u64		ca_kernel_private;
};

/* 
                                                                           
                                  
  
                                                                         
                              
  
                                                                             
                             
  
                                                                         
                   
  
                                                                       
             
  
                                                          
                                                    
                                               
                                           
 */
static inline u64
tioca_paddr_to_gart(unsigned long paddr)
{
	/*
                                                                
                                                                  
                                                               
  */

	return ((paddr) >> 12) | (1UL << 63);
}

/* 
                                                                         
                                         
 */

static inline unsigned long
tioca_physpage_to_gart(u64 page_addr)
{
	u64 coretalk_addr;

	coretalk_addr = PHYS_TO_TIODMA(page_addr);
	if (!coretalk_addr) {
		return 0;
	}

	return tioca_paddr_to_gart(coretalk_addr);
}

/* 
                                                             
                             
  
                                                                             
                
 */
static inline void
tioca_tlbflush(struct tioca_kernel *tioca_kernel)
{
	volatile u64 tmp;
	volatile struct tioca __iomem *ca_base;
	struct tioca_common *tioca_common;

	tioca_common = tioca_kernel->ca_common;
	ca_base = (struct tioca __iomem *)tioca_common->ca_common.bs_base;

	/*
                                                         
  */
	if (tioca_kernel->ca_gart_iscoherent) {
		if (TIOCA_WAR_ENABLED(PV910244, tioca_common)) {
			/*
                                                
                                                
                                                       
     
                                                     
                                        
    */

			__sn_clrq_relaxed(&ca_base->ca_control2, CA_GART_MEM_PARAM);
			__sn_setq_relaxed(&ca_base->ca_control2, CA_GART_FLUSH_TLB);
			__sn_setq_relaxed(&ca_base->ca_control2,
			    (0x2ull << CA_GART_MEM_PARAM_SHFT));
			tmp = __sn_readq_relaxed(&ca_base->ca_control2);
		}

		return;
	}

	/*
                                                     
  */

	__sn_setq_relaxed(&ca_base->ca_control2, CA_GART_FLUSH_TLB);
	tmp = __sn_readq_relaxed(&ca_base->ca_control2);
}

extern u32	tioca_gart_found;
extern struct list_head tioca_list;
extern int tioca_init_provider(void);
extern void tioca_fastwrite_enable(struct tioca_kernel *tioca_kern);
#endif /*                                    */