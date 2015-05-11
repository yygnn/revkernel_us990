/*                                                                            
                   
  
                                                                         
  
                  
                   
                            
                                   
                                   
                                            
                                                 
                                                            
                    
                                   
                                            
                                   
                                             
                                                                              */

#ifndef _MAC_Structures_H_
#define _MAC_Structures_H_

#define MAC_ADDR_LENGTH                     6

/*                                                         
                      
        */
#define DOT_11_MAC_HEADER_SIZE		24
#define DOT_11_SNAP_SIZE			6
#define DOT_11_DURATION_OFFSET		2
/*                         */
#define DOT_11_SEQUENCE_OFFSET		22
/*                                    */
#define DOT_11_TYPE_OFFSET			30
#define DOT_11_DATA_OFFSET          24
#define DOT_11_DA_OFFSET			4

#define MAX_ETHERNET_PACKET_SIZE		1514

/*                                                                          */
#define MAC_SUBTYPE_MNGMNT_ASSOC_REQUEST    0x00
#define MAC_SUBTYPE_MNGMNT_ASSOC_RESPONSE   0x10
#define MAC_SUBTYPE_MNGMNT_REASSOC_REQUEST  0x20
#define MAC_SUBTYPE_MNGMNT_REASSOC_RESPONSE 0x30
#define MAC_SUBTYPE_MNGMNT_PROBE_REQUEST    0x40
#define MAC_SUBTYPE_MNGMNT_PROBE_RESPONSE   0x50
#define MAC_SUBTYPE_MNGMNT_BEACON           0x80
#define MAC_SUBTYPE_MNGMNT_ATIM             0x90
#define MAC_SUBTYPE_MNGMNT_DISASSOCIATION   0xA0
#define MAC_SUBTYPE_MNGMNT_AUTHENTICATION   0xB0
#define MAC_SUBTYPE_MNGMNT_DEAUTHENTICATION 0xC0

#define RATE_AUTO					0
#define RATE_1M						2
#define RATE_2M						4
#define RATE_5dot5M					11
#define RATE_6M						12
#define RATE_9M						18
#define RATE_11M					22
#define RATE_12M					24
#define RATE_18M					36
#define RATE_22M					44
#define RATE_24M					48
#define RATE_33M					66
#define RATE_36M					72
#define RATE_48M					96
#define RATE_54M					108
#define RATE_MAX					255

#endif /*                   */
