/*
 *  linux/arch/m68k/kernel/traps.c
 *
 *  Copyright (C) 1993, 1994 by Hamish Macdonald
 *
 *  68040 fixes by Michael Rausch
 *  68040 fixes by Martin Apel
 *  68040 fixes and writeback by Richard Zidlicky
 *  68060 fixes by Roman Hodek
 *  68060 fixes by Jesper Skov
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */

/*
                                
 */

#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/user.h>
#include <linux/string.h>
#include <linux/linkage.h>
#include <linux/init.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>

#include <asm/setup.h>
#include <asm/fpu.h>
#include <asm/uaccess.h>
#include <asm/traps.h>
#include <asm/pgalloc.h>
#include <asm/machdep.h>
#include <asm/siginfo.h>


static const char *vec_names[] = {
	[VEC_RESETSP]	= "RESET SP",
	[VEC_RESETPC]	= "RESET PC",
	[VEC_BUSERR]	= "BUS ERROR",
	[VEC_ADDRERR]	= "ADDRESS ERROR",
	[VEC_ILLEGAL]	= "ILLEGAL INSTRUCTION",
	[VEC_ZERODIV]	= "ZERO DIVIDE",
	[VEC_CHK]	= "CHK",
	[VEC_TRAP]	= "TRAPcc",
	[VEC_PRIV]	= "PRIVILEGE VIOLATION",
	[VEC_TRACE]	= "TRACE",
	[VEC_LINE10]	= "LINE 1010",
	[VEC_LINE11]	= "LINE 1111",
	[VEC_RESV12]	= "UNASSIGNED RESERVED 12",
	[VEC_COPROC]	= "COPROCESSOR PROTOCOL VIOLATION",
	[VEC_FORMAT]	= "FORMAT ERROR",
	[VEC_UNINT]	= "UNINITIALIZED INTERRUPT",
	[VEC_RESV16]	= "UNASSIGNED RESERVED 16",
	[VEC_RESV17]	= "UNASSIGNED RESERVED 17",
	[VEC_RESV18]	= "UNASSIGNED RESERVED 18",
	[VEC_RESV19]	= "UNASSIGNED RESERVED 19",
	[VEC_RESV20]	= "UNASSIGNED RESERVED 20",
	[VEC_RESV21]	= "UNASSIGNED RESERVED 21",
	[VEC_RESV22]	= "UNASSIGNED RESERVED 22",
	[VEC_RESV23]	= "UNASSIGNED RESERVED 23",
	[VEC_SPUR]	= "SPURIOUS INTERRUPT",
	[VEC_INT1]	= "LEVEL 1 INT",
	[VEC_INT2]	= "LEVEL 2 INT",
	[VEC_INT3]	= "LEVEL 3 INT",
	[VEC_INT4]	= "LEVEL 4 INT",
	[VEC_INT5]	= "LEVEL 5 INT",
	[VEC_INT6]	= "LEVEL 6 INT",
	[VEC_INT7]	= "LEVEL 7 INT",
	[VEC_SYS]	= "SYSCALL",
	[VEC_TRAP1]	= "TRAP #1",
	[VEC_TRAP2]	= "TRAP #2",
	[VEC_TRAP3]	= "TRAP #3",
	[VEC_TRAP4]	= "TRAP #4",
	[VEC_TRAP5]	= "TRAP #5",
	[VEC_TRAP6]	= "TRAP #6",
	[VEC_TRAP7]	= "TRAP #7",
	[VEC_TRAP8]	= "TRAP #8",
	[VEC_TRAP9]	= "TRAP #9",
	[VEC_TRAP10]	= "TRAP #10",
	[VEC_TRAP11]	= "TRAP #11",
	[VEC_TRAP12]	= "TRAP #12",
	[VEC_TRAP13]	= "TRAP #13",
	[VEC_TRAP14]	= "TRAP #14",
	[VEC_TRAP15]	= "TRAP #15",
	[VEC_FPBRUC]	= "FPCP BSUN",
	[VEC_FPIR]	= "FPCP INEXACT",
	[VEC_FPDIVZ]	= "FPCP DIV BY 0",
	[VEC_FPUNDER]	= "FPCP UNDERFLOW",
	[VEC_FPOE]	= "FPCP OPERAND ERROR",
	[VEC_FPOVER]	= "FPCP OVERFLOW",
	[VEC_FPNAN]	= "FPCP SNAN",
	[VEC_FPUNSUP]	= "FPCP UNSUPPORTED OPERATION",
	[VEC_MMUCFG]	= "MMU CONFIGURATION ERROR",
	[VEC_MMUILL]	= "MMU ILLEGAL OPERATION ERROR",
	[VEC_MMUACC]	= "MMU ACCESS LEVEL VIOLATION ERROR",
	[VEC_RESV59]	= "UNASSIGNED RESERVED 59",
	[VEC_UNIMPEA]	= "UNASSIGNED RESERVED 60",
	[VEC_UNIMPII]	= "UNASSIGNED RESERVED 61",
	[VEC_RESV62]	= "UNASSIGNED RESERVED 62",
	[VEC_RESV63]	= "UNASSIGNED RESERVED 63",
};

