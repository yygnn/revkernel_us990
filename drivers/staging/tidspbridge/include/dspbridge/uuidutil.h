/*
 * uuidutil.h
 *
 * DSP-BIOS Bridge driver support functions for TI OMAP processors.
 *
 * This file contains the specification of UUID helper functions.
 *
 * Copyright (C) 2005-2006 Texas Instruments, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef UUIDUTIL_
#define UUIDUTIL_

#define MAXUUIDLEN  37

/*
                                         
            
                                              
               
                                                    
                                                                         
                           
                                                     
            
             
                                               
            
                                                   
            
                                                      
 */
void uuid_uuid_to_string(struct dsp_uuid *uuid_obj, char *sz_uuid,
			 s32 size);

/*
                                           
            
                                              
               
                                                                          
                                                    
            
             
                                               
            
            
                                                                               
                                               
 */
extern void uuid_uuid_from_string(char *sz_uuid,
				  struct dsp_uuid *uuid_obj);

#endif /*           */
