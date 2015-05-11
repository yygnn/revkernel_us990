#ifndef _ASM_X86_ELF_H
#define _ASM_X86_ELF_H

/*
                             
 */
#include <linux/thread_info.h>

#include <asm/ptrace.h>
#include <asm/user.h>
#include <asm/auxvec.h>

typedef unsigned long elf_greg_t;

#define ELF_NGREG (sizeof(struct user_regs_struct) / sizeof(elf_greg_t))
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

typedef struct user_i387_struct elf_fpregset_t;

#ifdef __i386__

typedef struct user_fxsr_struct elf_fpxregset_t;

#define R_386_NONE	0
#define R_386_32	1
#define R_386_PC32	2
#define R_386_GOT32	3
#define R_386_PLT32	4
#define R_386_COPY	5
#define R_386_GLOB_DAT	6
#define R_386_JMP_SLOT	7
#define R_386_RELATIVE	8
#define R_386_GOTOFF	9
#define R_386_GOTPC	10
#define R_386_NUM	11

/*
                                                      
 */
#define ELF_CLASS	ELFCLASS32
#define ELF_DATA	ELFDATA2LSB
#define ELF_ARCH	EM_386

#else

/*                         */
#define R_X86_64_NONE		0	/*          */
#define R_X86_64_64		1	/*                */
#define R_X86_64_PC32		2	/*                           */
#define R_X86_64_GOT32		3	/*                  */
#define R_X86_64_PLT32		4	/*                    */
#define R_X86_64_COPY		5	/*                        */
#define R_X86_64_GLOB_DAT	6	/*                  */
#define R_X86_64_JUMP_SLOT	7	/*                  */
#define R_X86_64_RELATIVE	8	/*                        */
#define R_X86_64_GOTPCREL	9	/*                          
                      */
#define R_X86_64_32		10	/*                             */
#define R_X86_64_32S		11	/*                             */
#define R_X86_64_16		12	/*                             */
#define R_X86_64_PC16		13	/*                                  */
#define R_X86_64_8		14	/*                             */
#define R_X86_64_PC8		15	/*                                 */

#define R_X86_64_NUM		16

/*
                                                      
 */
#define ELF_CLASS	ELFCLASS64
#define ELF_DATA	ELFDATA2LSB
#define ELF_ARCH	EM_X86_64

#endif

#include <asm/vdso.h>

extern unsigned int vdso_enabled;

/*
                                                                             
 */
#define elf_check_arch_ia32(x) \
	(((x)->e_machine == EM_386) || ((x)->e_machine == EM_486))

#include <asm/processor.h>

#ifdef CONFIG_X86_32
#include <asm/desc.h>

#define elf_check_arch(x)	elf_check_arch_ia32(x)

/*                                                                        
                                                                             
                                                                            
                                                               

                                              

                                                                               
                                          
 */
#define ELF_PLAT_INIT(_r, load_addr)		\
	do {					\
	_r->bx = 0; _r->cx = 0; _r->dx = 0;	\
	_r->si = 0; _r->di = 0; _r->bp = 0;	\
	_r->ax = 0;				\
} while (0)

/*
                                                            
                                            
 */

#define ELF_CORE_COPY_REGS_COMMON(pr_reg, regs)	\
do {						\
	pr_reg[0] = regs->bx;			\
	pr_reg[1] = regs->cx;			\
	pr_reg[2] = regs->dx;			\
	pr_reg[3] = regs->si;			\
	pr_reg[4] = regs->di;			\
	pr_reg[5] = regs->bp;			\
	pr_reg[6] = regs->ax;			\
	pr_reg[7] = regs->ds & 0xffff;		\
	pr_reg[8] = regs->es & 0xffff;		\
	pr_reg[9] = regs->fs & 0xffff;		\
	pr_reg[11] = regs->orig_ax;		\
	pr_reg[12] = regs->ip;			\
	pr_reg[13] = regs->cs & 0xffff;		\
	pr_reg[14] = regs->flags;		\
	pr_reg[15] = regs->sp;			\
	pr_reg[16] = regs->ss & 0xffff;		\
} while (0);