static const char *space_names[] = {
	[0]		= "Space 0",
	[USER_DATA]	= "User Data",
	[USER_PROGRAM]	= "User Program",
#ifndef CONFIG_SUN3
	[3]		= "Space 3",
#else
	[FC_CONTROL]	= "Control",
#endif
	[4]		= "Space 4",
	[SUPER_DATA]	= "Super Data",
	[SUPER_PROGRAM]	= "Super Program",
	[CPU_SPACE]	= "CPU"
};

void die_if_kernel(char *,struct pt_regs *,int);
asmlinkage int do_page_fault(struct pt_regs *regs, unsigned long address,
                             unsigned long error_code);
int send_fault_sig(struct pt_regs *regs);

asmlinkage void trap_c(struct frame *fp);

#if defined (CONFIG_M68060)
static inline void access_error060 (struct frame *fp)
{
	unsigned long fslw = fp->un.fmt4.pc; /*                                 */

#ifdef DEBUG
	printk("fslw=%#lx, fa=%#lx\n", fslw, fp->un.fmt4.effaddr);
#endif

	if (fslw & MMU060_BPE) {
		/*                                               */
		__asm__ __volatile__ ("movec %/cacr,%/d0\n\t"
				      "orl   #0x00400000,%/d0\n\t"
				      "movec %/d0,%/cacr"
				      : : : "d0" );
		/*                                  */
		if (!(fslw & MMU060_ERR_BITS) && !(fslw & MMU060_SEE))
			return;
	}

	if (fslw & (MMU060_DESC_ERR | MMU060_WP | MMU060_SP)) {
		unsigned long errorcode;
		unsigned long addr = fp->un.fmt4.effaddr;

		if (fslw & MMU060_MA)
			addr = (addr + PAGE_SIZE - 1) & PAGE_MASK;

		errorcode = 1;
		if (fslw & MMU060_DESC_ERR) {
			__flush_tlb040_one(addr);
			errorcode = 0;
		}
		if (fslw & MMU060_W)
			errorcode |= 2;
#ifdef DEBUG
		printk("errorcode = %d\n", errorcode );
#endif
		do_page_fault(&fp->ptregs, addr, errorcode);
	} else if (fslw & (MMU060_SEE)){
		/*                          
                                                     
   */
		send_fault_sig(&fp->ptregs);
	} else if (!(fslw & (MMU060_RE|MMU060_WE)) ||
		   send_fault_sig(&fp->ptregs) > 0) {
		printk("pc=%#lx, fa=%#lx\n", fp->ptregs.pc, fp->un.fmt4.effaddr);
		printk( "68060 access error, fslw=%lx\n", fslw );
		trap_c( fp );
	}
}
#endif /*               */

#if defined (CONFIG_M68040)
static inline unsigned long probe040(int iswrite, unsigned long addr, int wbs)
{
	unsigned long mmusr;
	mm_segment_t old_fs = get_fs();

	set_fs(MAKE_MM_SEG(wbs));

	if (iswrite)
		asm volatile (".chip 68040; ptestw (%0); .chip 68k" : : "a" (addr));
	else
		asm volatile (".chip 68040; ptestr (%0); .chip 68k" : : "a" (addr));

	asm volatile (".chip 68040; movec %%mmusr,%0; .chip 68k" : "=r" (mmusr));

	set_fs(old_fs);

	return mmusr;
}

static inline int do_040writeback1(unsigned short wbs, unsigned long wba,
				   unsigned long wbd)
{
	int res = 0;
	mm_segment_t old_fs = get_fs();

	/*                                                        */
	set_fs(MAKE_MM_SEG(wbs));

	switch (wbs & WBSIZ_040) {
	case BA_SIZE_BYTE:
		res = put_user(wbd & 0xff, (char __user *)wba);
		break;
	case BA_SIZE_WORD:
		res = put_user(wbd & 0xffff, (short __user *)wba);
		break;
	case BA_SIZE_LONG:
		res = put_user(wbd, (int __user *)wba);
		break;
	}

	/*                                                        */
	set_fs(old_fs);


#ifdef DEBUG
	printk("do_040writeback1, res=%d\n",res);
#endif

	return res;
}

/*                                                                
                                                                  
                                       
 */
static inline void fix_xframe040(struct frame *fp, unsigned long wba, unsigned short wbs)
{
	fp->un.fmt7.faddr = wba;
	fp->un.fmt7.ssw = wbs & 0xff;
	if (wba != current->thread.faddr)
	    fp->un.fmt7.ssw |= MA_040;
}

