/*
 * Bit operations for the Hexagon architecture
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef _ASM_BITOPS_H
#define _ASM_BITOPS_H

#include <linux/compiler.h>
#include <asm/byteorder.h>
#include <asm/atomic.h>

#ifdef __KERNEL__

#define smp_mb__before_clear_bit()	barrier()
#define smp_mb__after_clear_bit()	barrier()

/*
                                                                     
                                                                       
                      
  
                                                                       
 */

/* 
                                                            
                            
                            
 */
static inline int test_and_clear_bit(int nr, volatile void *addr)
{
	int oldval;

	__asm__ __volatile__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = clrbit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if !P1 jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);

	return oldval;
}

/* 
                                                        
                          
                            
 */
static inline int test_and_set_bit(int nr, volatile void *addr)
{
	int oldval;

	__asm__ __volatile__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = setbit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if !P1 jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);


	return oldval;

}

/* 
                                                              
                          
                            
 */
static inline int test_and_change_bit(int nr, volatile void *addr)
{
	int oldval;

	__asm__ __volatile__ (
	"	{R10 = %1; R11 = asr(%2,#5); }\n"
	"	{R10 += asl(R11,#2); R11 = and(%2,#0x1f)}\n"
	"1:	R12 = memw_locked(R10);\n"
	"	{ P0 = tstbit(R12,R11); R12 = togglebit(R12,R11); }\n"
	"	memw_locked(R10,P1) = R12;\n"
	"	{if !P1 jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&r" (oldval)
	: "r" (addr), "r" (nr)
	: "r10", "r11", "r12", "p0", "p1", "memory"
	);

	return oldval;

}

/*
                                                   
                                        
 */

static inline void clear_bit(int nr, volatile void *addr)
{
	test_and_clear_bit(nr, addr);
}

static inline void set_bit(int nr, volatile void *addr)
{
	test_and_set_bit(nr, addr);
}

static inline void change_bit(int nr, volatile void *addr)
{
	test_and_change_bit(nr, addr);
}


/*
                                                                       
                                                                   
  
                                                                         
                                                                     
  
 */
static inline void __clear_bit(int nr, volatile unsigned long *addr)
{
	test_and_clear_bit(nr, addr);
}

static inline void __set_bit(int nr, volatile unsigned long *addr)
{
	test_and_set_bit(nr, addr);
}

static inline void __change_bit(int nr, volatile unsigned long *addr)
{
	test_and_change_bit(nr, addr);
}

/*                                                                   */
static inline int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
	return test_and_clear_bit(nr, addr);
}

static inline int __test_and_set_bit(int nr, volatile unsigned long *addr)
{
	return test_and_set_bit(nr, addr);
}

static inline int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
	return test_and_change_bit(nr, addr);
}

static inline int __test_bit(int nr, const volatile unsigned long *addr)
{
	int retval;

	asm volatile(
	"{P0 = tstbit(%1,%2); if (P0.new) %0 = #1; if (!P0.new) %0 = #0;}\n"
	: "=&r" (retval)
	: "r" (addr[BIT_WORD(nr)]), "r" (nr % BITS_PER_LONG)
	: "p0"
	);

	return retval;
}

#define test_bit(nr, addr) __test_bit(nr, addr)

/*
                                 
                            
  
                                                                        
 */
static inline long ffz(int x)
{
	int r;

	asm("%0 = ct1(%1);\n"
		: "=&r" (r)
		: "r" (x));
	return r;
}

/*
                                             
                         
  
                                       
                                                     
 */
static inline long fls(int x)
{
	int r;

	asm("{ %0 = cl0(%1);}\n"
		"%0 = sub(#32,%0);\n"
		: "=&r" (r)
		: "r" (x)
		: "p0");

	return r;
}

/*
                           
                         
  
                                  
                                                        
                                                  
 */
static inline long ffs(int x)
{
	int r;

	asm("{ P0 = cmp.eq(%1,#0); %0 = ct0(%1);}\n"
		"{ if P0 %0 = #0; if !P0 %0 = add(%0,#1);}\n"
		: "=&r" (r)
		: "r" (x)
		: "p0");

	return r;
}

/*
                                  
                            
  
                                                                    
  
                                 
                                                        
 */
static inline unsigned long __ffs(unsigned long word)
{
	int num;

	asm("%0 = ct0(%1);\n"
		: "=&r" (num)
		: "r" (word));

	return num;
}

/*
                                                              
                            
  
                                                                        
                                 
 */
static inline unsigned long __fls(unsigned long word)
{
	int num;

	asm("%0 = cl0(%1);\n"
		"%0 = sub(#31,%0);\n"
		: "=&r" (num)
		: "r" (word));

	return num;
}

#include <asm-generic/bitops/lock.h>
#include <asm-generic/bitops/find.h>

#include <asm-generic/bitops/fls64.h>
#include <asm-generic/bitops/sched.h>
#include <asm-generic/bitops/hweight.h>

#include <asm-generic/bitops/le.h>
#include <asm-generic/bitops/ext2-atomic.h>

#endif /*            */
#endif