#define ELF_CORE_COPY_REGS(pr_reg, regs)	\
do {						\
	ELF_CORE_COPY_REGS_COMMON(pr_reg, regs);\
	pr_reg[10] = get_user_gs(regs);		\
} while (0);

#define ELF_CORE_COPY_KERNEL_REGS(pr_reg, regs)	\
do {						\
	ELF_CORE_COPY_REGS_COMMON(pr_reg, regs);\
	savesegment(gs, pr_reg[10]);		\
} while (0);

#define ELF_PLATFORM	(utsname()->machine)
#define set_personality_64bit()	do { } while (0)

#else /*               */

/*
                                                                             
 */
#define elf_check_arch(x)			\
	((x)->e_machine == EM_X86_64)

#define compat_elf_check_arch(x)		\
	(elf_check_arch_ia32(x) || (x)->e_machine == EM_X86_64)

#if __USER32_DS != __USER_DS
# error "The following code assumes __USER32_DS == __USER_DS"
#endif

static inline void elf_common_init(struct thread_struct *t,
				   struct pt_regs *regs, const u16 ds)
{
	regs->ax = regs->bx = regs->cx = regs->dx = 0;
	regs->si = regs->di = regs->bp = 0;
	regs->r8 = regs->r9 = regs->r10 = regs->r11 = 0;
	regs->r12 = regs->r13 = regs->r14 = regs->r15 = 0;
	t->fs = t->gs = 0;
	t->fsindex = t->gsindex = 0;
	t->ds = t->es = ds;
}

#define ELF_PLAT_INIT(_r, load_addr)			\
	elf_common_init(&current->thread, _r, 0)

#define	COMPAT_ELF_PLAT_INIT(regs, load_addr)		\
	elf_common_init(&current->thread, regs, __USER_DS)

void start_thread_ia32(struct pt_regs *regs, u32 new_ip, u32 new_sp);
#define compat_start_thread start_thread_ia32

void set_personality_ia32(bool);
#define COMPAT_SET_PERSONALITY(ex)			\
	set_personality_ia32((ex).e_machine == EM_X86_64)

#define COMPAT_ELF_PLATFORM			("i686")

/*
                                                            
                                                                            
                  
 */

#define ELF_CORE_COPY_REGS(pr_reg, regs)			\
do {								\
	unsigned v;						\
	(pr_reg)[0] = (regs)->r15;				\
	(pr_reg)[1] = (regs)->r14;				\
	(pr_reg)[2] = (regs)->r13;				\
	(pr_reg)[3] = (regs)->r12;				\
	(pr_reg)[4] = (regs)->bp;				\
	(pr_reg)[5] = (regs)->bx;				\
	(pr_reg)[6] = (regs)->r11;				\
	(pr_reg)[7] = (regs)->r10;				\
	(pr_reg)[8] = (regs)->r9;				\
	(pr_reg)[9] = (regs)->r8;				\
	(pr_reg)[10] = (regs)->ax;				\
	(pr_reg)[11] = (regs)->cx;				\
	(pr_reg)[12] = (regs)->dx;				\
	(pr_reg)[13] = (regs)->si;				\
	(pr_reg)[14] = (regs)->di;				\
	(pr_reg)[15] = (regs)->orig_ax;				\
	(pr_reg)[16] = (regs)->ip;				\
	(pr_reg)[17] = (regs)->cs;				\
	(pr_reg)[18] = (regs)->flags;				\
	(pr_reg)[19] = (regs)->sp;				\
	(pr_reg)[20] = (regs)->ss;				\
	(pr_reg)[21] = current->thread.fs;			\
	(pr_reg)[22] = current->thread.gs;			\
	asm("movl %%ds,%0" : "=r" (v)); (pr_reg)[23] = v;	\
	asm("movl %%es,%0" : "=r" (v)); (pr_reg)[24] = v;	\
	asm("movl %%fs,%0" : "=r" (v)); (pr_reg)[25] = v;	\
	asm("movl %%gs,%0" : "=r" (v)); (pr_reg)[26] = v;	\
} while (0);