static inline void do_040writebacks(struct frame *fp)
{
	int res = 0;
#if 0
	if (fp->un.fmt7.wb1s & WBV_040)
		printk("access_error040: cannot handle 1st writeback. oops.\n");
#endif

	if ((fp->un.fmt7.wb2s & WBV_040) &&
	    !(fp->un.fmt7.wb2s & WBTT_040)) {
		res = do_040writeback1(fp->un.fmt7.wb2s, fp->un.fmt7.wb2a,
				       fp->un.fmt7.wb2d);
		if (res)
			fix_xframe040(fp, fp->un.fmt7.wb2a, fp->un.fmt7.wb2s);
		else
			fp->un.fmt7.wb2s = 0;
	}

	/*                                                                             */
	if (fp->un.fmt7.wb3s & WBV_040 && (!res || fp->un.fmt7.wb3s & 4)) {
		res = do_040writeback1(fp->un.fmt7.wb3s, fp->un.fmt7.wb3a,
				       fp->un.fmt7.wb3d);
		if (res)
		    {
			fix_xframe040(fp, fp->un.fmt7.wb3a, fp->un.fmt7.wb3s);

			fp->un.fmt7.wb2s = fp->un.fmt7.wb3s;
			fp->un.fmt7.wb3s &= (~WBV_040);
			fp->un.fmt7.wb2a = fp->un.fmt7.wb3a;
			fp->un.fmt7.wb2d = fp->un.fmt7.wb3d;
		    }
		else
			fp->un.fmt7.wb3s = 0;
	}

	if (res)
		send_fault_sig(&fp->ptregs);
}

/*
                                                             
                                                                     
                     
                                                       
 */
asmlinkage void berr_040cleanup(struct frame *fp)
{
	fp->un.fmt7.wb2s &= ~4;
	fp->un.fmt7.wb3s &= ~4;

	do_040writebacks(fp);
}

static inline void access_error040(struct frame *fp)
{
	unsigned short ssw = fp->un.fmt7.ssw;
	unsigned long mmusr;

#ifdef DEBUG
	printk("ssw=%#x, fa=%#lx\n", ssw, fp->un.fmt7.faddr);
        printk("wb1s=%#x, wb2s=%#x, wb3s=%#x\n", fp->un.fmt7.wb1s,
		fp->un.fmt7.wb2s, fp->un.fmt7.wb3s);
	printk ("wb2a=%lx, wb3a=%lx, wb2d=%lx, wb3d=%lx\n",
		fp->un.fmt7.wb2a, fp->un.fmt7.wb3a,
		fp->un.fmt7.wb2d, fp->un.fmt7.wb3d);
#endif

	if (ssw & ATC_040) {
		unsigned long addr = fp->un.fmt7.faddr;
		unsigned long errorcode;

		/*
                                                          
                                                              
   */
		if (ssw & MA_040)
			addr = (addr + 7) & -8;

		/*                                               */
		mmusr = probe040(!(ssw & RW_040), addr, ssw);
#ifdef DEBUG
		printk("mmusr = %lx\n", mmusr);
#endif
		errorcode = 1;
		if (!(mmusr & MMU_R_040)) {
			/*                             */
			__flush_tlb040_one(addr);
			errorcode = 0;
		}

		/*                                             
                                                      */
		if (!(ssw & RW_040) || (ssw & LK_040))
			errorcode |= 2;

		if (do_page_fault(&fp->ptregs, addr, errorcode)) {
#ifdef DEBUG
			printk("do_page_fault() !=0\n");
#endif
			if (user_mode(&fp->ptregs)){
				/*                                        */
#ifdef DEBUG
			        printk(".. was usermode - return\n");
#endif
				return;
			}
			/*                                              
                                               
                                                       
    */
disable_wb:
#ifdef DEBUG
			printk(".. disabling wb2\n");
#endif
			if (fp->un.fmt7.wb2a == fp->un.fmt7.faddr)
				fp->un.fmt7.wb2s &= ~WBV_040;
			if (fp->un.fmt7.wb3a == fp->un.fmt7.faddr)
				fp->un.fmt7.wb3s &= ~WBV_040;
		}
	} else {
		/*                                                            
                                                                  
                              
   */
		current->thread.signo = SIGBUS;
		current->thread.faddr = fp->un.fmt7.faddr;
		if (send_fault_sig(&fp->ptregs) >= 0)
			printk("68040 bus error (ssw=%x, faddr=%lx)\n", ssw,
			       fp->un.fmt7.faddr);
		goto disable_wb;
	}

	do_040writebacks(fp);
}
#endif /*               */

#if defined(CONFIG_SUN3)
#include <asm/sun3mmu.h>

extern int mmu_emu_handle_fault (unsigned long, int, int);

/*                              */

