/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datensysteme GmbH.
 *
 *	See the file "skfddi.c" for further information.
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	The information in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
        
                               
                                   
*/

/*
                                                    
                                                        
  
                  
                      
                     
  
                                                                  
                       
                     
                   
   
                                                    
        
  
 */

#include "h/types.h"
#include "h/fddi.h"
#include "h/smc.h"

#define KERNEL
#include "h/smtstate.h"

#ifndef	lint
static const char ID_sccs[] = "@(#)ecm.c	2.7 99/08/05 (C) SK " ;
#endif

/*
             
 */
#define AFLAG	0x10
#define GO_STATE(x)	(smc->mib.fddiSMTECMState = (x)|AFLAG)
#define ACTIONS_DONE()	(smc->mib.fddiSMTECMState &= ~AFLAG)
#define ACTIONS(x)	(x|AFLAG)

#define EC0_OUT		0			/*              */
#define EC1_IN		1			/*          */
#define EC2_TRACE	2			/*         */
#define EC3_LEAVE	3			/*                  */
#define EC4_PATH_TEST	4			/*                      */
#define EC5_INSERT	5			/*                        */
#define EC6_CHECK	6			/*                 */
#define EC7_DEINSERT	7			/*                         */

#ifdef	DEBUG
/*
                       
 */
static const char * const ecm_states[] = {
	"EC0_OUT","EC1_IN","EC2_TRACE","EC3_LEAVE","EC4_PATH_TEST",
	"EC5_INSERT","EC6_CHECK","EC7_DEINSERT"
} ;

/*
                       
 */
static const char * const ecm_events[] = {
	"NONE","EC_CONNECT","EC_DISCONNECT","EC_TRACE_PROP","EC_PATH_TEST",
	"EC_TIMEOUT_TD","EC_TIMEOUT_TMAX",
	"EC_TIMEOUT_IMAX","EC_TIMEOUT_INMAX","EC_TEST_DONE"
} ;
#endif

/*
                                    
               
 */

/*
                        
 */

static void ecm_fsm(struct s_smc *smc, int cmd);
static void start_ecm_timer(struct s_smc *smc, u_long value, int event);
static void stop_ecm_timer(struct s_smc *smc);
static void prop_actions(struct s_smc *smc);

/*
                       
                             
*/
void ecm_init(struct s_smc *smc)
{
	smc->e.path_test = PT_PASSED ;
	smc->e.trace_prop = 0 ;
	smc->e.sb_flag = 0 ;
	smc->mib.fddiSMTECMState = ACTIONS(EC0_OUT) ;
	smc->e.ecm_line_state = FALSE ;
}

/*
                  
                     

   
                      
               
                   
*/
void ecm(struct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_ECM("ECM : state %s%s",
			(smc->mib.fddiSMTECMState & AFLAG) ? "ACTIONS " : "",
			ecm_states[smc->mib.fddiSMTECMState & ~AFLAG]) ;
		DB_ECM(" event %s\n",ecm_events[event],0) ;
		state = smc->mib.fddiSMTECMState ;
		ecm_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.fddiSMTECMState) ;
	ecm_state_change(smc,(int)smc->mib.fddiSMTECMState) ;
}

