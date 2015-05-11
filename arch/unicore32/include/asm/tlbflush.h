/*
 * linux/arch/unicore32/include/asm/tlbflush.h
 *
 * Code specific to PKUnity SoC and UniCore ISA
 *
 * Copyright (C) 2001-2010 GUAN Xue-tao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __UNICORE_TLBFLUSH_H__
#define __UNICORE_TLBFLUSH_H__

#ifndef __ASSEMBLY__

#include <linux/sched.h>

extern void __cpu_flush_user_tlb_range(unsigned long, unsigned long,
					struct vm_area_struct *);
extern void __cpu_flush_kern_tlb_range(unsigned long, unsigned long);

/*
                 
                 
  
                                                             
  
                                                                 
                                                              
                                                             
                                                       
  
                  
  
                              
  
                   
  
                                                      
          
                                             
  
                                
  
                                                      
                  
                                             
                                                
                                                       
  
                            
  
                                                                 
                                                  
                                               
  
                             
  
                                                                 
                                                              
                                             
                                           
 */

static inline void local_flush_tlb_all(void)
{
	const int zero = 0;

	/*                    */
	asm("movc p0.c6, %0, #6; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (zero) : "cc");
}

static inline void local_flush_tlb_mm(struct mm_struct *mm)
{
	const int zero = 0;

	if (cpumask_test_cpu(get_cpu(), mm_cpumask(mm))) {
		/*                    */
		asm("movc p0.c6, %0, #6; nop; nop; nop; nop; nop; nop; nop; nop"
			: : "r" (zero) : "cc");
	}
	put_cpu();
}

static inline void
local_flush_tlb_page(struct vm_area_struct *vma, unsigned long uaddr)
{
	if (cpumask_test_cpu(smp_processor_id(), mm_cpumask(vma->vm_mm))) {
#ifndef CONFIG_CPU_TLB_SINGLE_ENTRY_DISABLE
		/*                      */
		asm("movc p0.c6, %0, #5; nop; nop; nop; nop; nop; nop; nop; nop"
			: : "r" (uaddr & PAGE_MASK) : "cc");
		/*                      */
		asm("movc p0.c6, %0, #3; nop; nop; nop; nop; nop; nop; nop; nop"
			: : "r" (uaddr & PAGE_MASK) : "cc");
#else
		/*                    */
		asm("movc p0.c6, %0, #6; nop; nop; nop; nop; nop; nop; nop; nop"
			: : "r" (uaddr & PAGE_MASK) : "cc");
#endif
	}
}

static inline void local_flush_tlb_kernel_page(unsigned long kaddr)
{
#ifndef CONFIG_CPU_TLB_SINGLE_ENTRY_DISABLE
	/*                      */
	asm("movc p0.c6, %0, #5; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (kaddr & PAGE_MASK) : "cc");
	/*                      */
	asm("movc p0.c6, %0, #3; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (kaddr & PAGE_MASK) : "cc");
#else
	/*                    */
	asm("movc p0.c6, %0, #6; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (kaddr & PAGE_MASK) : "cc");
#endif
}

/*
                  
  
                                                              
                                                              
                                                           
  
                  
  
                                                               
                                                                 
               
 */
static inline void flush_pmd_entry(pmd_t *pmd)
{
#ifndef CONFIG_CPU_DCACHE_LINE_DISABLE
	/*                                                          */
	asm("mov	r1, %0 << #20\n"
		"ldw	r2, =_stext\n"
		"add	r2, r2, r1 >> #20\n"
		"ldw	r1, [r2+], #0x0000\n"
		"ldw	r1, [r2+], #0x1000\n"
		"ldw	r1, [r2+], #0x2000\n"
		"ldw	r1, [r2+], #0x3000\n"
		: : "r" (pmd) : "r1", "r2");
#else
	/*                  */
	asm("movc p0.c5, %0, #14; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (pmd) : "cc");
#endif
}

static inline void clean_pmd_entry(pmd_t *pmd)
{
#ifndef CONFIG_CPU_DCACHE_LINE_DISABLE
	/*                   */
	asm("movc p0.c5, %0, #11; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (__pa(pmd) & ~(L1_CACHE_BYTES - 1)) : "cc");
#else
	/*                  */
	asm("movc p0.c5, %0, #10; nop; nop; nop; nop; nop; nop; nop; nop"
		: : "r" (pmd) : "cc");
#endif
}

/*
                                           
 */
#define local_flush_tlb_range(vma, start, end)	\
	__cpu_flush_user_tlb_range(start, end, vma)
#define local_flush_tlb_kernel_range(s, e)	\
	__cpu_flush_kern_tlb_range(s, e)

#define flush_tlb_all		local_flush_tlb_all
#define flush_tlb_mm		local_flush_tlb_mm
#define flush_tlb_page		local_flush_tlb_page
#define flush_tlb_kernel_page	local_flush_tlb_kernel_page
#define flush_tlb_range		local_flush_tlb_range
#define flush_tlb_kernel_range	local_flush_tlb_kernel_range

/*
                                                                         
                                                                 
                    
 */
extern void update_mmu_cache(struct vm_area_struct *vma,
		unsigned long addr, pte_t *ptep);

extern void do_bad_area(unsigned long addr, unsigned int fsr,
		struct pt_regs *regs);

#endif

#endif