static inline void bus_error030 (struct frame *fp)
{
	unsigned char buserr_type = sun3_get_buserr ();
	unsigned long addr, errorcode;
	unsigned short ssw = fp->un.fmtb.ssw;
	extern unsigned long _sun3_map_test_start, _sun3_map_test_end;

#ifdef DEBUG
	if (ssw & (FC | FB))
		printk ("Instruction fault at %#010lx\n",
			ssw & FC ?
			fp->ptregs.format == 0xa ? fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2
			:
			fp->ptregs.format == 0xa ? fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
	if (ssw & DF)
		printk ("Data %s fault at %#010lx in %s (pc=%#lx)\n",
			ssw & RW ? "read" : "write",
			fp->un.fmtb.daddr,
			space_names[ssw & DFC], fp->ptregs.pc);
#endif

	/*
                                                                       
                                                                     
                            
  */

	if ((ssw & DF)
	    && (buserr_type & (SUN3_BUSERR_PROTERR | SUN3_BUSERR_INVALID))) {
		if (mmu_emu_handle_fault (fp->un.fmtb.daddr, ssw & RW, 0))
			return;
	}

	/*                                         */
	if (fp->ptregs.sr & PS_S) {
		/*                                                 */
		if (! ((ssw & DF) && ((ssw & DFC) == USER_DATA))) {
		     //                                                  
		     if (mmu_emu_handle_fault (fp->un.fmtb.daddr, ssw & RW, 1))
			  return;
			/*                                         */
			if (ssw & (FC | FB))
				printk ("Instruction fault at %#010lx\n",
					fp->ptregs.pc);
			if (ssw & DF) {
				/*                                               */
				if((fp->ptregs.pc >= (unsigned long)&_sun3_map_test_start) &&
				   (fp->ptregs.pc <= (unsigned long)&_sun3_map_test_end)) {
					send_fault_sig(&fp->ptregs);
					return;
				}

				printk ("Data %s fault at %#010lx in %s (pc=%#lx)\n",
					ssw & RW ? "read" : "write",
					fp->un.fmtb.daddr,
					space_names[ssw & DFC], fp->ptregs.pc);
			}
			printk ("BAD KERNEL BUSERR\n");

			die_if_kernel("Oops", &fp->ptregs,0);
			force_sig(SIGKILL, current);
			return;
		}
	} else {
		/*            */
		if (!(ssw & (FC | FB)) && !(ssw & DF))
			/*                                             */
			panic ("USER BUSERR w/o instruction or data fault");
	}


	/*                                       */
	if (ssw & DF) {
		addr = fp->un.fmtb.daddr;

//                                                     
//                                                   

//                                                        
//                                                          

		if (buserr_type & SUN3_BUSERR_PROTERR)
			errorcode = 0x01;
		else if (buserr_type & SUN3_BUSERR_INVALID)
			errorcode = 0x00;
		else {
#ifdef DEBUG
			printk ("*** unexpected busfault type=%#04x\n", buserr_type);
			printk ("invalid %s access at %#lx from pc %#lx\n",
				!(ssw & RW) ? "write" : "read", addr,
				fp->ptregs.pc);
#endif
			die_if_kernel ("Oops", &fp->ptregs, buserr_type);
			force_sig (SIGBUS, current);
			return;
		}

//                        
		if (!(ssw & RW) || ssw & RM)
			errorcode |= 0x02;

		/*                    */
		do_page_fault (&fp->ptregs, addr, errorcode);

		/*                           */
		return;
	}

	/*                                   */

	/*                        */
	if (fp->ptregs.format == 0xA)
		addr = fp->ptregs.pc + 4;
	else
		addr = fp->un.fmtb.baddr;
	if (ssw & FC)
		addr -= 2;

	if (buserr_type & SUN3_BUSERR_INVALID) {
		if (!mmu_emu_handle_fault (fp->un.fmtb.daddr, 1, 0))
			do_page_fault (&fp->ptregs, addr, 0);
       } else {
#ifdef DEBUG
		printk ("protection fault on insn access (segv).\n");
#endif
		force_sig (SIGSEGV, current);
       }
}
#else
#if defined(CPU_M68020_OR_M68030)
static inline void bus_error030 (struct frame *fp)
{
	volatile unsigned short temp;
	unsigned short mmusr;
	unsigned long addr, errorcode;
	unsigned short ssw = fp->un.fmtb.ssw;
#ifdef DEBUG
	unsigned long desc;

	printk ("pid = %x  ", current->pid);
	printk ("SSW=%#06x  ", ssw);

	if (ssw & (FC | FB))
		printk ("Instruction fault at %#010lx\n",
			ssw & FC ?
			fp->ptregs.format == 0xa ? fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2
			:
			fp->ptregs.format == 0xa ? fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
	if (ssw & DF)
		printk ("Data %s fault at %#010lx in %s (pc=%#lx)\n",
			ssw & RW ? "read" : "write",
			fp->un.fmtb.daddr,
			space_names[ssw & DFC], fp->ptregs.pc);
#endif

	/*                                                           
                                         */

	/*                                       */
	if (ssw & DF) {
		addr = fp->un.fmtb.daddr;

#ifdef DEBUG
		asm volatile ("ptestr %3,%2@,#7,%0\n\t"
			      "pmove %%psr,%1"
			      : "=a&" (desc), "=m" (temp)
			      : "a" (addr), "d" (ssw));
#else
		asm volatile ("ptestr %2,%1@,#7\n\t"
			      "pmove %%psr,%0"
			      : "=m" (temp) : "a" (addr), "d" (ssw));
#endif
		mmusr = temp;

#ifdef DEBUG
		printk("mmusr is %#x for addr %#lx in task %p\n",
		       mmusr, addr, current);
		printk("descriptor address is %#lx, contents %#lx\n",
		       __va(desc), *(unsigned long *)__va(desc));
#endif

		errorcode = (mmusr & MMU_I) ? 0 : 1;
		if (!(ssw & RW) || (ssw & RM))
			errorcode |= 2;

		if (mmusr & (MMU_I | MMU_WP)) {
			if (ssw & 4) {
				printk("Data %s fault at %#010lx in %s (pc=%#lx)\n",
				       ssw & RW ? "read" : "write",
				       fp->un.fmtb.daddr,
				       space_names[ssw & DFC], fp->ptregs.pc);
				goto buserr;
			}
			/*                                                     
               */
			if (do_page_fault (&fp->ptregs, addr, errorcode) < 0)
				return;
		} else if (!(mmusr & MMU_I)) {
			/*                          */
			if (!(ssw & RM) && send_fault_sig(&fp->ptregs) > 0)
				printk("unexpected bus error (%#x,%#x)\n", ssw, mmusr);
		} else if (mmusr & (MMU_B|MMU_L|MMU_S)) {
			printk("invalid %s access at %#lx from pc %#lx\n",
			       !(ssw & RW) ? "write" : "read", addr,
			       fp->ptregs.pc);
			die_if_kernel("Oops",&fp->ptregs,mmusr);
			force_sig(SIGSEGV, current);
			return;
		} else {
#if 0
			static volatile long tlong;
#endif

			printk("weird %s access at %#lx from pc %#lx (ssw is %#x)\n",
			       !(ssw & RW) ? "write" : "read", addr,
			       fp->ptregs.pc, ssw);
			asm volatile ("ptestr #1,%1@,#0\n\t"
				      "pmove %%psr,%0"
				      : "=m" (temp)
				      : "a" (addr));
			mmusr = temp;

			printk ("level 0 mmusr is %#x\n", mmusr);
#if 0
			asm volatile ("pmove %%tt0,%0"
				      : "=m" (tlong));
			printk("tt0 is %#lx, ", tlong);
			asm volatile ("pmove %%tt1,%0"
				      : "=m" (tlong));
			printk("tt1 is %#lx\n", tlong);
#endif
#ifdef DEBUG
			printk("Unknown SIGSEGV - 1\n");
#endif
			die_if_kernel("Oops",&fp->ptregs,mmusr);
			force_sig(SIGSEGV, current);
			return;
		}

		/*                                                       */
		if (!(ssw & RW) || (ssw & RM))
			asm volatile ("ploadw %1,%0@" : /*            */
				      : "a" (addr), "d" (ssw));
		else
			asm volatile ("ploadr %1,%0@" : /*            */
				      : "a" (addr), "d" (ssw));
	}

	/*                                   */

	if (!(ssw & (FC|FB)))
		return;

	if (fp->ptregs.sr & PS_S) {
		printk("Instruction fault at %#010lx\n",
			fp->ptregs.pc);
	buserr:
		printk ("BAD KERNEL BUSERR\n");
		die_if_kernel("Oops",&fp->ptregs,0);
		force_sig(SIGKILL, current);
		return;
	}

	/*                       */
	if (fp->ptregs.format == 10)
		addr = fp->ptregs.pc + 4;
	else
		addr = fp->un.fmtb.baddr;
	if (ssw & FC)
		addr -= 2;

	if ((ssw & DF) && ((addr ^ fp->un.fmtb.daddr) & PAGE_MASK) == 0)
		/*                                               
                                         */
		goto create_atc_entry;

#ifdef DEBUG
	asm volatile ("ptestr #1,%2@,#7,%0\n\t"
		      "pmove %%psr,%1"
		      : "=a&" (desc), "=m" (temp)
		      : "a" (addr));
#else
	asm volatile ("ptestr #1,%1@,#7\n\t"
		      "pmove %%psr,%0"
		      : "=m" (temp) : "a" (addr));
#endif
	mmusr = temp;

#ifdef DEBUG
	printk ("mmusr is %#x for addr %#lx in task %p\n",
		mmusr, addr, current);
	printk ("descriptor address is %#lx, contents %#lx\n",
		__va(desc), *(unsigned long *)__va(desc));
#endif

	if (mmusr & MMU_I)
		do_page_fault (&fp->ptregs, addr, 0);
	else if (mmusr & (MMU_B|MMU_L|MMU_S)) {
		printk ("invalid insn access at %#lx from pc %#lx\n",
			addr, fp->ptregs.pc);
#ifdef DEBUG
		printk("Unknown SIGSEGV - 2\n");
#endif
		die_if_kernel("Oops",&fp->ptregs,mmusr);
		force_sig(SIGSEGV, current);
		return;
	}

create_atc_entry:
	/*                                                       */
	asm volatile ("ploadr #2,%0@" : /*            */
		      : "a" (addr));
}
#endif /*                      */
#endif /*              */

#if defined(CONFIG_COLDFIRE) && defined(CONFIG_MMU)
#include <asm/mcfmmu.h>

/*
                                                             
                                                            
            
*/
static const unsigned char fs_err_code[] = {
	0,  /*      */
	0,  /*      */
	0,  /*      */
	0,  /*      */
	1,  /*      */
	0,  /*      */
	0,  /*      */
	0,  /*      */
	2,  /*      */
	3,  /*      */
	2,  /*      */
	0,  /*      */
	1,  /*      */
	1,  /*      */
	0,  /*      */
	0   /*      */
};

static inline void access_errorcf(unsigned int fs, struct frame *fp)
{
	unsigned long mmusr, addr;
	unsigned int err_code;
	int need_page_fault;

	mmusr = mmu_read(MMUSR);
	addr = mmu_read(MMUAR);

	/*
               
                                                            
                                        
  */
	switch (fs) {
	case  5:  /*                        */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 0, 0);
		addr = fp->ptregs.pc;
		break;
	case  6:  /*                                */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 0, 1);
		addr = fp->ptregs.pc + sizeof(long);
		break;
	case 10:  /*                 */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 1, 1, 0);
		break;
	case 14: /*                 */
		need_page_fault = cf_tlb_miss(&fp->ptregs, 0, 1, 0);
		break;
	default:
		/*              */
		/*               */
		/*                                             */
		/*               */
		/*                   */
		/*                           */
		/*                  */
		/*                 */
		/*              */
		/*                  */
		/*                  */
		/*                          */
		need_page_fault = 1;
		break;
	}

	if (need_page_fault) {
		err_code = fs_err_code[fs];
		if ((fs == 13) && (mmusr & MMUSR_WF)) /*                  */
			err_code |= 2; /*                                 */
		do_page_fault(&fp->ptregs, addr, err_code);
	}
}
#endif /*                            */