/*                                     */
#define ELF_PLATFORM       ("x86_64")
extern void set_personality_64bit(void);
extern unsigned int sysctl_vsyscall32;
extern int force_personality32;

#endif /*                */

#define CORE_DUMP_USE_REGSET
#define ELF_EXEC_PAGESIZE	4096

/*                                                                           
                                                                           
                                                                             
                                                                        */

#define ELF_ET_DYN_BASE		(TASK_SIZE / 3 * 2)

/*                                                                 
                                                                        
                                                       */

#define ELF_HWCAP		(boot_cpu_data.x86_capability[0])

/*                                                                
                                                                 
                                                

                                                                        
                            */

#define SET_PERSONALITY(ex) set_personality_64bit()

/*
                                                                    
                                                                 
 */
#define elf_read_implies_exec(ex, executable_stack)	\
	(executable_stack != EXSTACK_DISABLE_X)

struct task_struct;

#define	ARCH_DLINFO_IA32(vdso_enabled)					\
do {									\
	if (vdso_enabled) {						\
		NEW_AUX_ENT(AT_SYSINFO,	VDSO_ENTRY);			\
		NEW_AUX_ENT(AT_SYSINFO_EHDR, VDSO_CURRENT_BASE);	\
	}								\
} while (0)

#ifdef CONFIG_X86_32

#define STACK_RND_MASK (0x7ff)

#define VDSO_HIGH_BASE		(__fix_to_virt(FIX_VDSO))

#define ARCH_DLINFO		ARCH_DLINFO_IA32(vdso_enabled)

/*                                                                         */

#else /*               */

#define VDSO_HIGH_BASE		0xffffe000U /*                            */

/*                              */
#define STACK_RND_MASK (test_thread_flag(TIF_ADDR32) ? 0x7ff : 0x3fffff)

#define ARCH_DLINFO							\
do {									\
	if (vdso_enabled)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
			    (unsigned long)current->mm->context.vdso);	\
} while (0)

#define ARCH_DLINFO_X32							\
do {									\
	if (vdso_enabled)						\
		NEW_AUX_ENT(AT_SYSINFO_EHDR,				\
			    (unsigned long)current->mm->context.vdso);	\
} while (0)

#define AT_SYSINFO		32

#define COMPAT_ARCH_DLINFO						\
if (test_thread_flag(TIF_X32))						\
	ARCH_DLINFO_X32;						\
else									\
	ARCH_DLINFO_IA32(sysctl_vsyscall32)

#define COMPAT_ELF_ET_DYN_BASE	(TASK_UNMAPPED_BASE + 0x1000000)

#endif /*                */

#define VDSO_CURRENT_BASE	((unsigned long)current->mm->context.vdso)

#define VDSO_ENTRY							\
	((unsigned long)VDSO32_SYMBOL(VDSO_CURRENT_BASE, vsyscall))

struct linux_binprm;

#define ARCH_HAS_SETUP_ADDITIONAL_PAGES 1
extern int arch_setup_additional_pages(struct linux_binprm *bprm,
				       int uses_interp);
extern int x32_setup_additional_pages(struct linux_binprm *bprm,
				      int uses_interp);

extern int syscall32_setup_pages(struct linux_binprm *, int exstack);
#define compat_arch_setup_additional_pages	syscall32_setup_pages

extern unsigned long arch_randomize_brk(struct mm_struct *mm);
#define arch_randomize_brk arch_randomize_brk

/*
                                                  
 */
static inline int mmap_is_ia32(void)
{
#ifdef CONFIG_X86_32
	return 1;
#endif
#ifdef CONFIG_IA32_EMULATION
	if (test_thread_flag(TIF_ADDR32))
		return 1;
#endif
	return 0;
}

/*                                                                   */
enum align_flags {
	ALIGN_VA_32	= BIT(0),
	ALIGN_VA_64	= BIT(1),
	ALIGN_VDSO	= BIT(2),
	ALIGN_TOPDOWN	= BIT(3),
};

struct va_alignment {
	int flags;
	unsigned long mask;
} ____cacheline_aligned;

extern struct va_alignment va_align;
extern unsigned long align_addr(unsigned long, struct file *, enum align_flags);
#endif /*                */
