/*
 * OMAP2xxx clockdomains
 *
 * Copyright (C) 2008-2009 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Paul Walmsley, Jouni Högander
 *
 * This file contains clockdomains and clockdomain wakeup dependencies
 * for OMAP2xxx chips.  Some notes:
 *
 * A useful validation rule for struct clockdomain: Any clockdomain
 * referenced by a wkdep_srcs must have a dep_bit assigned.  So
 * wkdep_srcs are really just software-controllable dependencies.
 * Non-software-controllable dependencies do exist, but they are not
 * encoded below (yet).
 *
 * 24xx does not support programmable sleep dependencies (SLEEPDEP)
 *
 * The overly-specific dep_bit names are due to a bit name collision
 * with CM_FCLKEN_{DSP,IVA2}.  The DSP/IVA2 PM_WKDEP and CM_SLEEPDEP shift
 * value are the same for all powerdomains: 2
 *
 * XXX should dep_bit be a mask, so we can test to see if it is 0 as a
 * sanity check?
 * XXX encode hardware fixed wakeup dependencies -- esp. for 3430 CORE
 */

/*
             
                                                        
                                     
 */

#include <linux/kernel.h>
#include <linux/io.h>

#include "clockdomain.h"
#include "prm2xxx_3xxx.h"
#include "cm2xxx_3xxx.h"
#include "cm-regbits-24xx.h"
#include "prm-regbits-24xx.h"

/*
                                      
  
                                                               
                                                                 
 */

/*                                 */

/*                                            */

/*                                              */
static struct clkdm_dep core_2430_wkdeps[] = {
	{ .clkdm_name = "dsp_clkdm" },
	{ .clkdm_name = "gfx_clkdm" },
	{ .clkdm_name = "mpu_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ .clkdm_name = "mdm_clkdm" },
	{ NULL },
};

/*                                         */
static struct clkdm_dep mpu_2430_wkdeps[] = {
	{ .clkdm_name = "core_l3_clkdm" },
	{ .clkdm_name = "core_l4_clkdm" },
	{ .clkdm_name = "dsp_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ .clkdm_name = "mdm_clkdm" },
	{ NULL },
};

/*                                    */
static struct clkdm_dep mdm_2430_wkdeps[] = {
	{ .clkdm_name = "core_l3_clkdm" },
	{ .clkdm_name = "core_l4_clkdm" },
	{ .clkdm_name = "mpu_clkdm" },
	{ .clkdm_name = "wkup_clkdm" },
	{ NULL },
};

/*
                         
 */

static struct clockdomain mpu_2430_clkdm = {
	.name		= "mpu_clkdm",
	.pwrdm		= { .name = "mpu_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= mpu_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_MPU_MASK,
};

/*                                                                       */
static struct clockdomain mdm_clkdm = {
	.name		= "mdm_clkdm",
	.pwrdm		= { .name = "mdm_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP2430_PM_WKDEP_MPU_EN_MDM_SHIFT,
	.wkdep_srcs	= mdm_2430_wkdeps,
	.clktrctrl_mask = OMAP2430_AUTOSTATE_MDM_MASK,
};

static struct clockdomain dsp_2430_clkdm = {
	.name		= "dsp_clkdm",
	.pwrdm		= { .name = "dsp_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP24XX_PM_WKDEP_MPU_EN_DSP_SHIFT,
	.wkdep_srcs	= dsp_24xx_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSP_MASK,
};

static struct clockdomain gfx_2430_clkdm = {
	.name		= "gfx_clkdm",
	.pwrdm		= { .name = "gfx_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_24xx_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_GFX_MASK,
};

/*
                                                                     
                                                                    
                      
 */
static struct clockdomain core_l3_2430_clkdm = {
	.name		= "core_l3_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_CORE_SHIFT,
	.wkdep_srcs	= core_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L3_MASK,
};

/*
                                                                     
                                                                    
                      
 */
static struct clockdomain core_l4_2430_clkdm = {
	.name		= "core_l4_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_CORE_SHIFT,
	.wkdep_srcs	= core_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L4_MASK,
};

static struct clockdomain dss_2430_clkdm = {
	.name		= "dss_clkdm",
	.pwrdm		= { .name = "core_pwrdm" },
	.flags		= CLKDM_CAN_HWSUP,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSS_MASK,
};

static struct clockdomain *clockdomains_omap243x[] __initdata = {
	&wkup_common_clkdm,
	&cm_common_clkdm,
	&prm_common_clkdm,
	&mpu_2430_clkdm,
	&mdm_clkdm,
	&dsp_2430_clkdm,
	&gfx_2430_clkdm,
	&core_l3_2430_clkdm,
	&core_l4_2430_clkdm,
	&dss_2430_clkdm,
	NULL,
};

void __init omap243x_clockdomains_init(void)
{
	if (!cpu_is_omap243x())
		return;

	clkdm_register_platform_funcs(&omap2_clkdm_operations);
	clkdm_register_clkdms(clockdomains_omap243x);
	clkdm_complete_init();
}