asmlinkage void buserr_c(struct frame *fp)
{
	/*                                        */
	if (user_mode(&fp->ptregs))
		current->thread.esp0 = (unsigned long) fp;

#ifdef DEBUG
	printk ("*** Bus Error *** Format is %x\n", fp->ptregs.format);
#endif

#if defined(CONFIG_COLDFIRE) && defined(CONFIG_MMU)
	if (CPU_IS_COLDFIRE) {
		unsigned int fs;
		fs = (fp->ptregs.vector & 0x3) |
			((fp->ptregs.vector & 0xc00) >> 8);
		switch (fs) {
		case 0x5:
		case 0x6:
		case 0x7:
		case 0x9:
		case 0xa:
		case 0xd:
		case 0xe:
		case 0xf:
			access_errorcf(fs, fp);
			return;
		default:
			break;
		}
	}
#endif /*                               */

	switch (fp->ptregs.format) {
#if defined (CONFIG_M68060)
	case 4:				/*                    */
	  access_error060 (fp);
	  break;
#endif
#if defined (CONFIG_M68040)
	case 0x7:			/*                    */
	  access_error040 (fp);
	  break;
#endif
#if defined (CPU_M68020_OR_M68030)
	case 0xa:
	case 0xb:
	  bus_error030 (fp);
	  break;
#endif
	default:
	  die_if_kernel("bad frame format",&fp->ptregs,0);
#ifdef DEBUG
	  printk("Unknown SIGSEGV - 4\n");
#endif
	  force_sig(SIGSEGV, current);
	}
}