/*
                  
*/
static void ecm_fsm(struct s_smc *smc, int cmd)
{
	int ls_a ;			/*                          */
	int ls_b ;			/*                          */
	int	p ;			/*       */


	smc->mib.fddiSMTBypassPresent = sm_pm_bypass_present(smc) ;
	if (cmd == EC_CONNECT)
		smc->mib.fddiSMTRemoteDisconnectFlag = FALSE ;

	/*                             */
	/*                                            */
	if (cmd == EC_DISCONNECT &&
		smc->mib.fddiSMTRemoteDisconnectFlag == TRUE)
		AIX_EVENT (smc, (u_long) CIO_HARD_FAIL, (u_long)
			FDDI_REMOTE_DISCONNECT, smt_get_event_word(smc),
			smt_get_error_word(smc) );

	/*                                                                  */
	if (cmd == EC_CONNECT) {
		smc->e.DisconnectFlag = FALSE ;
	}
	else if (cmd == EC_DISCONNECT) {
		smc->e.DisconnectFlag = TRUE ;
	}
	
	switch(smc->mib.fddiSMTECMState) {
	case ACTIONS(EC0_OUT) :
		/*
                                  
   */
		smc->e.path_test = PT_PASSED ;
		smc->e.ecm_line_state = FALSE ;
		stop_ecm_timer(smc) ;
		ACTIONS_DONE() ;
		break ;
	case EC0_OUT:
		/*    */
		if (cmd == EC_CONNECT && !smc->mib.fddiSMTBypassPresent
			&& smc->e.path_test==PT_PASSED) {
			GO_STATE(EC1_IN) ;
			break ;
		}
		/*    */
		else if (cmd == EC_CONNECT && (smc->e.path_test==PT_PASSED) &&
			smc->mib.fddiSMTBypassPresent &&
			(smc->s.sas == SMT_DAS)) {
			GO_STATE(EC5_INSERT) ;
			break ;
		}
		break;
	case ACTIONS(EC1_IN) :
		stop_ecm_timer(smc) ;
		smc->e.trace_prop = 0 ;
		sm_ma_control(smc,MA_TREQ) ;
		for (p = 0 ; p < NUMPHYS ; p++)
			if (smc->mib.p[p].fddiPORTHardwarePresent)
				queue_event(smc,EVENT_PCMA+p,PC_START) ;
		ACTIONS_DONE() ;
		break ;
	case EC1_IN:
		/*    */
		if (cmd == EC_TRACE_PROP) {
			prop_actions(smc) ;
			GO_STATE(EC2_TRACE) ;
			break ;
		}
		/*    */
		else if (cmd == EC_DISCONNECT) {
			GO_STATE(EC3_LEAVE) ;
			break ;
		}
		break;
	case ACTIONS(EC2_TRACE) :
		start_ecm_timer(smc,MIB2US(smc->mib.fddiSMTTrace_MaxExpiration),
			EC_TIMEOUT_TMAX) ;
		ACTIONS_DONE() ;
		break ;
	case EC2_TRACE :
		/*    */
		if (cmd == EC_TRACE_PROP) {
			prop_actions(smc) ;
			GO_STATE(EC2_TRACE) ;
			break ;
		}
		/*     */
		else if (cmd == EC_DISCONNECT) {
			smc->e.path_test = PT_EXITING ;
			GO_STATE(EC3_LEAVE) ;
			break ;
		}
		/*     */
		else if (smc->e.path_test == PT_PENDING) {
			GO_STATE(EC3_LEAVE) ;
			break ;
		}
		/*     */
		else if (cmd == EC_TIMEOUT_TMAX) {
			/*                      */
			/*                   */
			AIX_EVENT(smc, (u_long) FDDI_RING_STATUS,
				(u_long) FDDI_SMT_ERROR, (u_long)
				FDDI_TRACE_MAX, smt_get_error_word(smc));
			smc->e.path_test = PT_PENDING ;
			GO_STATE(EC3_LEAVE) ;
			break ;
		}
		break ;
	case ACTIONS(EC3_LEAVE) :
		start_ecm_timer(smc,smc->s.ecm_td_min,EC_TIMEOUT_TD) ;
		for (p = 0 ; p < NUMPHYS ; p++)
			queue_event(smc,EVENT_PCMA+p,PC_STOP) ;
		ACTIONS_DONE() ;
		break ;
	case EC3_LEAVE:
		/*    */
		if (cmd == EC_TIMEOUT_TD && !smc->mib.fddiSMTBypassPresent &&
			(smc->e.path_test != PT_PENDING)) {
			GO_STATE(EC0_OUT) ;
			break ;
		}
		/*    */
		else if (cmd == EC_TIMEOUT_TD &&
			(smc->e.path_test == PT_PENDING)) {
			GO_STATE(EC4_PATH_TEST) ;
			break ;
		}
		/*    */
		else if (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) {
			GO_STATE(EC1_IN) ;
			break ;
		}
		/*    */
		else if (cmd == EC_DISCONNECT &&
			smc->e.path_test == PT_PENDING) {
			smc->e.path_test = PT_EXITING ;
			/*
                                                    
    */
		}
		/*    */
		else if (cmd == EC_TIMEOUT_TD &&
			smc->mib.fddiSMTBypassPresent &&
			smc->e.path_test != PT_PENDING) {
			GO_STATE(EC7_DEINSERT) ;
			break ;
		}
		break ;
	case ACTIONS(EC4_PATH_TEST) :
		stop_ecm_timer(smc) ;
		smc->e.path_test = PT_TESTING ;
		start_ecm_timer(smc,smc->s.ecm_test_done,EC_TEST_DONE) ;
		/*                                             */
		ACTIONS_DONE() ;
		break ;
	case EC4_PATH_TEST :
		/*                      */
		if (cmd == EC_TEST_DONE)
			smc->e.path_test = PT_PASSED ;

		if (smc->e.path_test == PT_FAILED)
			RS_SET(smc,RS_PATHTEST) ;

		/*     */
		if (smc->e.path_test == PT_FAILED &&
			!smc->mib.fddiSMTBypassPresent) {
			GO_STATE(EC0_OUT) ;
			break ;
		}
		/*     */
		else if (cmd == EC_DISCONNECT &&
			!smc->mib.fddiSMTBypassPresent) {
			GO_STATE(EC0_OUT) ;
			break ;
		}
		/*    */
		else if (smc->e.path_test == PT_PASSED) {
			GO_STATE(EC1_IN) ;
			break ;
		}
		/*     */
		else if (smc->e.path_test == PT_FAILED &&
			smc->mib.fddiSMTBypassPresent) {
			GO_STATE(EC7_DEINSERT) ;
			break ;
		}
		/*     */
		else if (cmd == EC_DISCONNECT &&
			smc->mib.fddiSMTBypassPresent) {
			GO_STATE(EC7_DEINSERT) ;
			break ;
		}
		break ;
	case ACTIONS(EC5_INSERT) :
		sm_pm_bypass_req(smc,BP_INSERT);
		start_ecm_timer(smc,smc->s.ecm_in_max,EC_TIMEOUT_INMAX) ;
		ACTIONS_DONE() ;
		break ;
	case EC5_INSERT :
		/*    */
		if (cmd == EC_TIMEOUT_INMAX) {
			GO_STATE(EC6_CHECK) ;
			break ;
		}
		/*    */
		else if (cmd == EC_DISCONNECT) {
			GO_STATE(EC7_DEINSERT) ;
			break ;
		}
		break ;
	case ACTIONS(EC6_CHECK) :
		/*
                                             
                                                      
   */
		start_ecm_timer(smc,smc->s.ecm_check_poll,0) ;
		smc->e.ecm_line_state = TRUE ;	/*                           */
		(void) sm_pm_ls_latch(smc,PA,1) ; /*                         */
		(void) sm_pm_ls_latch(smc,PB,1) ; /*                         */
		ACTIONS_DONE() ;
		break ;
	case EC6_CHECK :
		ls_a = sm_pm_get_ls(smc,PA) ;
		ls_b = sm_pm_get_ls(smc,PB) ;

		/*    */
		if (((ls_a == PC_QLS) || (ls_a == PC_HLS)) &&
		    ((ls_b == PC_QLS) || (ls_b == PC_HLS)) ) {
			smc->e.sb_flag = FALSE ;
			smc->e.ecm_line_state = FALSE ;
			GO_STATE(EC1_IN) ;
			break ;
		}
		/*    */
		else if (!smc->e.sb_flag &&
			 (((ls_a == PC_ILS) && (ls_b == PC_QLS)) ||
			  ((ls_a == PC_QLS) && (ls_b == PC_ILS)))){
			smc->e.sb_flag = TRUE ;
			DB_ECMN(1,"ECM : EC6_CHECK - stuck bypass\n",0,0) ;
			AIX_EVENT(smc, (u_long) FDDI_RING_STATUS, (u_long)
				FDDI_SMT_ERROR, (u_long) FDDI_BYPASS_STUCK,
				smt_get_error_word(smc));
		}
		/*    */
		else if (cmd == EC_DISCONNECT) {
			smc->e.ecm_line_state = FALSE ;
			GO_STATE(EC7_DEINSERT) ;
			break ;
		}
		else {
			/*
                  
    */
			start_ecm_timer(smc,smc->s.ecm_check_poll,0) ;
		}
		break ;
	case ACTIONS(EC7_DEINSERT) :
		sm_pm_bypass_req(smc,BP_DEINSERT);
		start_ecm_timer(smc,smc->s.ecm_i_max,EC_TIMEOUT_IMAX) ;
		ACTIONS_DONE() ;
		break ;
	case EC7_DEINSERT:
		/*    */
		if (cmd == EC_TIMEOUT_IMAX) {
			GO_STATE(EC0_OUT) ;
			break ;
		}
		/*    */
		else if (cmd == EC_CONNECT && smc->e.path_test == PT_PASSED) {
			GO_STATE(EC5_INSERT) ;
			break ;
		}
		break;
	default:
		SMT_PANIC(smc,SMT_E0107, SMT_E0107_MSG) ;
		break;
	}
}

