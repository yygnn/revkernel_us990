/*
 * Copyright (c) 2012-2013 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#ifndef BTAMPHCI_H
#define BTAMPHCI_H

/* 
                    
   
                                                        
                                  
   
   

   
   
                                                      
                                                        
   
                 
    
                                        
   
                                                   
                                                      
                                           
   
   
  */


#define WLANBAP_MAX_LOG_LINKS 16  /*                                   */


#if 0

/*                                                                          */

/*                                                                          

                               

              
                                                         


               


             
 

      
                                                                     
                                                       
                                                                         
                                                                                   
   
              

                                                              
 

               

                                                                            */
v_U32_t Unpack_XxxMessage(void *, v_U8_t*,v_U16_t, tXxxMessage*);


/*                                                                          

                             

              
                                                          


               


             


      
                                                                     
                                                                        
                                                             
                                                                     
                                                                                        


              

                                                              

               


                                                                            */
v_U32_t Pack_XxxMessage(void *, tXxxMessage*, v_U8_t*, v_U32_t, v_U32_t*);

#endif
 

typedef v_U32_t tBTAMP_U64[2];

#if defined ( _MSC_VER )
#   pragma warning (disable: 4214) /*                            */
#endif /*                                                            */

/*
                       
  
                                                                        
                                                                       
                                                                      
                   
  
                                                                     
                                                                       
                           
  
  
 */

#define BTAMP_PARSE_SUCCESS         ( 0x00000000 )
#define BTAMP_UNKNOWN_IES           ( 0x00000001 )
#define BTAMP_MANDATORY_IE_MISSING  ( 0x00000002 )
#define BTAMP_INCOMPLETE_IE         ( 0x00000004 )
#define BTAMP_SKIPPED_BAD_IE        ( 0x00000008 )
#define BTAMP_LAST_IE_TOO_LONG      ( 0x00000010 )
#define BTAMP_DUPLICATE_IE          ( 0x00000020 )
#define BTAMP_BAD_FIXED_VALUE       ( 0x00000040 )
#define BTAMP_INCOMPLETE_TLV        ( 0x00000080 )
#define BTAMP_INVALID_TLV_LENGTH    ( 0x00000100 )
#define BTAMP_SKIPPED_BAD_TLV       ( 0x00000200 )
#define BTAMP_UNKNOWN_TLVS          ( 0x00000400 )
#define BTAMP_LAST_TLV_TOO_LONG     ( 0x00000800 )
#define BTAMP_INTERNAL_ERROR        ( 0x10000001 )
#define BTAMP_MISSING_FIXED_FIELD   ( 0x10000002 )
#define BTAMP_BAD_INPUT_BUFFER      ( 0x10000003 )
#define BTAMP_BAD_OUTPUT_BUFFER     ( 0x10000004 )
#define BTAMP_BUFFER_OVERFLOW       ( 0x10000005 )
#define BTAMP_MANDATORY_TLV_MISSING ( 0x00001000 )
#define BTAMP_FAILED(code)          ( (code) & 0x10000000 )
#define BTAMP_WARNED(code)          ( ( ( 0 == (code) ) & 0x10000000 ) && code)
#define BTAMP_SUCCEEDED(code)       ( (code) == 0 )

/*                                                                    
                                                                      
                                                                    */

/*                                                                    
                                                                      
                                                                    */

//              
typedef struct sBtampTLVAMP_Assoc_Connected_Channel {
    v_U8_t       present;
    v_U8_t       country[3];
    v_U8_t       num_triplets;
    v_U8_t       triplets[5][3];
} tBtampTLVAMP_Assoc_Connected_Channel;

#define BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL ( 3 )

//                                                     
#define BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL_MIN_LEN ( 5 )

#define BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL_MAX_LEN ( 11 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvAMP_Assoc_Connected_Channel(void *, v_U8_t*,v_U16_t, tBtampTLVAMP_Assoc_Connected_Channel*);

