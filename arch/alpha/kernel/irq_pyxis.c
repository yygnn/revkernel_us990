/*
                                      
  
                                                                            
  
                                                 
 */

#include <linux/init.h>
#include <linux/sched.h>
#include <linux/irq.h>

#include <asm/io.h>
#include <asm/core_cia.h>

#include "proto.h"
#include "irq_impl.h"


/*                                          */
static unsigned long cached_irq_mask;

static inline void
pyxis_update_irq_hw(unsigned long mask)
{
	*(vulp)PYXIS_INT_MASK = mask;
	mb();
	*(vulp)PYXIS_INT_MASK;
}

static inline void
pyxis_enable_irq(struct irq_data *d)
{
	pyxis_update_irq_hw(cached_irq_mask |= 1UL << (d->irq - 16));
}

static void
pyxis_disable_irq(struct irq_data *d)
{
	pyxis_update_irq_hw(cached_irq_mask &= ~(1UL << (d->irq - 16)));
}

static void
pyxis_mask_and_ack_irq(struct irq_data *d)
{
	unsigned long bit = 1UL << (d->irq - 16);
	unsigned long mask = cached_irq_mask &= ~bit;

	/*                         */
	*(vulp)PYXIS_INT_MASK = mask;
	wmb();
	/*                           */
	*(vulp)PYXIS_INT_REQ = bit;
	mb();
	/*                                */
	*(vulp)PYXIS_INT_MASK;
}

static struct irq_chip pyxis_irq_type = {
	.name		= "PYXIS",
	.irq_mask_ack	= pyxis_mask_and_ack_irq,
	.irq_mask	= pyxis_disable_irq,
	.irq_unmask	= pyxis_enable_irq,
};

void 
pyxis_device_interrupt(unsigned long vector)
{
	unsigned long pld;
	unsigned int i;

	/*                                              */
	pld = *(vulp)PYXIS_INT_REQ;
	pld &= cached_irq_mask;

	/*
                                                              
                                      
  */
	while (pld) {
		i = ffz(~pld);
		pld &= pld - 1; /*                     */
		if (i == 7)
			isa_device_interrupt(vector);
		else
			handle_irq(16+i);
	}
}

void __init
init_pyxis_irqs(unsigned long ignore_mask)
{
	long i;

	*(vulp)PYXIS_INT_MASK = 0;		/*             */
	*(vulp)PYXIS_INT_REQ  = -1;		/*           */
	mb();

	/*                                                      */
	*(vuip) CIA_IACK_SC;

	for (i = 16; i < 48; ++i) {
		if ((ignore_mask >> i) & 1)
			continue;
		irq_set_chip_and_handler(i, &pyxis_irq_type, handle_level_irq);
		irq_set_status_flags(i, IRQ_LEVEL);
	}

	setup_irq(16+7, &isa_cascade_irqaction);
}