static int kstack_depth_to_print = 48;

void show_trace(unsigned long *stack)
{
	unsigned long *endstack;
	unsigned long addr;
	int i;

	printk("Call Trace:");
	addr = (unsigned long)stack + THREAD_SIZE - 1;
	endstack = (unsigned long *)(addr & -THREAD_SIZE);
	i = 0;
	while (stack + 1 <= endstack) {
		addr = *stack++;
		/*
                                                        
                                                       
                                                 
                                                     
                                                       
                                      
   */
		if (__kernel_text_address(addr)) {
#ifndef CONFIG_KALLSYMS
			if (i % 5 == 0)
				printk("\n       ");
#endif
			printk(" [<%08lx>] %pS\n", addr, (void *)addr);
			i++;
		}
	}
	printk("\n");
}

void show_registers(struct pt_regs *regs)
{
	struct frame *fp = (struct frame *)regs;
	mm_segment_t old_fs = get_fs();
	u16 c, *cp;
	unsigned long addr;
	int i;

	print_modules();
	printk("PC: [<%08lx>] %pS\n", regs->pc, (void *)regs->pc);
	printk("SR: %04x  SP: %p  a2: %08lx\n", regs->sr, regs, regs->a2);
	printk("d0: %08lx    d1: %08lx    d2: %08lx    d3: %08lx\n",
	       regs->d0, regs->d1, regs->d2, regs->d3);
	printk("d4: %08lx    d5: %08lx    a0: %08lx    a1: %08lx\n",
	       regs->d4, regs->d5, regs->a0, regs->a1);

	printk("Process %s (pid: %d, task=%p)\n",
		current->comm, task_pid_nr(current), current);
	addr = (unsigned long)&fp->un;
	printk("Frame format=%X ", regs->format);
	switch (regs->format) {
	case 0x2:
		printk("instr addr=%08lx\n", fp->un.fmt2.iaddr);
		addr += sizeof(fp->un.fmt2);
		break;
	case 0x3:
		printk("eff addr=%08lx\n", fp->un.fmt3.effaddr);
		addr += sizeof(fp->un.fmt3);
		break;
	case 0x4:
		printk((CPU_IS_060 ? "fault addr=%08lx fslw=%08lx\n"
			: "eff addr=%08lx pc=%08lx\n"),
			fp->un.fmt4.effaddr, fp->un.fmt4.pc);
		addr += sizeof(fp->un.fmt4);
		break;
	case 0x7:
		printk("eff addr=%08lx ssw=%04x faddr=%08lx\n",
			fp->un.fmt7.effaddr, fp->un.fmt7.ssw, fp->un.fmt7.faddr);
		printk("wb 1 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb1s, fp->un.fmt7.wb1a, fp->un.fmt7.wb1dpd0);
		printk("wb 2 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb2s, fp->un.fmt7.wb2a, fp->un.fmt7.wb2d);
		printk("wb 3 stat/addr/data: %04x %08lx %08lx\n",
			fp->un.fmt7.wb3s, fp->un.fmt7.wb3a, fp->un.fmt7.wb3d);
		printk("push data: %08lx %08lx %08lx %08lx\n",
			fp->un.fmt7.wb1dpd0, fp->un.fmt7.pd1, fp->un.fmt7.pd2,
			fp->un.fmt7.pd3);
		addr += sizeof(fp->un.fmt7);
		break;
	case 0x9:
		printk("instr addr=%08lx\n", fp->un.fmt9.iaddr);
		addr += sizeof(fp->un.fmt9);
		break;
	case 0xa:
		printk("ssw=%04x isc=%04x isb=%04x daddr=%08lx dobuf=%08lx\n",
			fp->un.fmta.ssw, fp->un.fmta.isc, fp->un.fmta.isb,
			fp->un.fmta.daddr, fp->un.fmta.dobuf);
		addr += sizeof(fp->un.fmta);
		break;
	case 0xb:
		printk("ssw=%04x isc=%04x isb=%04x daddr=%08lx dobuf=%08lx\n",
			fp->un.fmtb.ssw, fp->un.fmtb.isc, fp->un.fmtb.isb,
			fp->un.fmtb.daddr, fp->un.fmtb.dobuf);
		printk("baddr=%08lx dibuf=%08lx ver=%x\n",
			fp->un.fmtb.baddr, fp->un.fmtb.dibuf, fp->un.fmtb.ver);
		addr += sizeof(fp->un.fmtb);
		break;
	default:
		printk("\n");
	}
	show_stack(NULL, (unsigned long *)addr);

	printk("Code:");
	set_fs(KERNEL_DS);
	cp = (u16 *)regs->pc;
	for (i = -8; i < 16; i++) {
		if (get_user(c, cp + i) && i >= 0) {
			printk(" Bad PC value.");
			break;
		}
		printk(i ? " %04x" : " <%04x>", c);
	}
	set_fs(old_fs);
	printk ("\n");
}

void show_stack(struct task_struct *task, unsigned long *stack)
{
	unsigned long *p;
	unsigned long *endstack;
	int i;

	if (!stack) {
		if (task)
			stack = (unsigned long *)task->thread.esp0;
		else
			stack = (unsigned long *)&stack;
	}
	endstack = (unsigned long *)(((unsigned long)stack + THREAD_SIZE - 1) & -THREAD_SIZE);

	printk("Stack from %08lx:", (unsigned long)stack);
	p = stack;
	for (i = 0; i < kstack_depth_to_print; i++) {
		if (p + 1 > endstack)
			break;
		if (i % 8 == 0)
			printk("\n       ");
		printk(" %08lx", *p++);
	}
	printk("\n");
	show_trace(stack);
}

/*
                                                   
 */
void dump_stack(void)
{
	unsigned long stack;

	show_trace(&stack);
}

EXPORT_SYMBOL(dump_stack);

/*
                                                                   
                                                                    
                                                                   
                                                                      
                                            
 */

void bad_super_trap (struct frame *fp)
{
	int vector = (fp->ptregs.vector >> 2) & 0xff;

	console_verbose();
	if (vector < ARRAY_SIZE(vec_names))
		printk ("*** %s ***   FORMAT=%X\n",
			vec_names[vector],
			fp->ptregs.format);
	else
		printk ("*** Exception %d ***   FORMAT=%X\n",
			vector, fp->ptregs.format);
	if (vector == VEC_ADDRERR && CPU_IS_020_OR_030) {
		unsigned short ssw = fp->un.fmtb.ssw;

		printk ("SSW=%#06x  ", ssw);

		if (ssw & RC)
			printk ("Pipe stage C instruction fault at %#010lx\n",
				(fp->ptregs.format) == 0xA ?
				fp->ptregs.pc + 2 : fp->un.fmtb.baddr - 2);
		if (ssw & RB)
			printk ("Pipe stage B instruction fault at %#010lx\n",
				(fp->ptregs.format) == 0xA ?
				fp->ptregs.pc + 4 : fp->un.fmtb.baddr);
		if (ssw & DF)
			printk ("Data %s fault at %#010lx in %s (pc=%#lx)\n",
				ssw & RW ? "read" : "write",
				fp->un.fmtb.daddr, space_names[ssw & DFC],
				fp->ptregs.pc);
	}
	printk ("Current process id is %d\n", task_pid_nr(current));
	die_if_kernel("BAD KERNEL TRAP", &fp->ptregs, 0);
}

asmlinkage void trap_c(struct frame *fp)
{
	int sig;
	int vector = (fp->ptregs.vector >> 2) & 0xff;
	siginfo_t info;

	if (fp->ptregs.sr & PS_S) {
		if (vector == VEC_TRACE) {
			/*                                             
                                                 
    */
		} else if (!handle_kernel_fault(&fp->ptregs))
			bad_super_trap(fp);
		return;
	}

	/*                                                 */
	switch (vector) {
	    case VEC_ADDRERR:
		info.si_code = BUS_ADRALN;
		sig = SIGBUS;
		break;
	    case VEC_ILLEGAL:
	    case VEC_LINE10:
	    case VEC_LINE11:
		info.si_code = ILL_ILLOPC;
		sig = SIGILL;
		break;
	    case VEC_PRIV:
		info.si_code = ILL_PRVOPC;
		sig = SIGILL;
		break;
	    case VEC_COPROC:
		info.si_code = ILL_COPROC;
		sig = SIGILL;
		break;
	    case VEC_TRAP1:
	    case VEC_TRAP2:
	    case VEC_TRAP3:
	    case VEC_TRAP4:
	    case VEC_TRAP5:
	    case VEC_TRAP6:
	    case VEC_TRAP7:
	    case VEC_TRAP8:
	    case VEC_TRAP9:
	    case VEC_TRAP10:
	    case VEC_TRAP11:
	    case VEC_TRAP12:
	    case VEC_TRAP13:
	    case VEC_TRAP14:
		info.si_code = ILL_ILLTRP;
		sig = SIGILL;
		break;
	    case VEC_FPBRUC:
	    case VEC_FPOE:
	    case VEC_FPNAN:
		info.si_code = FPE_FLTINV;
		sig = SIGFPE;
		break;
	    case VEC_FPIR:
		info.si_code = FPE_FLTRES;
		sig = SIGFPE;
		break;
	    case VEC_FPDIVZ:
		info.si_code = FPE_FLTDIV;
		sig = SIGFPE;
		break;
	    case VEC_FPUNDER:
		info.si_code = FPE_FLTUND;
		sig = SIGFPE;
		break;
	    case VEC_FPOVER:
		info.si_code = FPE_FLTOVF;
		sig = SIGFPE;
		break;
	    case VEC_ZERODIV:
		info.si_code = FPE_INTDIV;
		sig = SIGFPE;
		break;
	    case VEC_CHK:
	    case VEC_TRAP:
		info.si_code = FPE_INTOVF;
		sig = SIGFPE;
		break;
	    case VEC_TRACE:		/*                    */
		info.si_code = TRAP_TRACE;
		sig = SIGTRAP;
		break;
	    case VEC_TRAP15:		/*            */
		info.si_code = TRAP_BRKPT;
		sig = SIGTRAP;
		break;
	    default:
		info.si_code = ILL_ILLOPC;
		sig = SIGILL;
		break;
	}
	info.si_signo = sig;
	info.si_errno = 0;
	switch (fp->ptregs.format) {
	    default:
		info.si_addr = (void *) fp->ptregs.pc;
		break;
	    case 2:
		info.si_addr = (void *) fp->un.fmt2.iaddr;
		break;
	    case 7:
		info.si_addr = (void *) fp->un.fmt7.effaddr;
		break;
	    case 9:
		info.si_addr = (void *) fp->un.fmt9.iaddr;
		break;
	    case 10:
		info.si_addr = (void *) fp->un.fmta.daddr;
		break;
	    case 11:
		info.si_addr = (void *) fp->un.fmtb.daddr;
		break;
	}
	force_sig_info (sig, &info, current);
}

void die_if_kernel (char *str, struct pt_regs *fp, int nr)
{
	if (!(fp->sr & PS_S))
		return;

	console_verbose();
	printk("%s: %08x\n",str,nr);
	show_registers(fp);
	add_taint(TAINT_DIE);
	do_exit(SIGSEGV);
}

asmlinkage void set_esp0(unsigned long ssp)
{
	current->thread.esp0 = ssp;
}

/*
                                                            
                                    
 */
asmlinkage void fpsp040_die(void)
{
	do_exit(SIGSEGV);
}

#ifdef CONFIG_M68KFPU_EMU
asmlinkage void fpemu_signal(int signal, int code, void *addr)
{
	siginfo_t info;

	info.si_signo = signal;
	info.si_errno = 0;
	info.si_code = code;
	info.si_addr = addr;
	force_sig_info(signal, &info, current);
}
#endif