v_U32_t btampPackTlvAMP_Assoc_Connected_Channel(void *, tBtampTLVAMP_Assoc_Connected_Channel*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvAMP_Assoc_Connected_Channel(void *, tBtampTLVAMP_Assoc_Connected_Channel*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//              
typedef struct sBtampTLVAMP_Assoc_MAC_Addr {
    v_U8_t       present;
    v_U8_t       mac_addr[6];
} tBtampTLVAMP_Assoc_MAC_Addr;

#define BTAMP_TLV_AMP_ASSOC_MAC_ADDR ( 1 )

//                                                     
#define BTAMP_TLV_AMP_ASSOC_MAC_ADDR_MIN_LEN ( 8 )

#define BTAMP_TLV_AMP_ASSOC_MAC_ADDR_MAX_LEN ( 8 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvAMP_Assoc_MAC_Addr(void *, v_U8_t*,v_U16_t, tBtampTLVAMP_Assoc_MAC_Addr*);

v_U32_t btampPackTlvAMP_Assoc_MAC_Addr(void *, tBtampTLVAMP_Assoc_MAC_Addr*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvAMP_Assoc_MAC_Addr(void *, tBtampTLVAMP_Assoc_MAC_Addr*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//              
typedef struct sBtampTLVAMP_Assoc_PAL_Capabilities {
    v_U8_t       present;
    v_U32_t      pal_capabilities;
} tBtampTLVAMP_Assoc_PAL_Capabilities;

#define BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES ( 4 )

//                                                     
#define BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES_MIN_LEN ( 6 )

#define BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES_MAX_LEN ( 6 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvAMP_Assoc_PAL_Capabilities(void *, v_U8_t*,v_U16_t, tBtampTLVAMP_Assoc_PAL_Capabilities*);

v_U32_t btampPackTlvAMP_Assoc_PAL_Capabilities(void *, tBtampTLVAMP_Assoc_PAL_Capabilities*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvAMP_Assoc_PAL_Capabilities(void *, tBtampTLVAMP_Assoc_PAL_Capabilities*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//              
typedef struct sBtampTLVAMP_Assoc_PAL_Version {
    v_U8_t       present;
    v_U8_t       pal_version;
    v_U16_t      pal_CompanyID;
    v_U16_t      pal_subversion;
} tBtampTLVAMP_Assoc_PAL_Version;

#define BTAMP_TLV_AMP_ASSOC_PAL_VERSION ( 5 )

//                                                     
#define BTAMP_TLV_AMP_ASSOC_PAL_VERSION_MIN_LEN ( 7 )

#define BTAMP_TLV_AMP_ASSOC_PAL_VERSION_MAX_LEN ( 7 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvAMP_Assoc_PAL_Version(void *, v_U8_t*,v_U16_t, tBtampTLVAMP_Assoc_PAL_Version*);

v_U32_t btampPackTlvAMP_Assoc_PAL_Version(void *, tBtampTLVAMP_Assoc_PAL_Version*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvAMP_Assoc_PAL_Version(void *, tBtampTLVAMP_Assoc_PAL_Version*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//              
typedef struct sBtampTLVAMP_Assoc_Preferred_Channel_List {
    v_U8_t       present;
    v_U8_t       country[3];
    v_U8_t       num_triplets;
    v_U8_t       triplets[5][3];
} tBtampTLVAMP_Assoc_Preferred_Channel_List;

#define BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST ( 2 )

//                                                     
#define BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST_MIN_LEN ( 5 )

#define BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST_MAX_LEN ( 20 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvAMP_Assoc_Preferred_Channel_List(void *, v_U8_t*,v_U16_t, tBtampTLVAMP_Assoc_Preferred_Channel_List*);

v_U32_t btampPackTlvAMP_Assoc_Preferred_Channel_List(void *, tBtampTLVAMP_Assoc_Preferred_Channel_List*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvAMP_Assoc_Preferred_Channel_List(void *, tBtampTLVAMP_Assoc_Preferred_Channel_List*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//              
typedef struct sBtampTLVFlow_Spec {
    v_U8_t       present;
    v_U8_t       flow_spec_id;
    v_U8_t       service_type;
    v_U16_t      max_sdu;
    v_U32_t      sdu_inter_arrival;
    v_U32_t      access_latency;
    v_U32_t      flush_timeout;
} tBtampTLVFlow_Spec;

#define BTAMP_TLV_FLOW_SPEC ( 6 )

//                                                     
#define BTAMP_TLV_FLOW_SPEC_MIN_LEN ( 18 )

#define BTAMP_TLV_FLOW_SPEC_MAX_LEN ( 18 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvFlow_Spec(void *, v_U8_t*,v_U16_t, tBtampTLVFlow_Spec*);

v_U32_t btampPackTlvFlow_Spec(void *, tBtampTLVFlow_Spec*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvFlow_Spec(void *, tBtampTLVFlow_Spec*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Accept_Logical_Link_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       tx_flow_spec[18];
    v_U8_t       rx_flow_spec[18];
} tBtampTLVHCI_Accept_Logical_Link_Cmd;

#define BTAMP_TLV_HCI_ACCEPT_LOGICAL_LINK_CMD ( 1081 )

//                                                     
#define BTAMP_TLV_HCI_ACCEPT_LOGICAL_LINK_CMD_MIN_LEN ( 39 )

#define BTAMP_TLV_HCI_ACCEPT_LOGICAL_LINK_CMD_MAX_LEN ( 39 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Accept_Logical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Accept_Logical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Accept_Logical_Link_Cmd(void *, tBtampTLVHCI_Accept_Logical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Accept_Logical_Link_Cmd(void *, tBtampTLVHCI_Accept_Logical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Accept_Physical_Link_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       key_length;
    v_U8_t       key_type;
    v_U8_t       key_material[32];
} tBtampTLVHCI_Accept_Physical_Link_Cmd;

#define BTAMP_TLV_HCI_ACCEPT_PHYSICAL_LINK_CMD ( 1078 )

//                                                     
#define BTAMP_TLV_HCI_ACCEPT_PHYSICAL_LINK_CMD_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_ACCEPT_PHYSICAL_LINK_CMD_MAX_LEN ( 37 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Accept_Physical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Accept_Physical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Accept_Physical_Link_Cmd(void *, tBtampTLVHCI_Accept_Physical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Accept_Physical_Link_Cmd(void *, tBtampTLVHCI_Accept_Physical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Channel_Selected_Event {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
} tBtampTLVHCI_Channel_Selected_Event;

#define BTAMP_TLV_HCI_CHANNEL_SELECTED_EVENT ( 65 )

//                                                     
#define BTAMP_TLV_HCI_CHANNEL_SELECTED_EVENT_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_CHANNEL_SELECTED_EVENT_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Channel_Selected_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Channel_Selected_Event*);

v_U32_t btampPackTlvHCI_Channel_Selected_Event(void *, tBtampTLVHCI_Channel_Selected_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Channel_Selected_Event(void *, tBtampTLVHCI_Channel_Selected_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Command_Complete_Event {
    v_U8_t       present;
    v_U8_t       num_hci_command_packets;
    v_U16_t      command_opcode;
    union
    {
        struct
        {
            v_U8_t status;
        } Reset; /*                      */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
        } Flush; /*                      */
        struct
        {
            v_U8_t status;
            v_U8_t phy_link_handle;
            v_U8_t tx_flow_spec_id;
        } Logical_Link_Cancel; /*                      */
        struct
        {
            v_U8_t status;
        } Set_Event_Mask; /*                      */
        struct
        {
            v_U8_t status;
            v_U16_t connection_accept_timeout;
        } Read_Connection_Accept_TO; /*                      */
        struct
        {
            v_U8_t status;
        } Write_Connection_Accept_TO; /*                      */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
            v_U16_t link_supervision_timeout;
        } Read_Link_Supervision_TO; /*                      */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
        } Write_Link_Supervision_TO; /*                      */
        struct
        {
            v_U8_t status;
            v_U16_t logical_link_accept_timeout;
        } Read_Logical_Link_Accept_TO; /*                      */
        struct
        {
            v_U8_t status;
        } Write_Logical_Link_Accept_TO; /*                      */
        struct
        {
            v_U8_t status;
        } Set_Event_Mask_Page_2; /*                      */
        struct
        {
            v_U8_t status;
            v_U8_t loc_domain_aware;
            v_U8_t loc_domain[3];
            v_U8_t loc_options;
        } Read_Location_Data; /*                       */
        struct
        {
            v_U8_t status;
        } Write_Location_Data; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t flow_control_mode;
        } Read_Flow_Control_Mode; /*                       */
        struct
        {
            v_U8_t status;
        } Write_Flow_Control_Mode; /*                       */
        struct
        {
            v_U8_t status;
            v_U32_t best_effort_flush_timeout;
        } Read_BE_Flush_TO; /*                       */
        struct
        {
            v_U8_t status;
        } Write_BE_Flush_TO; /*                       */
        struct
        {
            v_U8_t status;
        } Set_Short_Range_Mode; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t HC_HCI_Version;
            v_U16_t HC_HCI_Revision;
            v_U8_t HC_PAL_Version;
            v_U16_t HC_Manufac_Name;
            v_U16_t HC_PAL_Sub_Version;
        } Read_Local_Version_Info; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t HC_Support_Cmds[64];
        } Read_Local_Supported_Cmds; /*                       */
        struct
        {
            v_U8_t status;
            v_U16_t HC_ACL_Data_Packet_Length;
            v_U8_t HC_SCO_Packet_Length;
            v_U16_t HC_Total_Num_ACL_Packets;
            v_U16_t HC_Total_Num_SCO_Packets;
        } Read_Buffer_Size; /*                       */
        struct
        {
            v_U8_t status;
            v_U16_t HC_Max_ACL_Data_Packet_Length;
            v_U16_t HC_Data_Block_Length;
            v_U16_t HC_Total_Num_Data_Blocks;
        } Read_Data_Block_Size; /*                       */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
            v_U16_t failed_contact_counter;
        } Read_Failed_Contact_Counter; /*                       */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
        } Reset_Failed_Contact_Counter; /*                       */
        struct
        {
            v_U8_t status;
            v_U16_t log_link_handle;
            v_U8_t link_quality;
        } Read_Link_Quality; /*                       */
        struct
        {
            v_U8_t status;
            /*                                                        */
            v_U16_t phy_link_handle;
            v_S7_t rssi;
        } Read_RSSI; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t HC_AMP_Status;
            v_U32_t HC_Total_BW;
            v_U32_t HC_Max_Guaranteed_BW;
            v_U32_t HC_Min_Latency;
            v_U32_t HC_Max_PDU_Size;
            v_U8_t HC_Controller_Type;
            v_U16_t HC_PAL_Capabilities;
            v_U16_t HC_AMP_Assoc_Length;
            v_U32_t HC_Max_Flush_Timeout;
            v_U32_t HC_BE_Flush_Timeout;
        } Read_Local_AMP_Info; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t phy_link_handle;
            v_U16_t remaining_length;
            v_U8_t AMP_assoc_fragment[248];
        } Read_Read_Local_AMP_Assoc; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t phy_link_handle;
        } Write_Remote_AMP_Assoc; /*                       */
        struct
        {
            v_U8_t status;
            v_U8_t loopback_mode;
        } Read_Loopback_Mode; /*                       */
        struct
        {
            v_U8_t status;
        } Write_Loopback_Mode; /*                       */
        struct
        {
            v_U8_t status;
        } Vendor_Specific_Cmd_0; /*                       */
        struct
        {
            v_U8_t status;
        } Vendor_Specific_Cmd_1; /*                       */
    } cc_event;
} tBtampTLVHCI_Command_Complete_Event;