#ifndef	CONCENTRATOR
/*
                                          
 */
static void prop_actions(struct s_smc *smc)
{
	int	port_in = 0 ;
	int	port_out = 0 ;

	RS_SET(smc,RS_EVENT) ;
	switch (smc->s.sas) {
	case SMT_SAS :
		port_in = port_out = pcm_get_s_port(smc) ;
		break ;
	case SMT_DAS :
		port_in = cfm_get_mac_input(smc) ;	/*          */
		port_out = cfm_get_mac_output(smc) ;	/*          */
		break ;
	case SMT_NAC :
		SMT_PANIC(smc,SMT_E0108, SMT_E0108_MSG) ;
		return ;
	}

	DB_ECM("ECM : prop_actions - trace_prop %d\n", smc->e.trace_prop,0) ;
	DB_ECM("ECM : prop_actions - in %d out %d\n", port_in,port_out) ;

	if (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) {
		/*                  */
		DB_ECM("ECM : initiate TRACE on PHY %c\n",'A'+port_in-PA,0) ;
		queue_event(smc,EVENT_PCM+port_in,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PA))) &&
		port_out != PA) {
		/*                          */
		DB_ECM("ECM : propagate TRACE on PHY B\n",0,0) ;
		queue_event(smc,EVENT_PCMB,PC_TRACE) ;
	}
	else if ((smc->e.trace_prop & ENTITY_BIT(ENTITY_PHY(PB))) &&
		port_out != PB) {
		/*                          */
		DB_ECM("ECM : propagate TRACE on PHY A\n",0,0) ;
		queue_event(smc,EVENT_PCMA,PC_TRACE) ;
	}
	else {
		/*                          */
		DB_ECM("ECM : TRACE terminated\n",0,0) ;
		smc->e.path_test = PT_PENDING ;
	}
	smc->e.trace_prop = 0 ;
}
#else
/*
                                             
 */