#define BTAMP_TLV_HCI_COMMAND_COMPLETE_EVENT ( 14 )

//                                                     
#define BTAMP_TLV_HCI_COMMAND_COMPLETE_EVENT_MIN_LEN ( 6 )

#define BTAMP_TLV_HCI_COMMAND_COMPLETE_EVENT_MAX_LEN ( 257 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Command_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Command_Complete_Event*);

v_U32_t btampPackTlvHCI_Command_Complete_Event(void *, tBtampTLVHCI_Command_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Command_Complete_Event(void *, tBtampTLVHCI_Command_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Command_Status_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U8_t       num_hci_command_packets;
    v_U16_t      command_opcode;
} tBtampTLVHCI_Command_Status_Event;

#define BTAMP_TLV_HCI_COMMAND_STATUS_EVENT ( 15 )

//                                                     
#define BTAMP_TLV_HCI_COMMAND_STATUS_EVENT_MIN_LEN ( 6 )

#define BTAMP_TLV_HCI_COMMAND_STATUS_EVENT_MAX_LEN ( 6 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Command_Status_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Command_Status_Event*);

v_U32_t btampPackTlvHCI_Command_Status_Event(void *, tBtampTLVHCI_Command_Status_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Command_Status_Event(void *, tBtampTLVHCI_Command_Status_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Create_Logical_Link_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       tx_flow_spec[18];
    v_U8_t       rx_flow_spec[18];
} tBtampTLVHCI_Create_Logical_Link_Cmd;

#define BTAMP_TLV_HCI_CREATE_LOGICAL_LINK_CMD ( 1080 )

//                                                     
#define BTAMP_TLV_HCI_CREATE_LOGICAL_LINK_CMD_MIN_LEN ( 39 )

#define BTAMP_TLV_HCI_CREATE_LOGICAL_LINK_CMD_MAX_LEN ( 39 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Create_Logical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Create_Logical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Create_Logical_Link_Cmd(void *, tBtampTLVHCI_Create_Logical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Create_Logical_Link_Cmd(void *, tBtampTLVHCI_Create_Logical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Create_Physical_Link_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       key_length;
    v_U8_t       key_type;
    v_U8_t       key_material[32];
} tBtampTLVHCI_Create_Physical_Link_Cmd;

#define BTAMP_TLV_HCI_CREATE_PHYSICAL_LINK_CMD ( 1077 )

//                                                     
#define BTAMP_TLV_HCI_CREATE_PHYSICAL_LINK_CMD_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_CREATE_PHYSICAL_LINK_CMD_MAX_LEN ( 37 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Create_Physical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Create_Physical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Create_Physical_Link_Cmd(void *, tBtampTLVHCI_Create_Physical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Create_Physical_Link_Cmd(void *, tBtampTLVHCI_Create_Physical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Data_Buffer_Overflow_Event {
    v_U8_t       present;
    v_U8_t       link_type;
} tBtampTLVHCI_Data_Buffer_Overflow_Event;

#define BTAMP_TLV_HCI_DATA_BUFFER_OVERFLOW_EVENT ( 26 )

//                                                     
#define BTAMP_TLV_HCI_DATA_BUFFER_OVERFLOW_EVENT_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_DATA_BUFFER_OVERFLOW_EVENT_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Data_Buffer_Overflow_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Data_Buffer_Overflow_Event*);

v_U32_t btampPackTlvHCI_Data_Buffer_Overflow_Event(void *, tBtampTLVHCI_Data_Buffer_Overflow_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Data_Buffer_Overflow_Event(void *, tBtampTLVHCI_Data_Buffer_Overflow_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Disconnect_Logical_Link_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Disconnect_Logical_Link_Cmd;

#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_CMD ( 1082 )

//                                                     
#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Disconnect_Logical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Disconnect_Logical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Disconnect_Logical_Link_Cmd(void *, tBtampTLVHCI_Disconnect_Logical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Disconnect_Logical_Link_Cmd(void *, tBtampTLVHCI_Disconnect_Logical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Disconnect_Logical_Link_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U16_t      log_link_handle;
    v_U8_t       reason;
} tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event;

#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_COMPLETE_EVENT ( 70 )

//                                                     
#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_COMPLETE_EVENT_MIN_LEN ( 6 )

#define BTAMP_TLV_HCI_DISCONNECT_LOGICAL_LINK_COMPLETE_EVENT_MAX_LEN ( 6 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event*);

v_U32_t btampPackTlvHCI_Disconnect_Logical_Link_Complete_Event(void *, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Disconnect_Logical_Link_Complete_Event(void *, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Disconnect_Physical_Link_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       reason;
} tBtampTLVHCI_Disconnect_Physical_Link_Cmd;

#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_CMD ( 1079 )

//                                                     
#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Disconnect_Physical_Link_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Disconnect_Physical_Link_Cmd*);

v_U32_t btampPackTlvHCI_Disconnect_Physical_Link_Cmd(void *, tBtampTLVHCI_Disconnect_Physical_Link_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Disconnect_Physical_Link_Cmd(void *, tBtampTLVHCI_Disconnect_Physical_Link_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Disconnect_Physical_Link_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U8_t       phy_link_handle;
    v_U8_t       reason;
} tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event;

#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_COMPLETE_EVENT ( 66 )

//                                                     
#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_COMPLETE_EVENT_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_DISCONNECT_PHYSICAL_LINK_COMPLETE_EVENT_MAX_LEN ( 5 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event*);

v_U32_t btampPackTlvHCI_Disconnect_Physical_Link_Complete_Event(void *, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Disconnect_Physical_Link_Complete_Event(void *, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Flow_Spec_Modify_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
    v_U8_t       be_aggr_counter;
    v_U8_t       tx_flow_spec[18];
    v_U8_t       rx_flow_spec[18];
} tBtampTLVHCI_Flow_Spec_Modify_Cmd;

#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_CMD ( 1084 )

//                                                     
#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_CMD_MIN_LEN ( 41 )

#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_CMD_MAX_LEN ( 41 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Flow_Spec_Modify_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Flow_Spec_Modify_Cmd*);

v_U32_t btampPackTlvHCI_Flow_Spec_Modify_Cmd(void *, tBtampTLVHCI_Flow_Spec_Modify_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Flow_Spec_Modify_Cmd(void *, tBtampTLVHCI_Flow_Spec_Modify_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Flow_Spec_Modify_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Flow_Spec_Modify_Complete_Event;

#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_COMPLETE_EVENT ( 71 )

//                                                     
#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_COMPLETE_EVENT_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_FLOW_SPEC_MODIFY_COMPLETE_EVENT_MAX_LEN ( 5 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Flow_Spec_Modify_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event*);

v_U32_t btampPackTlvHCI_Flow_Spec_Modify_Complete_Event(void *, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Flow_Spec_Modify_Complete_Event(void *, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Flush_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Flush_Cmd;

#define BTAMP_TLV_HCI_FLUSH_CMD ( 3080 )

//                                                     
#define BTAMP_TLV_HCI_FLUSH_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_FLUSH_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Flush_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Flush_Cmd*);

v_U32_t btampPackTlvHCI_Flush_Cmd(void *, tBtampTLVHCI_Flush_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Flush_Cmd(void *, tBtampTLVHCI_Flush_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Flush_Occurred_Event {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Flush_Occurred_Event;

#define BTAMP_TLV_HCI_FLUSH_OCCURRED_EVENT ( 17 )

//                                                     
#define BTAMP_TLV_HCI_FLUSH_OCCURRED_EVENT_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_FLUSH_OCCURRED_EVENT_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Flush_Occurred_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Flush_Occurred_Event*);

v_U32_t btampPackTlvHCI_Flush_Occurred_Event(void *, tBtampTLVHCI_Flush_Occurred_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Flush_Occurred_Event(void *, tBtampTLVHCI_Flush_Occurred_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Enhanced_Flush_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
    v_U8_t       packet_type;
} tBtampTLVHCI_Enhanced_Flush_Cmd;

#define BTAMP_TLV_HCI_ENHANCED_FLUSH_CMD ( 3167 )

//                                                     
#define BTAMP_TLV_HCI_ENHANCED_FLUSH_CMD_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_ENHANCED_FLUSH_CMD_MAX_LEN ( 5 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Enhanced_Flush_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Enhanced_Flush_Cmd*);

v_U32_t btampPackTlvHCI_Enhanced_Flush_Cmd(void *, tBtampTLVHCI_Enhanced_Flush_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Enhanced_Flush_Cmd(void *, tBtampTLVHCI_Enhanced_Flush_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Enhanced_Flush_Complete_Event {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Enhanced_Flush_Complete_Event;

#define BTAMP_TLV_HCI_ENHANCED_FLUSH_COMPLETE_EVENT ( 57 )

//                                                     
#define BTAMP_TLV_HCI_ENHANCED_FLUSH_COMPLETE_EVENT_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_ENHANCED_FLUSH_COMPLETE_EVENT_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Enhanced_Flush_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Enhanced_Flush_Complete_Event*);

v_U32_t btampPackTlvHCI_Enhanced_Flush_Complete_Event(void *, tBtampTLVHCI_Enhanced_Flush_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Enhanced_Flush_Complete_Event(void *, tBtampTLVHCI_Enhanced_Flush_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */

//               
typedef struct sBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event {
    v_U8_t       present;
    v_U8_t       bd_addr[6];
    v_U8_t       generic_amp_link_key[32];
    v_U8_t       key_type;
} tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event;

#define BTAMP_TLV_HCI_GENERIC_AMP_LINK_KEY_NOTIFICATION_EVENT ( 62 )

//                                                     
#define BTAMP_TLV_HCI_GENERIC_AMP_LINK_KEY_NOTIFICATION_EVENT_MIN_LEN ( 41 )

#define BTAMP_TLV_HCI_GENERIC_AMP_LINK_KEY_NOTIFICATION_EVENT_MAX_LEN ( 41 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event*);

v_U32_t btampPackTlvHCI_Generic_AMP_Link_Key_Notification_Event(void *, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Generic_AMP_Link_Key_Notification_Event(void *, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Hardware_Error_Event {
    v_U8_t       present;
    v_U8_t       hardware_code;
} tBtampTLVHCI_Hardware_Error_Event;

#define BTAMP_TLV_HCI_HARDWARE_ERROR_EVENT ( 16 )

//                                                     
#define BTAMP_TLV_HCI_HARDWARE_ERROR_EVENT_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_HARDWARE_ERROR_EVENT_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Hardware_Error_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Hardware_Error_Event*);

v_U32_t btampPackTlvHCI_Hardware_Error_Event(void *, tBtampTLVHCI_Hardware_Error_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Hardware_Error_Event(void *, tBtampTLVHCI_Hardware_Error_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Logical_Link_Cancel_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       tx_flow_spec_id;
} tBtampTLVHCI_Logical_Link_Cancel_Cmd;

#define BTAMP_TLV_HCI_LOGICAL_LINK_CANCEL_CMD ( 1083 )

//                                                     
#define BTAMP_TLV_HCI_LOGICAL_LINK_CANCEL_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_LOGICAL_LINK_CANCEL_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Logical_Link_Cancel_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Logical_Link_Cancel_Cmd*);

v_U32_t btampPackTlvHCI_Logical_Link_Cancel_Cmd(void *, tBtampTLVHCI_Logical_Link_Cancel_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Logical_Link_Cancel_Cmd(void *, tBtampTLVHCI_Logical_Link_Cancel_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Logical_Link_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U16_t      log_link_handle;
    v_U8_t       phy_link_handle;
    v_U8_t       flow_spec_id;
} tBtampTLVHCI_Logical_Link_Complete_Event;

#define BTAMP_TLV_HCI_LOGICAL_LINK_COMPLETE_EVENT ( 69 )

//                                                     
#define BTAMP_TLV_HCI_LOGICAL_LINK_COMPLETE_EVENT_MIN_LEN ( 7 )

#define BTAMP_TLV_HCI_LOGICAL_LINK_COMPLETE_EVENT_MAX_LEN ( 7 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Logical_Link_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Logical_Link_Complete_Event*);

v_U32_t btampPackTlvHCI_Logical_Link_Complete_Event(void *, tBtampTLVHCI_Logical_Link_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Logical_Link_Complete_Event(void *, tBtampTLVHCI_Logical_Link_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Loopback_Command_Event {
    v_U8_t       present;
    v_U8_t       hci_command_packet[64];
} tBtampTLVHCI_Loopback_Command_Event;

#define BTAMP_TLV_HCI_LOOPBACK_COMMAND_EVENT ( 25 )

//                                                     
#define BTAMP_TLV_HCI_LOOPBACK_COMMAND_EVENT_MIN_LEN ( 66 )

#define BTAMP_TLV_HCI_LOOPBACK_COMMAND_EVENT_MAX_LEN ( 66 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Loopback_Command_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Loopback_Command_Event*);

v_U32_t btampPackTlvHCI_Loopback_Command_Event(void *, tBtampTLVHCI_Loopback_Command_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Loopback_Command_Event(void *, tBtampTLVHCI_Loopback_Command_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Physical_Link_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U8_t       phy_link_handle;
    v_U8_t       ch_number;
} tBtampTLVHCI_Physical_Link_Complete_Event;

#define BTAMP_TLV_HCI_PHYSICAL_LINK_COMPLETE_EVENT ( 64 )

//                                                     
#define BTAMP_TLV_HCI_PHYSICAL_LINK_COMPLETE_EVENT_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_PHYSICAL_LINK_COMPLETE_EVENT_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Physical_Link_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Physical_Link_Complete_Event*);

v_U32_t btampPackTlvHCI_Physical_Link_Complete_Event(void *, tBtampTLVHCI_Physical_Link_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Physical_Link_Complete_Event(void *, tBtampTLVHCI_Physical_Link_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Physical_Link_Loss_Warning_Event {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       reason;
} tBtampTLVHCI_Physical_Link_Loss_Warning_Event;

#define BTAMP_TLV_HCI_PHYSICAL_LINK_LOSS_WARNING_EVENT ( 67 )

//                                                     
#define BTAMP_TLV_HCI_PHYSICAL_LINK_LOSS_WARNING_EVENT_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_PHYSICAL_LINK_LOSS_WARNING_EVENT_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Physical_Link_Loss_Warning_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Physical_Link_Loss_Warning_Event*);

v_U32_t btampPackTlvHCI_Physical_Link_Loss_Warning_Event(void *, tBtampTLVHCI_Physical_Link_Loss_Warning_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Physical_Link_Loss_Warning_Event(void *, tBtampTLVHCI_Physical_Link_Loss_Warning_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Physical_Link_Recovery_Event {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
} tBtampTLVHCI_Physical_Link_Recovery_Event;

#define BTAMP_TLV_HCI_PHYSICAL_LINK_RECOVERY_EVENT ( 68 )

//                                                     
#define BTAMP_TLV_HCI_PHYSICAL_LINK_RECOVERY_EVENT_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_PHYSICAL_LINK_RECOVERY_EVENT_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Physical_Link_Recovery_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Physical_Link_Recovery_Event*);

v_U32_t btampPackTlvHCI_Physical_Link_Recovery_Event(void *, tBtampTLVHCI_Physical_Link_Recovery_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Physical_Link_Recovery_Event(void *, tBtampTLVHCI_Physical_Link_Recovery_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Qos_Violation_Event {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Qos_Violation_Event;

#define BTAMP_TLV_HCI_QOS_VIOLATION_EVENT ( 30 )

//                                                     
#define BTAMP_TLV_HCI_QOS_VIOLATION_EVENT_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_QOS_VIOLATION_EVENT_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Qos_Violation_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Qos_Violation_Event*);

v_U32_t btampPackTlvHCI_Qos_Violation_Event(void *, tBtampTLVHCI_Qos_Violation_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Qos_Violation_Event(void *, tBtampTLVHCI_Qos_Violation_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd;

#define BTAMP_TLV_HCI_READ_BEST_EFFORT_FLUSH_TIMEOUT_CMD ( 3177 )

//                                                     
#define BTAMP_TLV_HCI_READ_BEST_EFFORT_FLUSH_TIMEOUT_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_READ_BEST_EFFORT_FLUSH_TIMEOUT_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void *, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void *, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Buffer_Size_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Buffer_Size_Cmd;

#define BTAMP_TLV_HCI_READ_BUFFER_SIZE_CMD ( 4101 )

//                                                     
#define BTAMP_TLV_HCI_READ_BUFFER_SIZE_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_BUFFER_SIZE_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Buffer_Size_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Buffer_Size_Cmd*);

v_U32_t btampPackTlvHCI_Read_Buffer_Size_Cmd(void *, tBtampTLVHCI_Read_Buffer_Size_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Buffer_Size_Cmd(void *, tBtampTLVHCI_Read_Buffer_Size_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd;

#define BTAMP_TLV_HCI_READ_CONNECTION_ACCEPT_TIMEOUT_CMD ( 3093 )

//                                                     
#define BTAMP_TLV_HCI_READ_CONNECTION_ACCEPT_TIMEOUT_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_CONNECTION_ACCEPT_TIMEOUT_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Read_Connection_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Connection_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Data_Block_Size_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Data_Block_Size_Cmd;

#define BTAMP_TLV_HCI_READ_DATA_BLOCK_SIZE_CMD ( 4106 )

//                                                     
#define BTAMP_TLV_HCI_READ_DATA_BLOCK_SIZE_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_DATA_BLOCK_SIZE_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Data_Block_Size_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Data_Block_Size_Cmd*);

v_U32_t btampPackTlvHCI_Read_Data_Block_Size_Cmd(void *, tBtampTLVHCI_Read_Data_Block_Size_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Data_Block_Size_Cmd(void *, tBtampTLVHCI_Read_Data_Block_Size_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Failed_Contact_Counter_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd;

#define BTAMP_TLV_HCI_READ_FAILED_CONTACT_COUNTER_CMD ( 5121 )

//                                                     
#define BTAMP_TLV_HCI_READ_FAILED_CONTACT_COUNTER_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_READ_FAILED_CONTACT_COUNTER_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd*);

v_U32_t btampPackTlvHCI_Read_Failed_Contact_Counter_Cmd(void *, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Failed_Contact_Counter_Cmd(void *, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Flow_Control_Mode_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Flow_Control_Mode_Cmd;

#define BTAMP_TLV_HCI_READ_FLOW_CONTROL_MODE_CMD ( 3174 )

//                                                     
#define BTAMP_TLV_HCI_READ_FLOW_CONTROL_MODE_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_FLOW_CONTROL_MODE_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Flow_Control_Mode_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd*);

v_U32_t btampPackTlvHCI_Read_Flow_Control_Mode_Cmd(void *, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Flow_Control_Mode_Cmd(void *, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Link_Quality_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Read_Link_Quality_Cmd;

#define BTAMP_TLV_HCI_READ_LINK_QUALITY_CMD ( 5123 )

//                                                     
#define BTAMP_TLV_HCI_READ_LINK_QUALITY_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_READ_LINK_QUALITY_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Link_Quality_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Link_Quality_Cmd*);

v_U32_t btampPackTlvHCI_Read_Link_Quality_Cmd(void *, tBtampTLVHCI_Read_Link_Quality_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Link_Quality_Cmd(void *, tBtampTLVHCI_Read_Link_Quality_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd;

#define BTAMP_TLV_HCI_READ_LINK_SUPERVISION_TIMEOUT_CMD ( 3126 )

//                                                     
#define BTAMP_TLV_HCI_READ_LINK_SUPERVISION_TIMEOUT_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_READ_LINK_SUPERVISION_TIMEOUT_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Read_Link_Supervision_Timeout_Cmd(void *, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Link_Supervision_Timeout_Cmd(void *, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Local_AMP_Assoc_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U16_t      length_so_far;
    v_U16_t      max_remote_amp_assoc_length;
} tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd;

#define BTAMP_TLV_HCI_READ_LOCAL_AMP_ASSOC_CMD ( 5130 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOCAL_AMP_ASSOC_CMD_MIN_LEN ( 7 )

#define BTAMP_TLV_HCI_READ_LOCAL_AMP_ASSOC_CMD_MAX_LEN ( 7 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd*);

v_U32_t btampPackTlvHCI_Read_Local_AMP_Assoc_Cmd(void *, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Local_AMP_Assoc_Cmd(void *, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Local_AMP_Information_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Local_AMP_Information_Cmd;

#define BTAMP_TLV_HCI_READ_LOCAL_AMP_INFORMATION_CMD ( 5129 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOCAL_AMP_INFORMATION_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOCAL_AMP_INFORMATION_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Local_AMP_Information_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Local_AMP_Information_Cmd*);

v_U32_t btampPackTlvHCI_Read_Local_AMP_Information_Cmd(void *, tBtampTLVHCI_Read_Local_AMP_Information_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Local_AMP_Information_Cmd(void *, tBtampTLVHCI_Read_Local_AMP_Information_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Local_Supported_Cmds_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd;

#define BTAMP_TLV_HCI_READ_LOCAL_SUPPORTED_CMDS_CMD ( 4098 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOCAL_SUPPORTED_CMDS_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOCAL_SUPPORTED_CMDS_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd*);

v_U32_t btampPackTlvHCI_Read_Local_Supported_Cmds_Cmd(void *, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Local_Supported_Cmds_Cmd(void *, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Local_Version_Info_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Local_Version_Info_Cmd;

#define BTAMP_TLV_HCI_READ_LOCAL_VERSION_INFO_CMD ( 4097 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOCAL_VERSION_INFO_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOCAL_VERSION_INFO_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Local_Version_Info_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Local_Version_Info_Cmd*);

v_U32_t btampPackTlvHCI_Read_Local_Version_Info_Cmd(void *, tBtampTLVHCI_Read_Local_Version_Info_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Local_Version_Info_Cmd(void *, tBtampTLVHCI_Read_Local_Version_Info_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Location_Data_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Location_Data_Cmd;

#define BTAMP_TLV_HCI_READ_LOCATION_DATA_CMD ( 3172 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOCATION_DATA_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOCATION_DATA_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Location_Data_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Location_Data_Cmd*);

v_U32_t btampPackTlvHCI_Read_Location_Data_Cmd(void *, tBtampTLVHCI_Read_Location_Data_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Location_Data_Cmd(void *, tBtampTLVHCI_Read_Location_Data_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd;

#define BTAMP_TLV_HCI_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD ( 3169 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_Loopback_Mode_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Read_Loopback_Mode_Cmd;

#define BTAMP_TLV_HCI_READ_LOOPBACK_MODE_CMD ( 6145 )

//                                                     
#define BTAMP_TLV_HCI_READ_LOOPBACK_MODE_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_READ_LOOPBACK_MODE_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_Loopback_Mode_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_Loopback_Mode_Cmd*);

v_U32_t btampPackTlvHCI_Read_Loopback_Mode_Cmd(void *, tBtampTLVHCI_Read_Loopback_Mode_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_Loopback_Mode_Cmd(void *, tBtampTLVHCI_Read_Loopback_Mode_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Read_RSSI_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Read_RSSI_Cmd;

#define BTAMP_TLV_HCI_READ_RSSI_CMD ( 5125 )

//                                                     
#define BTAMP_TLV_HCI_READ_RSSI_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_READ_RSSI_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Read_RSSI_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Read_RSSI_Cmd*);

v_U32_t btampPackTlvHCI_Read_RSSI_Cmd(void *, tBtampTLVHCI_Read_RSSI_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Read_RSSI_Cmd(void *, tBtampTLVHCI_Read_RSSI_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Reset_Cmd {
    v_U8_t       present;
} tBtampTLVHCI_Reset_Cmd;

#define BTAMP_TLV_HCI_RESET_CMD ( 3075 )

//                                                     
#define BTAMP_TLV_HCI_RESET_CMD_MIN_LEN ( 2 )

#define BTAMP_TLV_HCI_RESET_CMD_MAX_LEN ( 2 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Reset_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Reset_Cmd*);

v_U32_t btampPackTlvHCI_Reset_Cmd(void *, tBtampTLVHCI_Reset_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Reset_Cmd(void *, tBtampTLVHCI_Reset_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
} tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd;

#define BTAMP_TLV_HCI_RESET_FAILED_CONTACT_COUNTER_CMD ( 5122 )

//                                                     
#define BTAMP_TLV_HCI_RESET_FAILED_CONTACT_COUNTER_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_RESET_FAILED_CONTACT_COUNTER_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd*);

v_U32_t btampPackTlvHCI_Reset_Failed_Contact_Counter_Cmd(void *, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Reset_Failed_Contact_Counter_Cmd(void *, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Set_Event_Mask_Cmd {
    v_U8_t       present;
    v_U8_t       event_mask[8];
} tBtampTLVHCI_Set_Event_Mask_Cmd;

#define BTAMP_TLV_HCI_SET_EVENT_MASK_CMD ( 3077 )

//                                                     
#define BTAMP_TLV_HCI_SET_EVENT_MASK_CMD_MIN_LEN ( 10 )

#define BTAMP_TLV_HCI_SET_EVENT_MASK_CMD_MAX_LEN ( 10 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Set_Event_Mask_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Set_Event_Mask_Cmd*);

v_U32_t btampPackTlvHCI_Set_Event_Mask_Cmd(void *, tBtampTLVHCI_Set_Event_Mask_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Set_Event_Mask_Cmd(void *, tBtampTLVHCI_Set_Event_Mask_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Set_Event_Mask_Page_2_Cmd {
    v_U8_t       present;
    v_U8_t       event_mask_page_2[8];
} tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd;

#define BTAMP_TLV_HCI_SET_EVENT_MASK_PAGE_2_CMD ( 3171 )

//                                                     
#define BTAMP_TLV_HCI_SET_EVENT_MASK_PAGE_2_CMD_MIN_LEN ( 10 )

#define BTAMP_TLV_HCI_SET_EVENT_MASK_PAGE_2_CMD_MAX_LEN ( 10 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd*);

v_U32_t btampPackTlvHCI_Set_Event_Mask_Page_2_Cmd(void *, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Set_Event_Mask_Page_2_Cmd(void *, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Set_Short_Range_Mode_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U8_t       short_range_mode;
} tBtampTLVHCI_Set_Short_Range_Mode_Cmd;

#define BTAMP_TLV_HCI_SET_SHORT_RANGE_MODE_CMD ( 3179 )

//                                                     
#define BTAMP_TLV_HCI_SET_SHORT_RANGE_MODE_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_SET_SHORT_RANGE_MODE_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Set_Short_Range_Mode_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Set_Short_Range_Mode_Cmd*);

v_U32_t btampPackTlvHCI_Set_Short_Range_Mode_Cmd(void *, tBtampTLVHCI_Set_Short_Range_Mode_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Set_Short_Range_Mode_Cmd(void *, tBtampTLVHCI_Set_Short_Range_Mode_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//               
typedef struct sBtampTLVHCI_Short_Range_Mode_Change_Complete_Event {
    v_U8_t       present;
    v_U8_t       status;
    v_U8_t       phy_link_handle;
    v_U8_t       short_range_mode;
} tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event;

#define BTAMP_TLV_HCI_SHORT_RANGE_MODE_CHANGE_COMPLETE_EVENT ( 76 )

//                                                     
#define BTAMP_TLV_HCI_SHORT_RANGE_MODE_CHANGE_COMPLETE_EVENT_MIN_LEN ( 5 )

#define BTAMP_TLV_HCI_SHORT_RANGE_MODE_CHANGE_COMPLETE_EVENT_MAX_LEN ( 5 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event*);

v_U32_t btampPackTlvHCI_Short_Range_Mode_Change_Complete_Event(void *, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Short_Range_Mode_Change_Complete_Event(void *, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
    v_U32_t      best_effort_flush_timeout;
} tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd;

#define BTAMP_TLV_HCI_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_CMD ( 3178 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_CMD_MIN_LEN ( 8 )

#define BTAMP_TLV_HCI_WRITE_BEST_EFFORT_FLUSH_TIMEOUT_CMD_MAX_LEN ( 8 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void *, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void *, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      connection_accept_timeout;
} tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd;

#define BTAMP_TLV_HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT_CMD ( 3094 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_WRITE_CONNECTION_ACCEPT_TIMEOUT_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Write_Connection_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Connection_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Flow_Control_Mode_Cmd {
    v_U8_t       present;
    v_U8_t       flow_control_mode;
} tBtampTLVHCI_Write_Flow_Control_Mode_Cmd;

#define BTAMP_TLV_HCI_WRITE_FLOW_CONTROL_MODE_CMD ( 3175 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_FLOW_CONTROL_MODE_CMD_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_WRITE_FLOW_CONTROL_MODE_CMD_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Flow_Control_Mode_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd*);

v_U32_t btampPackTlvHCI_Write_Flow_Control_Mode_Cmd(void *, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Flow_Control_Mode_Cmd(void *, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      log_link_handle;
    v_U16_t      link_supervision_timeout;
} tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd;

#define BTAMP_TLV_HCI_WRITE_LINK_SUPERVISION_TIMEOUT_CMD ( 3127 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_LINK_SUPERVISION_TIMEOUT_CMD_MIN_LEN ( 6 )

#define BTAMP_TLV_HCI_WRITE_LINK_SUPERVISION_TIMEOUT_CMD_MAX_LEN ( 6 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Write_Link_Supervision_Timeout_Cmd(void *, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Link_Supervision_Timeout_Cmd(void *, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Location_Data_Cmd {
    v_U8_t       present;
    v_U8_t       loc_domain_aware;
    v_U8_t       loc_domain[3];
    v_U8_t       loc_options;
} tBtampTLVHCI_Write_Location_Data_Cmd;

#define BTAMP_TLV_HCI_WRITE_LOCATION_DATA_CMD ( 3173 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_LOCATION_DATA_CMD_MIN_LEN ( 7 )

#define BTAMP_TLV_HCI_WRITE_LOCATION_DATA_CMD_MAX_LEN ( 7 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Location_Data_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Location_Data_Cmd*);

v_U32_t btampPackTlvHCI_Write_Location_Data_Cmd(void *, tBtampTLVHCI_Write_Location_Data_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Location_Data_Cmd(void *, tBtampTLVHCI_Write_Location_Data_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd {
    v_U8_t       present;
    v_U16_t      logical_link_accept_timeout;
} tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd;

#define BTAMP_TLV_HCI_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD ( 3170 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD_MIN_LEN ( 4 )

#define BTAMP_TLV_HCI_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT_CMD_MAX_LEN ( 4 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd*);

v_U32_t btampPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void *, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Loopback_Mode_Cmd {
    v_U8_t       present;
    v_U8_t       loopback_mode;
} tBtampTLVHCI_Write_Loopback_Mode_Cmd;

#define BTAMP_TLV_HCI_WRITE_LOOPBACK_MODE_CMD ( 6146 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_LOOPBACK_MODE_CMD_MIN_LEN ( 3 )

#define BTAMP_TLV_HCI_WRITE_LOOPBACK_MODE_CMD_MAX_LEN ( 3 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Loopback_Mode_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Loopback_Mode_Cmd*);

v_U32_t btampPackTlvHCI_Write_Loopback_Mode_Cmd(void *, tBtampTLVHCI_Write_Loopback_Mode_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Loopback_Mode_Cmd(void *, tBtampTLVHCI_Write_Loopback_Mode_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                 
typedef struct sBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd {
    v_U8_t       present;
    v_U8_t       phy_link_handle;
    v_U16_t      length_so_far;
    v_U16_t      amp_assoc_remaining_length;
    v_U8_t       amp_assoc_fragment[248];
} tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd;

#define BTAMP_TLV_HCI_WRITE_REMOTE_AMP_ASSOC_CMD ( 5131 )

//                                                     
#define BTAMP_TLV_HCI_WRITE_REMOTE_AMP_ASSOC_CMD_MIN_LEN ( 7 )

#define BTAMP_TLV_HCI_WRITE_REMOTE_AMP_ASSOC_CMD_MAX_LEN ( 255 )

#ifdef __cplusplus
extern "C" {
#endif /*     */
v_U32_t btampUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void *, v_U8_t*,v_U16_t, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd*);

v_U32_t btampPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void *, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void *, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd*, v_U32_t*);

#ifdef __cplusplus
}; /*                 */
#endif /*     */
//                  
typedef struct sBtampTLVHCI_Vendor_Specific_Cmd_0 {
    v_U8_t       present;
} tBtampTLVHCI_Vendor_Specific_0_Cmd;

#define BTAMP_TLV_HCI_VENDOR_SPECIFIC_CMD_0 ( 64512 )

//                  
typedef struct sBtampTLVHCI_Vendor_Specific_Cmd_1 {
    v_U8_t       present;
} tBtampTLVHCI_Vendor_Specific_1_Cmd;

#define BTAMP_TLV_HCI_VENDOR_SPECIFIC_CMD_1 ( 64513 )

/*                                                                    
                                                                      
                                                                    */

/*                                                                       
         
                                                                      */

typedef struct sBtampAMP_ASSOC{
    tBtampTLVAMP_Assoc_MAC_Addr AMP_Assoc_MAC_Addr;
    tBtampTLVAMP_Assoc_Preferred_Channel_List AMP_Assoc_Preferred_Channel_List;
    tBtampTLVAMP_Assoc_Connected_Channel AMP_Assoc_Connected_Channel;
    tBtampTLVAMP_Assoc_PAL_Capabilities AMP_Assoc_PAL_Capabilities;
    tBtampTLVAMP_Assoc_PAL_Version AMP_Assoc_PAL_Version;
} tBtampAMP_ASSOC;

#define BTAMP_AMP_ASSOC ( 1 )

#ifdef __cplusplus
extern "C" {
#endif /*     */

v_U32_t btampUnpackAMP_ASSOC(void * pCtx, v_U8_t *pBuf, v_U32_t nBuf, tBtampAMP_ASSOC *pFrm);
v_U32_t btampPackAMP_ASSOC(void * pCtx, tBtampAMP_ASSOC *pFrm, v_U8_t *pBuf, v_U32_t nBuf, v_U32_t *pnConsumed);
v_U32_t btampGetPackedAMP_ASSOCSize(void * pCtx, tBtampAMP_ASSOC *pFrm, v_U32_t *pnNeeded);

#ifdef __cplusplus
} /*                 */
#endif /*     */


#ifdef __cplusplus
extern "C" {
#endif /*     */

/*                                      */
typedef struct sBtampTLVHCI_Num_Completed_Pkts_Event
{
    v_U8_t       present;
    /* 
                                                           
                                                           
    */

    v_U8_t   num_handles;

    /* 
                                                               
    */
    v_U16_t  conn_handles[WLANBAP_MAX_LOG_LINKS];  

    /* 
                                                                          
                                                                              
                                                       
    */
    v_U16_t  num_completed_pkts[WLANBAP_MAX_LOG_LINKS]; 
} tBtampTLVHCI_Num_Completed_Pkts_Event;

#define BTAMP_TLV_HCI_NUM_OF_COMPLETED_PKTS_EVENT ( 19 )

v_U32_t btampPackTlvHCI_Num_Completed_Pkts_Event(void *, tBtampTLVHCI_Num_Completed_Pkts_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Num_Completed_Pkts_Event(void *, tBtampTLVHCI_Num_Completed_Pkts_Event*, v_U32_t*);

/*                                                             */
#define WLAN_BAP_PAL_FLOW_SPEC_TLV_LEN          16

#ifdef __cplusplus
} /*                 */
#endif /*     */

#ifdef __cplusplus
extern "C" {
#endif /*     */

/*                                          */
typedef struct sBtampTLVHCI_Num_Completed_Data_Blocks_Event
{
    v_U8_t       present;
    /* 
                                                                            
                                                                        
                                                                        
                                                                   
    */

    v_U16_t   total_num_data_blocks;

    /* 
                                                           
                                                           
    */

    v_U8_t   num_handles;

    /* 
                                                               
    */
    v_U16_t  conn_handles[WLANBAP_MAX_LOG_LINKS];  

    /* 
                                                                          
                                                                              
                                                       
    */
    v_U16_t  num_completed_pkts[WLANBAP_MAX_LOG_LINKS]; 

    /* 
                                                                       
                                                                    
                                                          
                                
    */
    v_U16_t  num_completed_blocks[WLANBAP_MAX_LOG_LINKS]; 

} tBtampTLVHCI_Num_Completed_Data_Blocks_Event;

#define BTAMP_TLV_HCI_NUM_OF_COMPLETED_DATA_BLOCKS_EVENT ( 72 )

v_U32_t btampPackTlvHCI_Num_Completed_Data_Blocks_Event(void *, tBtampTLVHCI_Num_Completed_Data_Blocks_Event*, v_U8_t*, v_U32_t, v_U32_t*);

v_U32_t btampGetPackedTlvHCI_Num_Completed_Data_Blocks_Event(void *, tBtampTLVHCI_Num_Completed_Data_Blocks_Event*, v_U32_t*);

#ifdef __cplusplus
} /*                 */
#endif /*     */

#endif /*            */