static void prop_actions(struct s_smc *smc)
{
	int	initiator ;
	int	upstream ;
	int	p ;

	RS_SET(smc,RS_EVENT) ;
	while (smc->e.trace_prop) {
		DB_ECM("ECM : prop_actions - trace_prop %d\n",
			smc->e.trace_prop,0) ;

		if (smc->e.trace_prop & ENTITY_BIT(ENTITY_MAC)) {
			initiator = ENTITY_MAC ;
			smc->e.trace_prop &= ~ENTITY_BIT(ENTITY_MAC) ;
			DB_ECM("ECM: MAC initiates trace\n",0,0) ;
		}
		else {
			for (p = NUMPHYS-1 ; p >= 0 ; p--) {
				if (smc->e.trace_prop &
					ENTITY_BIT(ENTITY_PHY(p)))
					break ;
			}
			initiator = ENTITY_PHY(p) ;
			smc->e.trace_prop &= ~ENTITY_BIT(ENTITY_PHY(p)) ;
		}
		upstream = cem_get_upstream(smc,initiator) ;

		if (upstream == ENTITY_MAC) {
			/*                          */
			DB_ECM("ECM : TRACE terminated\n",0,0) ;
			smc->e.path_test = PT_PENDING ;
		}
		else {
			/*                          */
			DB_ECM("ECM : propagate TRACE on PHY %d\n",upstream,0) ;
			queue_event(smc,EVENT_PCM+upstream,PC_TRACE) ;
		}
	}
}
#endif


/*
                      
                  
 */
static void start_ecm_timer(struct s_smc *smc, u_long value, int event)
{
	smt_timer_start(smc,&smc->e.ecm_timer,value,EV_TOKEN(EVENT_ECM,event));
}

/*
                      
                 
 */
static void stop_ecm_timer(struct s_smc *smc)
{
	if (smc->e.ecm_timer.tm_active)
		smt_timer_stop(smc,&smc->e.ecm_timer) ;
}
