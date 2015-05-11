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

/* 
                    
   
                                                  
                              
   
   

   
   
                                                      
                                                        
   
                 
   
                                        
   
   
  */

#include <memory.h> /*            */
#include <stddef.h> /*              */

#define _vsnprintf vsnprintf

#include "vos_api.h"
#include "btampHCI.h"

#if defined ( _MSC_VER )
#   pragma warning (disable: 4244)
#   pragma warning (disable: 4505)
#   pragma warning (disable: 4702)
#   pragma warning (disable: 4996) /*                             */
#endif /*                 */

/*                                                                            
          */
#define WLAN_BAP_PAL_AMP_ASSOC_CONN_CH_TLV_MIN_LEN    3

/*                                                                            
          */
#define WLAN_BAP_PAL_AMP_ASSOC_PREF_CH_TLV_MIN_LEN    3

/*                                                               */
#define WLAN_BAP_PAL_MAC_ADDR_TLV_LEN                 6

/*                                                                */
#define WLAN_BAP_PAL_CAPABILITIES_TLV_LEN             4

/*                                                           */
#define WLAN_BAP_PAL_VERSION_TLV_LEN             5

/*                                                                   */
#define WLAN_BAP_PAL_ACC_PHY_LINK_TLV_MIN_LEN               3

/*                                                                   */
#define WLAN_BAP_PAL_ACC_LOG_LINK_TLV_LEN                  37

/*                                                                   */
#define WLAN_BAP_PAL_CREATE_LOG_LINK_TLV_LEN               37

/*                                                                   */
#define WLAN_BAP_PAL_CREATE_PHY_LINK_TLV_MIN_LEN            3

/*                                                                       */
#define WLAN_BAP_PAL_DISC_LOG_LINK_TLV_LEN                  2

/*                                                                       */
#define WLAN_BAP_PAL_DISC_PHY_LINK_TLV_LEN                  2

/*                                                                    */
#define WLAN_BAP_PAL_FLOW_SPEC_MOD_TLV_LEN                 34

/*                                                         */
#define WLAN_BAP_PAL_FLUSH_TLV_LEN                          2 

/*                                                                  */
#define WLAN_BAP_PAL_ENHANCED_FLUSH_TLV_LEN                 3 

/*                                                                   */
#define WLAN_BAP_PAL_CANCEL_LOG_LINK_TLV_LEN                2

/*                                                                           
        */
#define WLAN_BAP_PAL_READ_BE_FLUSH_TIMEOUT_TLV_LEN          2

/*                                                                        
        */
#define WLAN_BAP_PAL_READ_FAILED_CONTACT_CNT_TLV_LEN        2

/*                                                                */
#define WLAN_BAP_PAL_READ_LINK_QUALITY_TLV_LEN              2

/*                                                                         
         */
#define WLAN_BAP_PAL_READ_LINK_SVISISON_TIMEOUT_TLV_LEN     2

/*                                                                        */
#define WLAN_BAP_PAL_READ_LOCAL_AMP_ASSOC_TLV_LEN           5

/*                                                             */
#define WLAN_BAP_PAL_READ_RSSI_TLV_LEN                      2

/*                                                                         
        */
#define WLAN_BAP_PAL_RESET_FAILED_CONTACT_CNT_TLV_LEN       2

/*                                                                  */
#define WLAN_BAP_PAL_SET_EVENT_MASK_TLV_LEN                 8

/*                                                                   */
#define WLAN_BAP_PAL_SET_EVENT_MASK2_TLV_LEN                8

/*                                                                        */
#define WLAN_BAP_PAL_SET_SHORT_RANGE_MODE_TLV_LEN           2

/*                                                                            
         */
#define WLAN_BAP_PAL_WRITE_BE_FLUSH_TIMEOUT_TLV_LEN         6

/*                                                                            
         */
#define WLAN_BAP_PAL_WRITE_CON_ACC_TIMEOUT_TLV_LEN          2

/*                                                                           */
#define WLAN_BAP_PAL_WRITE_FLOW_CTRL_MODE_TLV_LEN           1

/*                                                                          
         */
#define WLAN_BAP_PAL_WRITE_LINK_SVISION_TIMEOUT_TLV_LEN     4

/*                                                                       */
#define WLAN_BAP_PAL_WRITE_LOCATION_DATA_CMD_TLV_LEN        5

/*                                                                        */
#define WLAN_BAP_PAL_WRITE_LOG_LINK_ACC_TIMEOUT_TLV_LEN     2

/*                                                                       */
#define WLAN_BAP_PAL_WRITE_LOOOPBACK_MODE_TLV_LEN           1

/*                                                                          */
#define WLAN_BAP_PAL_WRITE_REMOTE_AMP_ASSOC_MIN_TLV_LEN     5 

/*                          */
/*                                                  */
#define WLAN_BAP_PAL_REG_EXTN_ID_VAL                        201

/*                                   */
#define WLAN_BAP_PAL_REG_CLASS_VAL                          254

/*                                 */
#define WLAN_BAP_PAL_COVERAGE_CLASS_VAL                     0


/*                                       */
//                                            
//                                  

typedef unsigned char tFRAMES_BOOL;
typedef void (*pfnGeneric_t)(void);


typedef struct sFFDefn {
    v_U8_t  size;
    size_t       offset;
    v_U16_t sig;
    pfnGeneric_t pfn;
    const char  *name;
} tFFDefn;

typedef struct sIEDefn {
    v_U8_t   eid;
    v_U16_t  minSize;
    v_U16_t  maxSize;
    size_t        offset;
    size_t        presenceOffset;
    size_t        countOffset;
    v_U16_t  arraybound;
    unsigned char oui[5];
    unsigned char noui;
    v_U16_t  sig;
    pfnGeneric_t  pfn;
    const char   *name;
    tFRAMES_BOOL  fMandatory;
} tIEDefn;

#if !defined(countof)
#define countof(x) ( sizeof( (x) ) / sizeof( (x)[0] ) )
#endif

#if ! defined(BTAMP_MEMCPY)
#   define BTAMP_MEMCPY(ctx, dst, src, len) \
        vos_mem_copy( (dst), (src), (len) )        \

#endif

#if ! defined(BTAMP_MEMCMP)
#   define BTAMP_MEMCMP(ctx, lhs, rhs, len) \
        memcmp( (lhs), (rhs), (len) )        \

#endif

#ifndef BTAMP_HAVE_LOG_SEVERITIES
#   define FRLOG_OFF ( 0 )
#   define FRLOGP    ( 1 )
#   define FRLOGE    ( 2 )
#   define FRLOGW    ( 3 )
#   define FRLOG1    ( 4 )
#   define FRLOG2    ( 5 )
#   define FRLOG3    ( 6 )
#   define FRLOG4    ( 7 )
#endif

#define FRFL(x) x

#ifdef BTAMP_ENABLE_LOGGING

#ifndef BTAMP_HAVE_LOG_MACROS

#include <stdio.h>
#include <stdarg.h>

#ifndef BTAMP_LOG_GATE
#   define BTAMP_LOG_GATE FRLOGW
#endif //               

#ifdef WIN32

#if defined ( _CONSOLE ) || defined ( _WINDOWS ) || defined ( _DLL ) || defined ( _LIB )
#include <windows.h>
#define DBGPRINT OutputDebugStringA
#else  /*               */
#define DBGPRINT DbgPrint
#endif /*           */



static void framesLog(void * pCtx, int nSev,
                      const char *lpszFormat, ...)
{
    va_list val;
    char buffer[1024];
    (void)pCtx;
    if ( nSev <= BTAMP_LOG_GATE )
    {
        va_start(val, lpszFormat);
        _vsnprintf(buffer, 1024, lpszFormat, val);
        va_end(val);
        DBGPRINT(buffer);
    }
}
static void framesDump(void * pCtx, int nSev, v_U8_t *pBuf, int nBuf)
{
    char buffer[35];
    int i, offset;
    pCtx;
    offset = 0;
    if ( nSev > BTAMP_LOG_GATE ) return;
    for (i = 0; i < nBuf/8; ++i)
    {
        _snprintf(buffer, 35, "%08x: %02x %02x %02x %02x %02x %02x %02x %02x\n", offset, *pBuf, *(pBuf + 1), *(pBuf + 2), *(pBuf + 3), *(pBuf + 4), *(pBuf + 5), *(pBuf + 6), *(pBuf + 7));
        pBuf += 8; offset += 8;
        DBGPRINT(buffer);
    }
    _snprintf(buffer, 35, "%08x: ", offset);
    DBGPRINT(buffer);
    for (i = 0; i < nBuf % 8; ++i)
    {
        _snprintf(buffer, 35, "%02x ", *pBuf);
        ++pBuf;
        DBGPRINT(buffer);
    }
    DBGPRINT("\n");
}

#elif defined OS_X /*           */
static void framesLog(void * pCtx, int nSev,
                      const char *lpszFormat, ...)
{//                                   

}

static void framesDump(void * pCtx, int nSev, v_U8_t *pBuf, int nBuf)
{
}

#elif defined LINUX

static void framesLog(void * pCtx, int nSev,
                      const char *lpszFormat, ...)
{
    va_list marker;
    (void)pCtx;
    if ( nSev <= BTAMP_LOG_GATE )
    {
        va_start( marker, lpszFormat );
        vprintf(lpszFormat, marker);
        va_end( marker );
    }
}

static void framesDump(void * pCtx, int nSev, v_U8_t *pBuf, int nBuf)
{
    char buffer[35];
    int i, offset;
    (void)pCtx;
    offset = 0;
    if ( nSev > BTAMP_LOG_GATE ) return;
    for (i = 0; i < nBuf/8; ++i)
    {
        printf("%08x: %02x %02x %02x %02x %02x %02x %02x %02x\n", offset, *pBuf, *(pBuf + 1), *(pBuf + 2), *(pBuf + 3), *(pBuf + 4), *(pBuf + 5), *(pBuf + 6), *(pBuf + 7));
        pBuf += 8; offset += 8;
    }
    printf("%08x: ", offset);
    for (i = 0; i < nBuf % 8; ++i)
    {
        printf("%02x ", *pBuf);
        ++pBuf;
    }
    printf("\n");
}

#endif /*       */

#define FRAMES_LOG0(ctx, sev, fmt) \
     framesLog((ctx), (sev), (fmt));
#define FRAMES_LOG1(ctx, sev, fmt, p1) \
     framesLog((ctx), (sev), (fmt), (p1));
#define FRAMES_LOG2(ctx, sev, fmt, p1, p2) \
     framesLog((ctx), (sev), (fmt), (p1), (p2));
#define FRAMES_LOG3(ctx, sev, fmt, p1, p2, p3) \
     framesLog((ctx), (sev), (fmt), (p1), (p2), (p3));
#define FRAMES_DUMP(ctx, sev, p, n) \
     framesDump((ctx), (sev), (p), (n));
#ifndef FRAMES_SEV_FOR_FRAME
#   define FRAMES_SEV_FOR_FRAME(ctx, sig) FRLOG3
#endif

#endif /*                           */

#else  //                       
#   define FRAMES_LOG0(ctx, sev, fmt)
#   define FRAMES_LOG1(ctx, sev, fmt, p1)
#   define FRAMES_LOG2(ctx, sev, fmt, p1, p2)
#   define FRAMES_LOG3(ctx, sev, fmt, p1, p2, p3)
#   define FRAMES_DUMP(ctx, sev, p, n)
#   ifndef FRAMES_SEV_FOR_FRAME
#       define FRAMES_SEV_FOR_FRAME(ctx, sig) FRLOG3
#   endif
#endif //                     

#if defined( BTAMP_ENABLE_DBG_BREAK ) && defined ( WIN32 )
#   define FRAMES_DBG_BREAK() { _asm int 3 }
#else
#   define FRAMES_DBG_BREAK()
#endif

#if ! defined(BTAMP_PARAMETER_CHECK2)
#   if defined (BTAMP_HAVE_WIN32_API)

#       define BTAMP_PARAMETER_CHECK2(pSrc, pBuf, nBuf, pnConsumed) do { \
        if (!pSrc || IsBadReadPtr(pSrc, 4)) return BTAMP_BAD_INPUT_BUFFER; \
        if (!pBuf || IsBadWritePtr(pBuf, nBuf)) return BTAMP_BAD_OUTPUT_BUFFER; \
        if (!nBuf) return BTAMP_BAD_OUTPUT_BUFFER;                      \
        if (IsBadWritePtr(pnConsumed, 4)) return BTAMP_BAD_OUTPUT_BUFFER; \
    } while (0)

#   else

#       define BTAMP_PARAMETER_CHECK2(pSrc, pBuf, nBuf, pnConsumed) do { \
        if (!pSrc) return BTAMP_BAD_INPUT_BUFFER;                       \
        if (!pBuf) return BTAMP_BAD_OUTPUT_BUFFER;                      \
        if (!nBuf) return BTAMP_BAD_OUTPUT_BUFFER;                      \
        if (!pnConsumed) return BTAMP_BAD_OUTPUT_BUFFER;                \
    } while (0)
#   endif
#endif

static void framesntohs(void *    pCtx,
                        v_U16_t *pOut,
                        v_U8_t  *pIn,
                        tFRAMES_BOOL  fMsb)
{
    (void)pCtx;
#   if defined ( BTAMP_LITTLE_ENDIAN_HOST )
    if ( !fMsb )
    {
        BTAMP_MEMCPY(pCtx, ( v_U16_t* )pOut, pIn, 2);
    }
    else
    {
        *pOut = ( v_U16_t )( *pIn << 8 ) | *( pIn + 1 );
    }
#   else
    if ( !fMsb )
    {
        *pOut = ( v_U16_t )( *pIn | ( *( pIn + 1 ) << 8 ) );
    }
    else
    {
        BTAMP_MEMCPY(pCtx, ( v_U16_t* )pOut, pIn, 2);
    }
#   endif
}

static void framesntohl(void *    pCtx,
                        v_U32_t *pOut,
                        v_U8_t  *pIn,
                        tFRAMES_BOOL  fMsb)
{
    (void)pCtx;
#   if defined ( BTAMP_LITTLE_ENDIAN_HOST )
    if ( !fMsb )
    {
        *pOut = * ( v_U32_t* )pIn;
    }
    else
    {
        *pOut = ( v_U32_t )( *pIn         << 24 ) |
                ( *( pIn + 1 ) << 16 ) |
                ( *( pIn + 2 ) <<  8 ) |
                ( *( pIn + 3 ) );
    }
#   else
    if ( !fMsb )
    {
        *pOut = ( v_U32_t )( *( pIn + 3 ) << 24 ) |
                                ( *( pIn + 2 ) << 16 ) |
                                ( *( pIn + 1 ) <<  8 ) |
                                ( *( pIn ) );
    }
    else
    {
        *pOut = * ( v_U32_t* )pIn;
    }
#   endif
}

static void frameshtons(void *    pCtx
,                        v_U8_t  *pOut,
                        v_U16_t  pIn,
                        tFRAMES_BOOL  fMsb)
{
    (void)pCtx;
#   if defined ( BTAMP_LITTLE_ENDIAN_HOST )
    if ( !fMsb )
    {
        BTAMP_MEMCPY(pCtx, pOut, &pIn, 2);
    }
    else
    {
        *pOut         = ( pIn & 0xff00 ) >> 8;
        *( pOut + 1 ) = pIn & 0xff;
    }
#   else
    if ( !fMsb )
    {
        *pOut         = pIn & 0xff;
        *( pOut + 1 ) = ( pIn & 0xff00 ) >> 8;
    }
    else
    {
        BTAMP_MEMCPY(pCtx, pOut, &pIn, 2);
    }
#   endif
}

static void frameshtonl(void *    pCtx,
                        v_U8_t  *pOut,
                        v_U32_t  pIn,
                        tFRAMES_BOOL  fMsb)
{
    (void)pCtx;
#   if defined ( BTAMP_LITTLE_ENDIAN_HOST )
    if ( !fMsb )
    {
        BTAMP_MEMCPY(pCtx, pOut, &pIn, 4);
    }
    else
    {
        *pOut         = ( pIn & 0xff000000 ) >> 24;
        *( pOut + 1 ) = ( pIn & 0x00ff0000 ) >> 16;
        *( pOut + 2 ) = ( pIn & 0x0000ff00 ) >>  8;
        *( pOut + 3 ) = ( pIn & 0x000000ff );
    }
#   else
    if ( !fMsb )
    {
        *( pOut     ) = ( pIn & 0x000000ff );
        *( pOut + 1 ) = ( pIn & 0x0000ff00 ) >>  8;
        *( pOut + 2 ) = ( pIn & 0x00ff0000 ) >> 16;
        *( pOut + 3 ) = ( pIn & 0xff000000 ) >> 24;
    }
    else
    {
        BTAMP_MEMCPY(pCtx, pOut, &pIn, 4);
    }
#   endif
}

typedef struct sTLVDefn {
    v_U32_t   id;
    v_U32_t   pec;
    v_U32_t   minSize;
    v_U32_t   maxSize;
    size_t         offset;
    size_t         presenceOffset;
    v_U16_t   sig;
    pfnGeneric_t   pfn;
    const char *   name;
    v_U8_t    fMandatory;
} tTLVDefn;

static tTLVDefn* FindTLVDefn( void *    pCtx,
                              v_U8_t  *pBuf,
                              v_U32_t  nBuf,
                              tTLVDefn      TLVs[ ] )
{
    tTLVDefn    *pTlv;
    v_U32_t      sType, sLen;
    v_U32_t pec;
    v_U16_t id;
 
    sType = 1;
    sLen  = 2;
 
    (void)pCtx;
 
    if (sType == 2) 
        framesntohs( pCtx, &id, pBuf, 2 );
    else {
        id = *pBuf;
    }

    pTlv = &( TLVs[ 0 ] );
    while ( 0xffff != pTlv->id )
    {
        if ( id == pTlv->id )
        {
            if ( 0 == pTlv->pec ) return pTlv;

            if( nBuf > 5 )
            {
                pec =  ( ( * ( pBuf + 4 ) ) << 16 ) |
                       ( ( * ( pBuf + 5 ) ) <<  8 ) |
                           * ( pBuf + 6 );
                if ( pec == pTlv->pec )
                {
                    return pTlv;
                }
            }
        }

        ++pTlv;
    }

    return NULL;
}

static v_U32_t UnpackTlvCore( void *   pCtx,
                                   v_U8_t *pBuf,
                                   v_U32_t nBuf,
                                   tTLVDefn     TLVs[ ],
                                   v_U8_t *pFrm,
                                   size_t       nFrm );
static v_U32_t PackTlvCore(void * pCtx,
                                v_U8_t *pSrc,
                                v_U8_t *pBuf,
                                v_U32_t  nBuf,
                                v_U32_t *pnConsumed,
                                tTLVDefn  TLVs[],
                                v_U32_t *pidx);
static v_U32_t GetPackedSizeTlvCore(void * pCtx,
                                         v_U8_t *pFrm,
                                         v_U32_t *pnNeeded,
                                         tTLVDefn  TLVs[]);

v_U32_t btampUnpackTlvAMP_Assoc_Connected_Channel(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVAMP_Assoc_Connected_Channel *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_AMP_ASSOC_CONN_CH_TLV_MIN_LEN > tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR, "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */


    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->country, pBuf, 3);
    pBuf += 3;
    tlvlen -= (v_U8_t)3;
    if ( ! tlvlen )
    {
        pDst->num_triplets = 0U;
        return 0U;
    }
    else
    {
        /*                                                                     */
        if (tlvlen / 3 > 5)
        {
            tlvlen = 15;
        }
        pDst->num_triplets = (v_U8_t)( tlvlen / 3 );

        BTAMP_MEMCPY(pCtx, pDst->triplets, pBuf, ( tlvlen ) );
        pBuf += ( tlvlen );
        tlvlen -= ( tlvlen );
    }
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvAMP_Assoc_Connected_Channel_t)(void *, v_U8_t*, v_U16_t, tBtampTLVAMP_Assoc_Connected_Channel*);

#define SigUnpackTlvAMP_Assoc_Connected_Channel ( 0x0001 )


v_U32_t btampUnpackTlvAMP_Assoc_MAC_Addr(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVAMP_Assoc_MAC_Addr *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_MAC_ADDR_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,"Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->mac_addr, pBuf, 6);
    pBuf += 6;
    tlvlen -= (v_U8_t)6;
    (void)pCtx;
    return status;
} /*                                       */

typedef v_U32_t (*pfnUnpackTlvAMP_Assoc_MAC_Addr_t)(void *, v_U8_t*, v_U16_t, tBtampTLVAMP_Assoc_MAC_Addr*);

#define SigUnpackTlvAMP_Assoc_MAC_Addr ( 0x0002 )


v_U32_t btampUnpackTlvAMP_Assoc_PAL_Capabilities(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVAMP_Assoc_PAL_Capabilities *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_CAPABILITIES_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,"Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohl(pCtx, &pDst->pal_capabilities, pBuf, 0);
    pBuf += 4;
    tlvlen -= (v_U8_t)4;
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvAMP_Assoc_PAL_Capabilities_t)(void *, v_U8_t*, v_U16_t, tBtampTLVAMP_Assoc_PAL_Capabilities*);

#define SigUnpackTlvAMP_Assoc_PAL_Capabilities ( 0x0003 )


v_U32_t btampUnpackTlvAMP_Assoc_PAL_Version(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVAMP_Assoc_PAL_Version *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */


     /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_VERSION_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,"Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->pal_version = *pBuf;
    pBuf += 1;  
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->pal_CompanyID, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohs(pCtx, &pDst->pal_subversion, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                          */

typedef v_U32_t (*pfnUnpackTlvAMP_Assoc_PAL_Version_t)(void *, v_U8_t*, v_U16_t, tBtampTLVAMP_Assoc_PAL_Version*);

#define SigUnpackTlvAMP_Assoc_PAL_Version ( 0x0004 )


v_U32_t btampUnpackTlvAMP_Assoc_Preferred_Channel_List(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVAMP_Assoc_Preferred_Channel_List *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_AMP_ASSOC_PREF_CH_TLV_MIN_LEN > tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,"Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    /*                         */
    BTAMP_MEMCPY(pCtx, pDst->country, pBuf, 3);
    pBuf += 3;
    tlvlen -= (v_U8_t)3;

    if ( ! tlvlen )
    {
        pDst->num_triplets = 0U;
        return status;
    }
    else
    {
        /*                                                                     */
        if (tlvlen / 3 > 5)
        {
            tlvlen = 15;
        }
        pDst->num_triplets = (v_U8_t)( tlvlen / 3 );

        BTAMP_MEMCPY(pCtx, pDst->triplets, pBuf, ( tlvlen ) );
        pBuf += ( tlvlen );
        tlvlen -= ( tlvlen );
    }
    return status;
} /*                                                     */

typedef v_U32_t (*pfnUnpackTlvAMP_Assoc_Preferred_Channel_List_t)(void *, v_U8_t*, v_U16_t, tBtampTLVAMP_Assoc_Preferred_Channel_List*);

#define SigUnpackTlvAMP_Assoc_Preferred_Channel_List ( 0x0005 )


v_U32_t btampUnpackTlvFlow_Spec(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVFlow_Spec *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_FLOW_SPEC_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING 
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->flow_spec_id = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->service_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->max_sdu, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohl(pCtx, &pDst->sdu_inter_arrival, pBuf, 0);
    pBuf += 4;
    tlvlen -= (v_U8_t)4;
    framesntohl(pCtx, &pDst->access_latency, pBuf, 0);
    pBuf += 4;
    tlvlen -= (v_U8_t)4;
    framesntohl(pCtx, &pDst->flush_timeout, pBuf, 0);
    pBuf += 4;
    tlvlen -= (v_U8_t)4;
    (void)pCtx;
    return status;
} /*                              */

typedef v_U32_t (*pfnUnpackTlvFlow_Spec_t)(void *, v_U8_t*, v_U16_t, tBtampTLVFlow_Spec*);

#define SigUnpackTlvFlow_Spec ( 0x0006 )


v_U32_t btampUnpackTlvHCI_Accept_Logical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Accept_Logical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
#ifdef WLAN_BAPHCI_ENABLE_VALIDITY_CHECKING
    if ( WLAN_BAP_PAL_ACC_LOG_LINK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
//                                       
    }
#endif

    /*                                                                       
                
                                                                            */

    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    BTAMP_MEMCPY(pCtx, pDst->tx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    BTAMP_MEMCPY(pCtx, pDst->rx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Accept_Logical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Accept_Logical_Link_Cmd*);

#define SigUnpackTlvHCI_Accept_Logical_Link_Cmd ( 0x0007 )


v_U32_t btampUnpackTlvHCI_Accept_Physical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Accept_Physical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_ACC_PHY_LINK_TLV_MIN_LEN > tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->key_length = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->key_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    if (pDst->key_length > 32){
        pDst->present = 0;
        return BTAMP_SKIPPED_BAD_IE;
    }

    BTAMP_MEMCPY(pCtx, pDst->key_material, pBuf, ( pDst->key_length ) );
    pBuf += ( pDst->key_length );
    tlvlen -= ( pDst->key_length );
    (void)pCtx;
    return status;
} /*                                                 */

typedef v_U32_t (*pfnUnpackTlvHCI_Accept_Physical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Accept_Physical_Link_Cmd*);

#define SigUnpackTlvHCI_Accept_Physical_Link_Cmd ( 0x0008 )


v_U32_t btampUnpackTlvHCI_Channel_Selected_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Channel_Selected_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Channel_Selected_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Channel_Selected_Event*);

#define SigUnpackTlvHCI_Channel_Selected_Event ( 0x0009 )


v_U32_t btampUnpackTlvHCI_Command_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Command_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    pDst->present = 1;
    pDst->num_hci_command_packets = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->command_opcode, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    switch (pDst->command_opcode)
    {
        case 0x0c03:
            pDst->cc_event.Reset.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c08:
            pDst->cc_event.Flush.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Flush.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 0x043b:
            pDst->cc_event.Logical_Link_Cancel.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Logical_Link_Cancel.phy_link_handle = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Logical_Link_Cancel.tx_flow_spec_id = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c05:
            pDst->cc_event.Set_Event_Mask.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c15:
            pDst->cc_event.Read_Connection_Accept_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Connection_Accept_TO.connection_accept_timeout, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 0x0c16:
            pDst->cc_event.Write_Connection_Accept_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c36:
            pDst->cc_event.Read_Link_Supervision_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Link_Supervision_TO.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Link_Supervision_TO.link_supervision_timeout, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 0x0c37:
            pDst->cc_event.Write_Link_Supervision_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Write_Link_Supervision_TO.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 0x0c61:
            pDst->cc_event.Read_Logical_Link_Accept_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Logical_Link_Accept_TO.logical_link_accept_timeout, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 0x0c62:
            pDst->cc_event.Write_Logical_Link_Accept_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c63:
            pDst->cc_event.Set_Event_Mask_Page_2.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 0x0c64:
            pDst->cc_event.Read_Location_Data.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Location_Data.loc_domain_aware = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            BTAMP_MEMCPY(pCtx, pDst->cc_event.Read_Location_Data.loc_domain, pBuf, 3);
            pBuf += 3;
            tlvlen -= (v_U8_t)3;
            pDst->cc_event.Read_Location_Data.loc_options = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 3173:
            pDst->cc_event.Write_Location_Data.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 3174:
            pDst->cc_event.Read_Flow_Control_Mode.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Flow_Control_Mode.flow_control_mode = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 3175:
            pDst->cc_event.Write_Flow_Control_Mode.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 3177:
            pDst->cc_event.Read_BE_Flush_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohl(pCtx, &pDst->cc_event.Read_BE_Flush_TO.best_effort_flush_timeout, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
        break;
        case 3178:
            pDst->cc_event.Write_BE_Flush_TO.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 3179:
            pDst->cc_event.Set_Short_Range_Mode.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 4097:
            pDst->cc_event.Read_Local_Version_Info.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Local_Version_Info.HC_HCI_Version = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Local_Version_Info.HC_HCI_Revision, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            pDst->cc_event.Read_Local_Version_Info.HC_PAL_Version = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Local_Version_Info.HC_Manufac_Name, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Local_Version_Info.HC_PAL_Sub_Version, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 4098:
            pDst->cc_event.Read_Local_Supported_Cmds.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            BTAMP_MEMCPY(pCtx, pDst->cc_event.Read_Local_Supported_Cmds.HC_Support_Cmds, pBuf, 64);
            pBuf += 64;
            tlvlen -= (v_U8_t)64;
        break;
        case 4101:
            pDst->cc_event.Read_Buffer_Size.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Buffer_Size.HC_ACL_Data_Packet_Length, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            pDst->cc_event.Read_Buffer_Size.HC_SCO_Packet_Length = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Buffer_Size.HC_Total_Num_ACL_Packets, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Buffer_Size.HC_Total_Num_SCO_Packets, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 4106:
            pDst->cc_event.Read_Data_Block_Size.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Data_Block_Size.HC_Max_ACL_Data_Packet_Length, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Data_Block_Size.HC_Data_Block_Length, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Data_Block_Size.HC_Total_Num_Data_Blocks, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 5121:
            pDst->cc_event.Read_Failed_Contact_Counter.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Failed_Contact_Counter.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Failed_Contact_Counter.failed_contact_counter, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 5122:
            pDst->cc_event.Reset_Failed_Contact_Counter.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Reset_Failed_Contact_Counter.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
        break;
        case 5123:
            pDst->cc_event.Read_Link_Quality.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Link_Quality.log_link_handle, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            pDst->cc_event.Read_Link_Quality.link_quality = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 5125:
            pDst->cc_event.Read_RSSI.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_RSSI.phy_link_handle = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_RSSI.rssi = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 5129:
            pDst->cc_event.Read_Local_AMP_Info.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Local_AMP_Info.HC_AMP_Status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_Total_BW, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_Max_Guaranteed_BW, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_Min_Latency, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_Max_PDU_Size, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
            pDst->cc_event.Read_Local_AMP_Info.HC_Controller_Type = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_PAL_Capabilities, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohs(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_AMP_Assoc_Length, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_Max_Flush_Timeout, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
            framesntohl(pCtx, &pDst->cc_event.Read_Local_AMP_Info.HC_BE_Flush_Timeout, pBuf, 0);
            pBuf += 4;
            tlvlen -= (v_U8_t)4;
        break;
        case 5130:
            pDst->cc_event.Read_Read_Local_AMP_Assoc.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Read_Local_AMP_Assoc.phy_link_handle = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            framesntohs(pCtx, &pDst->cc_event.Read_Read_Local_AMP_Assoc.remaining_length, pBuf, 0);
            pBuf += 2;
            tlvlen -= (v_U8_t)2;
            if (pDst->cc_event.Read_Read_Local_AMP_Assoc.remaining_length > 248){
                        //                                                      
                        return BTAMP_SKIPPED_BAD_IE;
            }

            BTAMP_MEMCPY(pCtx, pDst->cc_event.Read_Read_Local_AMP_Assoc.AMP_assoc_fragment, pBuf, ( pDst->cc_event.Read_Read_Local_AMP_Assoc.remaining_length ) );
            pBuf += ( pDst->cc_event.Read_Read_Local_AMP_Assoc.remaining_length );
            tlvlen -= ( pDst->cc_event.Read_Read_Local_AMP_Assoc.remaining_length );
        break;
        case 5131:
            pDst->cc_event.Write_Remote_AMP_Assoc.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Write_Remote_AMP_Assoc.phy_link_handle = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 6145:
            pDst->cc_event.Read_Loopback_Mode.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
            pDst->cc_event.Read_Loopback_Mode.loopback_mode = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
        case 6146:
            pDst->cc_event.Write_Loopback_Mode.status = *pBuf;
            pBuf += 1;
            tlvlen -= (v_U8_t)1;
        break;
    }
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Command_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Command_Complete_Event*);

#define SigUnpackTlvHCI_Command_Complete_Event ( 0x000a )


v_U32_t btampUnpackTlvHCI_Command_Status_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Command_Status_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->num_hci_command_packets = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->command_opcode, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Command_Status_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Command_Status_Event*);

#define SigUnpackTlvHCI_Command_Status_Event ( 0x000b )


v_U32_t btampUnpackTlvHCI_Create_Logical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Create_Logical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
#ifdef WLAN_BAPHCI_ENABLE_VALIDITY_CHECKING
    if ( WLAN_BAP_PAL_CREATE_LOG_LINK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
//                                       
    }
#endif 
    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    BTAMP_MEMCPY(pCtx, pDst->tx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    BTAMP_MEMCPY(pCtx, pDst->rx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Create_Logical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Create_Logical_Link_Cmd*);

#define SigUnpackTlvHCI_Create_Logical_Link_Cmd ( 0x000c )


v_U32_t btampUnpackTlvHCI_Create_Physical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Create_Physical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_CREATE_PHY_LINK_TLV_MIN_LEN > tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING    
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->key_length = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->key_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    if (pDst->key_length > 32){
        pDst->present = 0;
        return BTAMP_SKIPPED_BAD_IE;
    }

    BTAMP_MEMCPY(pCtx, pDst->key_material, pBuf, ( pDst->key_length ) );
    pBuf += ( pDst->key_length );
    tlvlen -= ( pDst->key_length );
    (void)pCtx;
    return status;
} /*                                                 */

typedef v_U32_t (*pfnUnpackTlvHCI_Create_Physical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Create_Physical_Link_Cmd*);

#define SigUnpackTlvHCI_Create_Physical_Link_Cmd ( 0x000d )


v_U32_t btampUnpackTlvHCI_Data_Buffer_Overflow_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Data_Buffer_Overflow_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->link_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                   */

typedef v_U32_t (*pfnUnpackTlvHCI_Data_Buffer_Overflow_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Data_Buffer_Overflow_Event*);

#define SigUnpackTlvHCI_Data_Buffer_Overflow_Event ( 0x000e )


v_U32_t btampUnpackTlvHCI_Disconnect_Logical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Disconnect_Logical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_DISC_LOG_LINK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                    */

typedef v_U32_t (*pfnUnpackTlvHCI_Disconnect_Logical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Disconnect_Logical_Link_Cmd*);

#define SigUnpackTlvHCI_Disconnect_Logical_Link_Cmd ( 0x000f )


v_U32_t btampUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    pDst->reason = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event*);

#define SigUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event ( 0x0010 )


v_U32_t btampUnpackTlvHCI_Disconnect_Physical_Link_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Disconnect_Physical_Link_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
#ifdef WLAN_BAPHCI_ENABLE_VALIDITY_CHECKING
    if ( WLAN_BAP_PAL_DISC_PHY_LINK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
//                                       
    }
#endif      

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->reason = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                     */

typedef v_U32_t (*pfnUnpackTlvHCI_Disconnect_Physical_Link_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Disconnect_Physical_Link_Cmd*);

#define SigUnpackTlvHCI_Disconnect_Physical_Link_Cmd ( 0x0011 )


v_U32_t btampUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
   (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->reason = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event*);

#define SigUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event ( 0x0012 )


v_U32_t btampUnpackTlvHCI_Flow_Spec_Modify_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Flow_Spec_Modify_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_FLOW_SPEC_MOD_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    pDst->be_aggr_counter = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    BTAMP_MEMCPY(pCtx, pDst->tx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    BTAMP_MEMCPY(pCtx, pDst->rx_flow_spec, pBuf, 18);
    pBuf += 18;
    tlvlen -= (v_U8_t)18;
    (void)pCtx;
    return status;
} /*                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Flow_Spec_Modify_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Flow_Spec_Modify_Cmd*);

#define SigUnpackTlvHCI_Flow_Spec_Modify_Cmd ( 0x0013 )


v_U32_t btampUnpackTlvHCI_Flow_Spec_Modify_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                        */

typedef v_U32_t (*pfnUnpackTlvHCI_Flow_Spec_Modify_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event*);

#define SigUnpackTlvHCI_Flow_Spec_Modify_Complete_Event ( 0x0014 )


v_U32_t btampUnpackTlvHCI_Flush_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Flush_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_FLUSH_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                  */

typedef v_U32_t (*pfnUnpackTlvHCI_Flush_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Flush_Cmd*);

#define SigUnpackTlvHCI_Flush_Cmd ( 0x0015 )


v_U32_t btampUnpackTlvHCI_Flush_Occurred_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Flush_Occurred_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Flush_Occurred_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Flush_Occurred_Event*);

#define SigUnpackTlvHCI_Flush_Occurred_Event ( 0x0016 )


v_U32_t btampUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->bd_addr, pBuf, 6);
    pBuf += 6;
    tlvlen -= (v_U8_t)6;
    BTAMP_MEMCPY(pCtx, pDst->generic_amp_link_key, pBuf, 32);
    pBuf += 32;
    tlvlen -= (v_U8_t)32;
    pDst->key_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event*);

#define SigUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event ( 0x0017 )


v_U32_t btampUnpackTlvHCI_Hardware_Error_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Hardware_Error_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->hardware_code = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Hardware_Error_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Hardware_Error_Event*);

#define SigUnpackTlvHCI_Hardware_Error_Event ( 0x0018 )


v_U32_t btampUnpackTlvHCI_Logical_Link_Cancel_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Logical_Link_Cancel_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_CANCEL_LOG_LINK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->tx_flow_spec_id = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Logical_Link_Cancel_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Logical_Link_Cancel_Cmd*);

#define SigUnpackTlvHCI_Logical_Link_Cancel_Cmd ( 0x0019 )


v_U32_t btampUnpackTlvHCI_Logical_Link_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Logical_Link_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                    */

typedef v_U32_t (*pfnUnpackTlvHCI_Logical_Link_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Logical_Link_Complete_Event*);

#define SigUnpackTlvHCI_Logical_Link_Complete_Event ( 0x001a )


v_U32_t btampUnpackTlvHCI_Loopback_Command_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Loopback_Command_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->hci_command_packet, pBuf, 64);
    pBuf += 64;
    tlvlen -= (v_U8_t)64;
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Loopback_Command_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Loopback_Command_Event*);

#define SigUnpackTlvHCI_Loopback_Command_Event ( 0x001b )


v_U32_t btampUnpackTlvHCI_Physical_Link_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Physical_Link_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                     */

typedef v_U32_t (*pfnUnpackTlvHCI_Physical_Link_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Physical_Link_Complete_Event*);

#define SigUnpackTlvHCI_Physical_Link_Complete_Event ( 0x001c )


v_U32_t btampUnpackTlvHCI_Physical_Link_Loss_Warning_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Physical_Link_Loss_Warning_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->reason = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                         */

typedef v_U32_t (*pfnUnpackTlvHCI_Physical_Link_Loss_Warning_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Physical_Link_Loss_Warning_Event*);

#define SigUnpackTlvHCI_Physical_Link_Loss_Warning_Event ( 0x001d )


v_U32_t btampUnpackTlvHCI_Physical_Link_Recovery_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Physical_Link_Recovery_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                     */

typedef v_U32_t (*pfnUnpackTlvHCI_Physical_Link_Recovery_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Physical_Link_Recovery_Event*);

#define SigUnpackTlvHCI_Physical_Link_Recovery_Event ( 0x001e )


v_U32_t btampUnpackTlvHCI_Qos_Violation_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Qos_Violation_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                            */

typedef v_U32_t (*pfnUnpackTlvHCI_Qos_Violation_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Qos_Violation_Event*);

#define SigUnpackTlvHCI_Qos_Violation_Event ( 0x001f )


v_U32_t btampUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_READ_BE_FLUSH_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                           */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd*);

#define SigUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd ( 0x0020 )


v_U32_t btampUnpackTlvHCI_Read_Buffer_Size_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Buffer_Size_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Buffer_Size_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Buffer_Size_Cmd*);

#define SigUnpackTlvHCI_Read_Buffer_Size_Cmd ( 0x0021 )


v_U32_t btampUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                           */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd*);

#define SigUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd ( 0x0022 )


v_U32_t btampUnpackTlvHCI_Read_Data_Block_Size_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Data_Block_Size_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                 */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Data_Block_Size_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Data_Block_Size_Cmd*);

#define SigUnpackTlvHCI_Read_Data_Block_Size_Cmd ( 0x0023 )


v_U32_t btampUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_READ_FAILED_CONTACT_CNT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                        */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd*);

#define SigUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd ( 0x0024 )


v_U32_t btampUnpackTlvHCI_Read_Flow_Control_Mode_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                   */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Flow_Control_Mode_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd*);

#define SigUnpackTlvHCI_Read_Flow_Control_Mode_Cmd ( 0x0025 )


v_U32_t btampUnpackTlvHCI_Read_Link_Quality_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Link_Quality_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_READ_LINK_QUALITY_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                              */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Link_Quality_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Link_Quality_Cmd*);

#define SigUnpackTlvHCI_Read_Link_Quality_Cmd ( 0x0026 )


v_U32_t btampUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_READ_LINK_SVISISON_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                          */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd*);

#define SigUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd ( 0x0027 )


v_U32_t btampUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s. tlvlen=%d.", __func__, tlvlen); 

#ifdef WLAN_BAPHCI_ENABLE_VALIDITY_CHECKING
    if ( WLAN_BAP_PAL_READ_LOCAL_AMP_ASSOC_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
//                                       
    }
#endif      

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->length_so_far, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohs(pCtx, &pDst->max_remote_amp_assoc_length, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                 */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd*);

#define SigUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd ( 0x0028 )


v_U32_t btampUnpackTlvHCI_Read_Local_AMP_Information_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Local_AMP_Information_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
     pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                       */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Local_AMP_Information_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Local_AMP_Information_Cmd*);

#define SigUnpackTlvHCI_Read_Local_AMP_Information_Cmd ( 0x0029 )


v_U32_t btampUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                      */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd*);

#define SigUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd ( 0x002a )


v_U32_t btampUnpackTlvHCI_Read_Local_Version_Info_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Local_Version_Info_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                    */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Local_Version_Info_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Local_Version_Info_Cmd*);

#define SigUnpackTlvHCI_Read_Local_Version_Info_Cmd ( 0x002b )


v_U32_t btampUnpackTlvHCI_Read_Location_Data_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Location_Data_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Location_Data_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Location_Data_Cmd*);

#define SigUnpackTlvHCI_Read_Location_Data_Cmd ( 0x002c )


v_U32_t btampUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                                             */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd*);

#define SigUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd ( 0x002d )


v_U32_t btampUnpackTlvHCI_Read_Loopback_Mode_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_Loopback_Mode_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_Loopback_Mode_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_Loopback_Mode_Cmd*);

#define SigUnpackTlvHCI_Read_Loopback_Mode_Cmd ( 0x002e )


v_U32_t btampUnpackTlvHCI_Read_RSSI_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Read_RSSI_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_READ_RSSI_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                      */

typedef v_U32_t (*pfnUnpackTlvHCI_Read_RSSI_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Read_RSSI_Cmd*);

#define SigUnpackTlvHCI_Read_RSSI_Cmd ( 0x002f )


v_U32_t btampUnpackTlvHCI_Reset_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Reset_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    (void)pCtx;
    return status;
} /*                                  */

typedef v_U32_t (*pfnUnpackTlvHCI_Reset_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Reset_Cmd*);

#define SigUnpackTlvHCI_Reset_Cmd ( 0x0030 )


v_U32_t btampUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_RESET_FAILED_CONTACT_CNT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                         */

typedef v_U32_t (*pfnUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd*);

#define SigUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd ( 0x0031 )


v_U32_t btampUnpackTlvHCI_Set_Event_Mask_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Set_Event_Mask_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_SET_EVENT_MASK_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->event_mask, pBuf, 8);
    pBuf += 8;
    tlvlen -= (v_U8_t)8;
    (void)pCtx;
    return status;
} /*                                           */

typedef v_U32_t (*pfnUnpackTlvHCI_Set_Event_Mask_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Set_Event_Mask_Cmd*);

#define SigUnpackTlvHCI_Set_Event_Mask_Cmd ( 0x0032 )


v_U32_t btampUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */

      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s. tlvlen=%d.", __func__, tlvlen); 
#ifdef WLAN_BAPHCI_ENABLE_VALIDITY_CHECKING
    if ( WLAN_BAP_PAL_SET_EVENT_MASK2_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
//                                       
    }
#endif      

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    BTAMP_MEMCPY(pCtx, pDst->event_mask_page_2, pBuf, 8);
    pBuf += 8;
    tlvlen -= (v_U8_t)8;
    (void)pCtx;
    return status;
} /*                                                  */

typedef v_U32_t (*pfnUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd*);

#define SigUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd ( 0x0033 )


v_U32_t btampUnpackTlvHCI_Set_Short_Range_Mode_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Set_Short_Range_Mode_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_SET_SHORT_RANGE_MODE_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->short_range_mode = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                 */

typedef v_U32_t (*pfnUnpackTlvHCI_Set_Short_Range_Mode_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Set_Short_Range_Mode_Cmd*);

#define SigUnpackTlvHCI_Set_Short_Range_Mode_Cmd ( 0x0034 )


v_U32_t btampUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    pDst->status = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    pDst->short_range_mode = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                               */

typedef v_U32_t (*pfnUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event*);

#define SigUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event ( 0x0035 )


v_U32_t btampUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_BE_FLUSH_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohl(pCtx, &pDst->best_effort_flush_timeout, pBuf, 0);
    pBuf += 4;
    tlvlen -= (v_U8_t)4;
    (void)pCtx;
    return status;
} /*                                                            */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd*);

#define SigUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd ( 0x0036 )


v_U32_t btampUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_CON_ACC_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->connection_accept_timeout, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                            */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd*);

#define SigUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd ( 0x0037 )


v_U32_t btampUnpackTlvHCI_Write_Flow_Control_Mode_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_FLOW_CTRL_MODE_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->flow_control_mode = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                    */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Flow_Control_Mode_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd*);

#define SigUnpackTlvHCI_Write_Flow_Control_Mode_Cmd ( 0x0038 )


v_U32_t btampUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_LINK_SVISION_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohs(pCtx, &pDst->link_supervision_timeout, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                           */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd*);

#define SigUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd ( 0x0039 )


v_U32_t btampUnpackTlvHCI_Write_Location_Data_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Location_Data_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_LOCATION_DATA_CMD_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->loc_domain_aware = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    BTAMP_MEMCPY(pCtx, pDst->loc_domain, pBuf, 3);
    pBuf += 3;
    tlvlen -= (v_U8_t)3;
    pDst->loc_options = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Location_Data_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Location_Data_Cmd*);

#define SigUnpackTlvHCI_Write_Location_Data_Cmd ( 0x003a )


v_U32_t btampUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_LOG_LINK_ACC_TIMEOUT_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->logical_link_accept_timeout, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                              */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd*);

#define SigUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd ( 0x003b )


v_U32_t btampUnpackTlvHCI_Write_Loopback_Mode_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Loopback_Mode_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_LOOOPBACK_MODE_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->loopback_mode = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                                */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Loopback_Mode_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Loopback_Mode_Cmd*);

#define SigUnpackTlvHCI_Write_Loopback_Mode_Cmd ( 0x003c )


v_U32_t btampUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_WRITE_REMOTE_AMP_ASSOC_MIN_TLV_LEN > tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    pDst->phy_link_handle = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    framesntohs(pCtx, &pDst->length_so_far, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    framesntohs(pCtx, &pDst->amp_assoc_remaining_length, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    if (pDst->amp_assoc_remaining_length > 248){
        pDst->present = 0;
        return BTAMP_SKIPPED_BAD_IE;
    }

    BTAMP_MEMCPY(pCtx, pDst->amp_assoc_fragment, pBuf, ( pDst->amp_assoc_remaining_length ) );
    pBuf += ( pDst->amp_assoc_remaining_length );
    tlvlen -= ( pDst->amp_assoc_remaining_length );
    (void)pCtx;
    return status;
} /*                                                   */

typedef v_U32_t (*pfnUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd*);

#define SigUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd ( 0x003d )

v_U32_t btampUnpackTlvHCI_Enhanced_Flush_Cmd(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Enhanced_Flush_Cmd *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */

    /*                                                                       
                        
                                                                             */
    if ( WLAN_BAP_PAL_ENHANCED_FLUSH_TLV_LEN != tlvlen ) 
    {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
      /*               */
      VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, 
            "Invalid TLV len on %s", __func__); 
#endif      
      return BTAMP_INVALID_TLV_LENGTH; 
    }

    /*                                                                       
                
                                                                            */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    pDst->packet_type = *pBuf;
    pBuf += 1;
    tlvlen -= (v_U8_t)1;
    (void)pCtx;
    return status;
} /*                                           */

typedef v_U32_t (*pfnUnpackTlvHCI_Enhanced_Flush_Cmd_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Enhanced_Flush_Cmd*);

#define SigUnpackTlvHCI_Enhanced_Flush_Cmd ( 0x003e )


v_U32_t btampUnpackTlvHCI_Enhanced_Flush_Complete_Event(void * pCtx, v_U8_t *pBuf, v_U16_t tlvlen, tBtampTLVHCI_Enhanced_Flush_Complete_Event *pDst)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pBuf; (void)tlvlen; /*                     */
    pDst->present = 1;
    framesntohs(pCtx, &pDst->log_link_handle, pBuf, 0);
    pBuf += 2;
    tlvlen -= (v_U8_t)2;
    (void)pCtx;
    return status;
} /*                                                       */

typedef v_U32_t (*pfnUnpackTlvHCI_Enhanced_Flush_Complete_Event_t)(void *, v_U8_t*, v_U16_t, tBtampTLVHCI_Enhanced_Flush_Complete_Event*);

#define SigUnpackTlvHCI_Enhanced_Flush_Complete_Event ( 0x003f )


v_U32_t btampUnpackAMP_ASSOC(void * pCtx, v_U8_t *pBuf, v_U32_t nBuf, tBtampAMP_ASSOC *pFrm)
{
    v_U32_t i;
    static tTLVDefn TLVS[ ] = {
        {BTAMP_TLV_AMP_ASSOC_MAC_ADDR, 0, 9, 9, offsetof(tBtampAMP_ASSOC, AMP_Assoc_MAC_Addr), offsetof(tBtampTLVAMP_Assoc_MAC_Addr, present), SigUnpackTlvAMP_Assoc_MAC_Addr, (pfnGeneric_t)btampUnpackTlvAMP_Assoc_MAC_Addr, "AMP_Assoc_MAC_Addr", 1, },
        {BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST, 0, 9, 0xFF/*  */, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Preferred_Channel_List), offsetof(tBtampTLVAMP_Assoc_Preferred_Channel_List, present), SigUnpackTlvAMP_Assoc_Preferred_Channel_List, (pfnGeneric_t)btampUnpackTlvAMP_Assoc_Preferred_Channel_List, "AMP_Assoc_Preferred_Channel_List", 1, },
        {BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL, 0, 9, 0xFF/*  */, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Connected_Channel), offsetof(tBtampTLVAMP_Assoc_Connected_Channel, present), SigUnpackTlvAMP_Assoc_Connected_Channel, (pfnGeneric_t)btampUnpackTlvAMP_Assoc_Connected_Channel, "AMP_Assoc_Connected_Channel", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES, 0, 7, 7, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Capabilities), offsetof(tBtampTLVAMP_Assoc_PAL_Capabilities, present), SigUnpackTlvAMP_Assoc_PAL_Capabilities, (pfnGeneric_t)btampUnpackTlvAMP_Assoc_PAL_Capabilities, "AMP_Assoc_PAL_Capabilities", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_VERSION, 0, 8, 8, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Version), offsetof(tBtampTLVAMP_Assoc_PAL_Version, present), SigUnpackTlvAMP_Assoc_PAL_Version, (pfnGeneric_t)btampUnpackTlvAMP_Assoc_PAL_Version, "AMP_Assoc_PAL_Version", 1, },
    { 0xffff, 0 },
    };

    v_U32_t status = 0;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampUnpackAMP_ASSOC. nBuf - %d\n", nBuf); 
#endif    

    status |= UnpackTlvCore(pCtx,pBuf,nBuf,TLVS,(v_U8_t*)pFrm,sizeof(*pFrm));

    (void)i;
#   ifdef BTAMP_DUMP_FRAMES
    if (!BTAMP_FAILED(status))
    {
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Unpacked the AMP_ASSOC:\n"));
        FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), pBuf, nBuf);
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("to:\n"));
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_MAC_Addr:\n"));
        if (!pFrm->AMP_Assoc_MAC_Addr.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_MAC_Addr.mac_addr, 6);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_Preferred_Channel_List:\n"));
        if (!pFrm->AMP_Assoc_Preferred_Channel_List.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_Preferred_Channel_List.country, 3);
            FRAMES_LOG1(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("num_triplets: %d.\n"), pFrm->AMP_Assoc_Preferred_Channel_List.num_triplets);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* ) pFrm->AMP_Assoc_Preferred_Channel_List.triplets, 3 * pFrm->AMP_Assoc_Preferred_Channel_List.num_triplets);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_Connected_Channel:\n"));
        if (!pFrm->AMP_Assoc_Connected_Channel.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_Connected_Channel.country, 3);
            FRAMES_LOG1(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("num_triplets: %d.\n"), pFrm->AMP_Assoc_Connected_Channel.num_triplets);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* ) pFrm->AMP_Assoc_Connected_Channel.triplets, 3 * pFrm->AMP_Assoc_Connected_Channel.num_triplets);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_PAL_Capabilities:\n"));
        if (!pFrm->AMP_Assoc_PAL_Capabilities.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Capabilities.pal_capabilities, 4);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_PAL_Version:\n"));
        if (!pFrm->AMP_Assoc_PAL_Version.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_version, 1);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_CompanyID, 2);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_subversion, 2);
        }
    }
#   endif //                  
    return status;

} /*                           */

static v_U32_t UnpackTlvCore( void *   pCtx,
                                   v_U8_t *pBuf,
                                   v_U32_t nBuf,
                                   tTLVDefn     TLVs[ ],
                                   v_U8_t *pFrm,
                                   size_t       nFrm )
{
    tTLVDefn *pTlv;
    v_U32_t      nBufRemaining, status, status2, npec;
    v_U32_t      sType, sLen;
    v_U16_t      id, len;
    v_U8_t      *pBufRemaining, *pfFound;

    (void)pCtx;                 //                    
    (void)nFrm;
    status = BTAMP_PARSE_SUCCESS;
    status2 = BTAMP_PARSE_SUCCESS;
    pBufRemaining = pBuf;
    nBufRemaining = nBuf;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In UnpackTlvCore, nBufRemaining - %d\n", nBufRemaining); 
#endif    

    //                      
    while ( nBufRemaining )
    {
        if ( 3 > nBufRemaining )
        {
            FRAMES_LOG0( pCtx, FRLOGE, FRFL( "This frame reports "
                         "fewer three byte(s) remaining.\n" ) );
            status |= BTAMP_INCOMPLETE_TLV;
            FRAMES_DBG_BREAK();
            goto MandatoryCheck;
        }

        npec = 0U;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
        VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
          "Calling FindTLVDefn...\n", nBufRemaining); 
#endif

        //                                    
        pTlv = FindTLVDefn( pCtx, pBufRemaining, nBufRemaining, TLVs );
        sType = 1;
        sLen  = 2;
        //                  
        if (sType == 2) 
            framesntohs(pCtx, &id, pBufRemaining, 1);
        else { 
            id = *pBufRemaining; 
        }
        pBufRemaining += sType;
        nBufRemaining -= sType;
        //          
        framesntohs(pCtx, &len, pBufRemaining, 1);
        pBufRemaining += sLen;
        nBufRemaining -= sLen;

        if ( pTlv && pTlv->pec )
        {
            npec = 3U;
            if ( 3 > nBufRemaining )
            {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
                VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
                  "3 > nBufRemaining\n"); 
#endif

                FRAMES_LOG2(pCtx, FRLOGW, FRFL("TLV %d reports length"
                    "%d, but it has a Private Enterprise Code (3 byte"
                    "s.\n"), id, len);
                FRAMES_DUMP(pCtx, FRLOG1, pBuf, nBuf);
                FRAMES_LOG2(pCtx, FRLOG1, FRFL("We've parsed %d bytes"
                    "of this buffer, and show %d left.\n"),
                pBufRemaining - pBuf, nBufRemaining);
                status |= BTAMP_INCOMPLETE_TLV;
                FRAMES_DBG_BREAK();
                goto MandatoryCheck;
            }
            pBufRemaining += 3;
            nBufRemaining -= 3;
            len           -= 3;
        }
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
        VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
          "Len - %d nBufRemaining - %d\n", len, nBufRemaining); 
#endif

        //                                                            
        //                    
        if ( len > nBufRemaining )
        {
            FRAMES_LOG3(pCtx, FRLOGW, FRFL("TLV %d reports length %"
                "d, but there are only %d bytes remaining in this f"
                "rame.\n"), id, len, nBufRemaining );
            FRAMES_DUMP( pCtx, FRLOG1, pBuf, nBuf );
            FRAMES_LOG2( pCtx, FRLOG1, FRFL( "We've parsed %d bytes"
                " of this buffer, and show %d left.\n"),
                pBufRemaining - pBuf, nBufRemaining);
            status |= BTAMP_INCOMPLETE_TLV;
            FRAMES_DBG_BREAK();
            goto MandatoryCheck;
        }

        //                            
        if ( pTlv )
        {
            if ( nBufRemaining < pTlv->minSize - npec - (sType + sLen))
            {
                FRAMES_LOG3( pCtx, FRLOGW, FRFL("The IE %s must be "
                    "at least %d bytes in size, but there are only "
                    "%d bytes remaining in this frame.\n"),
                     pTlv->name, pTlv->minSize, nBufRemaining );
                FRAMES_DUMP( pCtx, FRLOG1, pBuf, nBuf );
                status |= BTAMP_INCOMPLETE_TLV;
                FRAMES_DBG_BREAK( );
                goto MandatoryCheck;
            }
            else if ( len > pTlv->maxSize - npec - (sType + sLen))
            {
                FRAMES_LOG1( pCtx, FRLOGW, FRFL("The TLV %s reports "
                    "an illegally large size; this TLV is presumably"
                    "corrupt or otherwise invalid & will be skipped "
                    "ipped.\n"), pTlv->name );
                FRAMES_DUMP( pCtx, FRLOG1, pBuf, nBuf );
                FRAMES_LOG2( pCtx, FRLOG1, FRFL("We've parsed %d by"
                    "tes of this buffer, and show %d left.\n"),
                    pBufRemaining - pBuf, nBufRemaining);
                FRAMES_DBG_BREAK();
                status |= BTAMP_SKIPPED_BAD_TLV;
            }
            else
            {
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
                VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
                  "pTlv->sig - %d\n", pTlv->sig); 
#endif

                switch (pTlv->sig)
                {
                case SigUnpackTlvAMP_Assoc_Connected_Channel:
                        status2 = ( (pfnUnpackTlvAMP_Assoc_Connected_Channel_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVAMP_Assoc_Connected_Channel* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvAMP_Assoc_MAC_Addr:
                        status2 = ( (pfnUnpackTlvAMP_Assoc_MAC_Addr_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVAMP_Assoc_MAC_Addr* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvAMP_Assoc_PAL_Capabilities:
                        status2 = ( (pfnUnpackTlvAMP_Assoc_PAL_Capabilities_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVAMP_Assoc_PAL_Capabilities* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvAMP_Assoc_PAL_Version:
                        status2 = ( (pfnUnpackTlvAMP_Assoc_PAL_Version_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVAMP_Assoc_PAL_Version* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvAMP_Assoc_Preferred_Channel_List:
                        status2 = ( (pfnUnpackTlvAMP_Assoc_Preferred_Channel_List_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVAMP_Assoc_Preferred_Channel_List* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvFlow_Spec:
                        status2 = ( (pfnUnpackTlvFlow_Spec_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVFlow_Spec* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Accept_Logical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Accept_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Accept_Logical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Accept_Physical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Accept_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Accept_Physical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Channel_Selected_Event:
                        status2 = ( (pfnUnpackTlvHCI_Channel_Selected_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Channel_Selected_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Command_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Command_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Command_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Command_Status_Event:
                        status2 = ( (pfnUnpackTlvHCI_Command_Status_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Command_Status_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Create_Logical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Create_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Create_Logical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Create_Physical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Create_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Create_Physical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Data_Buffer_Overflow_Event:
                        status2 = ( (pfnUnpackTlvHCI_Data_Buffer_Overflow_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Data_Buffer_Overflow_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Disconnect_Logical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Disconnect_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Disconnect_Logical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Disconnect_Physical_Link_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Disconnect_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Disconnect_Physical_Link_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Flow_Spec_Modify_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Flow_Spec_Modify_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Flow_Spec_Modify_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Flow_Spec_Modify_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Flow_Spec_Modify_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Flow_Spec_Modify_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Flush_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Flush_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Flush_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Flush_Occurred_Event:
                        status2 = ( (pfnUnpackTlvHCI_Flush_Occurred_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Flush_Occurred_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event:
                        status2 = ( (pfnUnpackTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Hardware_Error_Event:
                        status2 = ( (pfnUnpackTlvHCI_Hardware_Error_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Hardware_Error_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Logical_Link_Cancel_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Logical_Link_Cancel_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Logical_Link_Cancel_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Logical_Link_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Logical_Link_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Loopback_Command_Event:
                        status2 = ( (pfnUnpackTlvHCI_Loopback_Command_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Loopback_Command_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Physical_Link_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Physical_Link_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Physical_Link_Loss_Warning_Event:
                        status2 = ( (pfnUnpackTlvHCI_Physical_Link_Loss_Warning_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Physical_Link_Loss_Warning_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Physical_Link_Recovery_Event:
                        status2 = ( (pfnUnpackTlvHCI_Physical_Link_Recovery_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Physical_Link_Recovery_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Qos_Violation_Event:
                        status2 = ( (pfnUnpackTlvHCI_Qos_Violation_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Qos_Violation_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Buffer_Size_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Buffer_Size_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Buffer_Size_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Data_Block_Size_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Data_Block_Size_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Data_Block_Size_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Flow_Control_Mode_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Link_Quality_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Link_Quality_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Link_Quality_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Local_AMP_Information_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Local_AMP_Information_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Local_AMP_Information_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Local_Version_Info_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Local_Version_Info_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Local_Version_Info_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Location_Data_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Location_Data_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_Loopback_Mode_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_Loopback_Mode_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Read_RSSI_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Read_RSSI_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Read_RSSI_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Reset_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Reset_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Reset_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Set_Event_Mask_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Set_Event_Mask_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Set_Event_Mask_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Set_Short_Range_Mode_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Set_Short_Range_Mode_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Set_Short_Range_Mode_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event:
                        status2 = ( (pfnUnpackTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Flow_Control_Mode_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Location_Data_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Location_Data_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Loopback_Mode_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Loopback_Mode_Cmd* )(pFrm + pTlv->offset ));
                    break;
                case SigUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd:
                        status2 = ( (pfnUnpackTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(pTlv->pfn) )(pCtx, pBufRemaining, len, ( tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd* )(pFrm + pTlv->offset ));
                    break;
                default:
                    FRAMES_LOG1(pCtx, FRLOGE, FRFL("INTERNAL ERROR: I"
                        " don't know about the TLV signature %d-- thi"
                        "s is most likely a 'framesc' bug.\n"),
                        pTlv->sig);
                    FRAMES_DBG_BREAK();
                    return BTAMP_INTERNAL_ERROR;
                } //                   
            } //                        

            status |= status2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
            VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
              "status - %x\n", status); 
#endif
        }
        else
        {
            FRAMES_LOG2(pCtx, FRLOG3, FRFL("Skipping unknown TLV %d ("
                "length %d)\n"), id, len);
            FRAMES_DUMP(pCtx, FRLOG3, pBufRemaining - (sType + sLen), len);
            status |= BTAMP_UNKNOWN_TLVS;
        }

        //                        
        pBufRemaining += len;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
        VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
          "len - %d nBufRemaining - %d\n", len, nBufRemaining); 
#endif

        if (len > nBufRemaining)
         {
             FRAMES_LOG0(pCtx, FRLOGW, FRFL("This TLV extends past th"
                 "e buffer as it was defined to us.  This could mean "
                 "a corrupt frame, or just an incorrect length parame"
                 "ter.\n"));
             FRAMES_DBG_BREAK();
             status |= BTAMP_LAST_TLV_TOO_LONG;
             goto MandatoryCheck;
         }

        nBufRemaining -= len;

    } //                         

MandatoryCheck:
    pTlv = &TLVs[0];
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "pTlv->id - %x\n", pTlv->id); 
#endif    

    while (0xffff != pTlv->id)
    {
        if (pTlv->fMandatory)
        {
            pfFound = (v_U8_t*)(pFrm + pTlv->offset +
                             pTlv->presenceOffset);
            if (!*pfFound)
            {
                FRAMES_LOG1(pCtx, FRLOGW, FRFL("ERROR: The mandatory "
                    "TLV %s wasn't seen.\n"),
                    pTlv->name);
                FRAMES_DBG_BREAK();
                status |= BTAMP_MANDATORY_TLV_MISSING;
            }

        }
        ++pTlv;
    }

    return status;
} /*                    */
v_U32_t btampGetPackedTlvAMP_Assoc_Connected_Channel(void * pCtx, tBtampTLVAMP_Assoc_Connected_Channel *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedTlvAMP_Assoc_Connected_Channel\n"); 
#endif    

    while ( pTlv->present )
    {
        *pnNeeded += 3;
        if ( pTlv->num_triplets )
        {
            *pnNeeded += ( pTlv->num_triplets * 3 );
        }
        else break;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvAMP_Assoc_Connected_Channel_t)(void *, tBtampTLVAMP_Assoc_Connected_Channel*, v_U32_t*);
#define SigPackSizeTlvAMP_Assoc_Connected_Channel ( 0x003e )

v_U32_t btampGetPackedTlvAMP_Assoc_MAC_Addr(void * pCtx, tBtampTLVAMP_Assoc_MAC_Addr *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedTlvAMP_Assoc_MAC_Addr\n"); 
#endif    

    while ( pTlv->present )
    {
        *pnNeeded += 6;
        break;
    }
    return status;
} /*                                          */

typedef v_U32_t (*pfnPackSizeTlvAMP_Assoc_MAC_Addr_t)(void *, tBtampTLVAMP_Assoc_MAC_Addr*, v_U32_t*);
#define SigPackSizeTlvAMP_Assoc_MAC_Addr ( 0x003f )

v_U32_t btampGetPackedTlvAMP_Assoc_PAL_Capabilities(void * pCtx, tBtampTLVAMP_Assoc_PAL_Capabilities *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedTlvAMP_Assoc_PAL_Capabilities\n"); 
#endif    

    while ( pTlv->present )
    {
        *pnNeeded += 4;
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvAMP_Assoc_PAL_Capabilities_t)(void *, tBtampTLVAMP_Assoc_PAL_Capabilities*, v_U32_t*);
#define SigPackSizeTlvAMP_Assoc_PAL_Capabilities ( 0x0040 )

v_U32_t btampGetPackedTlvAMP_Assoc_PAL_Version(void * pCtx, tBtampTLVAMP_Assoc_PAL_Version *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackSizeTlvAMP_Assoc_PAL_Version_t)(void *, tBtampTLVAMP_Assoc_PAL_Version*, v_U32_t*);
#define SigPackSizeTlvAMP_Assoc_PAL_Version ( 0x0041 )

v_U32_t btampGetPackedTlvAMP_Assoc_Preferred_Channel_List(void * pCtx, tBtampTLVAMP_Assoc_Preferred_Channel_List *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedTlvAMP_Assoc_Preferred_Channel_List\n"); 
#endif    

    while ( pTlv->present )
    {
        *pnNeeded += 3;
        if ( pTlv->num_triplets )
        {
            *pnNeeded += ( pTlv->num_triplets * 3 );
        }
        else break;
        break;
    }
    return status;
} /*                                                        */

typedef v_U32_t (*pfnPackSizeTlvAMP_Assoc_Preferred_Channel_List_t)(void *, tBtampTLVAMP_Assoc_Preferred_Channel_List*, v_U32_t*);
#define SigPackSizeTlvAMP_Assoc_Preferred_Channel_List ( 0x0042 )

v_U32_t btampGetPackedTlvFlow_Spec(void * pCtx, tBtampTLVFlow_Spec *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 4;
        *pnNeeded += 4;
        *pnNeeded += 4;
        break;
    }
    return status;
} /*                                 */

typedef v_U32_t (*pfnPackSizeTlvFlow_Spec_t)(void *, tBtampTLVFlow_Spec*, v_U32_t*);
#define SigPackSizeTlvFlow_Spec ( 0x0043 )

v_U32_t btampGetPackedTlvHCI_Accept_Logical_Link_Cmd(void * pCtx, tBtampTLVHCI_Accept_Logical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 18;
        *pnNeeded += 18;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Accept_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Accept_Logical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Accept_Logical_Link_Cmd ( 0x0044 )

v_U32_t btampGetPackedTlvHCI_Accept_Physical_Link_Cmd(void * pCtx, tBtampTLVHCI_Accept_Physical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += pTlv->key_length;
        break;
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackSizeTlvHCI_Accept_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Accept_Physical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Accept_Physical_Link_Cmd ( 0x0045 )

v_U32_t btampGetPackedTlvHCI_Channel_Selected_Event(void * pCtx, tBtampTLVHCI_Channel_Selected_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Channel_Selected_Event_t)(void *, tBtampTLVHCI_Channel_Selected_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Channel_Selected_Event ( 0x0046 )

v_U32_t btampGetPackedTlvHCI_Command_Complete_Event(void * pCtx, tBtampTLVHCI_Command_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        switch (pTlv->command_opcode)
        {
            case 3075:
                *pnNeeded += 1;
            break;
            case 3080:
                *pnNeeded += 1;
                *pnNeeded += 2;
            break;
            case 1083:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 1;
            break;
            case 3077:
                *pnNeeded += 1;
            break;
            case 3093:
                *pnNeeded += 1;
                *pnNeeded += 2;
            break;
            case 3094:
                *pnNeeded += 1;
            break;
            case 3126:
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
            break;
            case 3127:
                *pnNeeded += 1;
                *pnNeeded += 2;
            break;
            case 3169:
                *pnNeeded += 1;
                *pnNeeded += 2;
            break;
            case 3170:
                *pnNeeded += 1;
            break;
            case 3171:
                *pnNeeded += 1;
            break;
            case 3172:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 3;
                *pnNeeded += 1;
            break;
            case 3173:
                *pnNeeded += 1;
            break;
            case 3174:
                *pnNeeded += 1;
                *pnNeeded += 1;
            break;
            case 3175:
                *pnNeeded += 1;
            break;
            case 3177:
                *pnNeeded += 1;
                *pnNeeded += 4;
            break;
            case 3178:
                *pnNeeded += 1;
            break;
            case 3179:
                *pnNeeded += 1;
            break;
            case 4097:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
            break;
            case 4098:
                *pnNeeded += 1;
                *pnNeeded += 64;
            break;
            case 4101:
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
            break;
            case 4106:
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
                *pnNeeded += 2;
            break;
            case 5121:
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
            break;
            case 5122:
                *pnNeeded += 1;
                *pnNeeded += 2;
            break;
            case 5123:
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 1;
            break;
            case 5125:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 1;
            break;
            case 5129:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 4;
                *pnNeeded += 4;
                *pnNeeded += 4;
                *pnNeeded += 4;
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += 2;
                *pnNeeded += 4;
                *pnNeeded += 4;
            break;
            case 5130:
                *pnNeeded += 1;
                *pnNeeded += 1;
                *pnNeeded += 2;
                *pnNeeded += pTlv->cc_event.Read_Read_Local_AMP_Assoc.remaining_length;
            break;
            case 5131:
                *pnNeeded += 1;
                *pnNeeded += 1;
            break;
            case 6145:
                *pnNeeded += 1;
                *pnNeeded += 1;
            break;
            case 6146:
                *pnNeeded += 1;
            break;
        }
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Command_Complete_Event_t)(void *, tBtampTLVHCI_Command_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Command_Complete_Event ( 0x0047 )

v_U32_t btampGetPackedTlvHCI_Command_Status_Event(void * pCtx, tBtampTLVHCI_Command_Status_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Command_Status_Event_t)(void *, tBtampTLVHCI_Command_Status_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Command_Status_Event ( 0x0048 )

v_U32_t btampGetPackedTlvHCI_Create_Logical_Link_Cmd(void * pCtx, tBtampTLVHCI_Create_Logical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 18;
        *pnNeeded += 18;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Create_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Create_Logical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Create_Logical_Link_Cmd ( 0x0049 )

v_U32_t btampGetPackedTlvHCI_Create_Physical_Link_Cmd(void * pCtx, tBtampTLVHCI_Create_Physical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += pTlv->key_length;
        break;
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackSizeTlvHCI_Create_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Create_Physical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Create_Physical_Link_Cmd ( 0x004a )

v_U32_t btampGetPackedTlvHCI_Data_Buffer_Overflow_Event(void * pCtx, tBtampTLVHCI_Data_Buffer_Overflow_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                      */

typedef v_U32_t (*pfnPackSizeTlvHCI_Data_Buffer_Overflow_Event_t)(void *, tBtampTLVHCI_Data_Buffer_Overflow_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Data_Buffer_Overflow_Event ( 0x004b )

v_U32_t btampGetPackedTlvHCI_Disconnect_Logical_Link_Cmd(void * pCtx, tBtampTLVHCI_Disconnect_Logical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackSizeTlvHCI_Disconnect_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Disconnect_Logical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Disconnect_Logical_Link_Cmd ( 0x004c )

v_U32_t btampGetPackedTlvHCI_Disconnect_Logical_Link_Complete_Event(void * pCtx, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Disconnect_Logical_Link_Complete_Event ( 0x004d )

v_U32_t btampGetPackedTlvHCI_Disconnect_Physical_Link_Cmd(void * pCtx, tBtampTLVHCI_Disconnect_Physical_Link_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                        */

typedef v_U32_t (*pfnPackSizeTlvHCI_Disconnect_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Disconnect_Physical_Link_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Disconnect_Physical_Link_Cmd ( 0x004e )

v_U32_t btampGetPackedTlvHCI_Disconnect_Physical_Link_Complete_Event(void * pCtx, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Disconnect_Physical_Link_Complete_Event ( 0x004f )

v_U32_t btampGetPackedTlvHCI_Flow_Spec_Modify_Cmd(void * pCtx, tBtampTLVHCI_Flow_Spec_Modify_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        *pnNeeded += 1;
        *pnNeeded += 18;
        *pnNeeded += 18;
        break;
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Flow_Spec_Modify_Cmd_t)(void *, tBtampTLVHCI_Flow_Spec_Modify_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Flow_Spec_Modify_Cmd ( 0x0050 )

v_U32_t btampGetPackedTlvHCI_Flow_Spec_Modify_Complete_Event(void * pCtx, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                           */

typedef v_U32_t (*pfnPackSizeTlvHCI_Flow_Spec_Modify_Complete_Event_t)(void *, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Flow_Spec_Modify_Complete_Event ( 0x0051 )

v_U32_t btampGetPackedTlvHCI_Flush_Cmd(void * pCtx, tBtampTLVHCI_Flush_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                     */

typedef v_U32_t (*pfnPackSizeTlvHCI_Flush_Cmd_t)(void *, tBtampTLVHCI_Flush_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Flush_Cmd ( 0x0052 )

v_U32_t btampGetPackedTlvHCI_Flush_Occurred_Event(void * pCtx, tBtampTLVHCI_Flush_Occurred_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Flush_Occurred_Event_t)(void *, tBtampTLVHCI_Flush_Occurred_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Flush_Occurred_Event ( 0x0053 )

v_U32_t btampGetPackedTlvHCI_Num_Completed_Pkts_Event(void * pCtx, tBtampTLVHCI_Num_Completed_Pkts_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
//                           
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 2;
#if 0
//     
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += 2;
//            
#endif
//              
    }
    return status;
} /*                                                    */

v_U32_t btampGetPackedTlvHCI_Num_Completed_Data_Blocks_Event(void * pCtx, tBtampTLVHCI_Num_Completed_Data_Blocks_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
//                           
    {
        *pnNeeded += 2;
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += 2;
//              
    }
    return status;
} /*                                                           */

//                                                                                                                      
//                                                             

v_U32_t btampGetPackedTlvHCI_Generic_AMP_Link_Key_Notification_Event(void * pCtx, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 6;
        *pnNeeded += 32;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(void *, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Generic_AMP_Link_Key_Notification_Event ( 0x0054 )

v_U32_t btampGetPackedTlvHCI_Hardware_Error_Event(void * pCtx, tBtampTLVHCI_Hardware_Error_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Hardware_Error_Event_t)(void *, tBtampTLVHCI_Hardware_Error_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Hardware_Error_Event ( 0x0055 )

v_U32_t btampGetPackedTlvHCI_Logical_Link_Cancel_Cmd(void * pCtx, tBtampTLVHCI_Logical_Link_Cancel_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Logical_Link_Cancel_Cmd_t)(void *, tBtampTLVHCI_Logical_Link_Cancel_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Logical_Link_Cancel_Cmd ( 0x0056 )

v_U32_t btampGetPackedTlvHCI_Logical_Link_Complete_Event(void * pCtx, tBtampTLVHCI_Logical_Link_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackSizeTlvHCI_Logical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Logical_Link_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Logical_Link_Complete_Event ( 0x0057 )

v_U32_t btampGetPackedTlvHCI_Loopback_Command_Event(void * pCtx, tBtampTLVHCI_Loopback_Command_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 64;
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Loopback_Command_Event_t)(void *, tBtampTLVHCI_Loopback_Command_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Loopback_Command_Event ( 0x0058 )

v_U32_t btampGetPackedTlvHCI_Physical_Link_Complete_Event(void * pCtx, tBtampTLVHCI_Physical_Link_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                        */

typedef v_U32_t (*pfnPackSizeTlvHCI_Physical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Physical_Link_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Physical_Link_Complete_Event ( 0x0059 )

v_U32_t btampGetPackedTlvHCI_Physical_Link_Loss_Warning_Event(void * pCtx, tBtampTLVHCI_Physical_Link_Loss_Warning_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                            */

typedef v_U32_t (*pfnPackSizeTlvHCI_Physical_Link_Loss_Warning_Event_t)(void *, tBtampTLVHCI_Physical_Link_Loss_Warning_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Physical_Link_Loss_Warning_Event ( 0x005a )

v_U32_t btampGetPackedTlvHCI_Physical_Link_Recovery_Event(void * pCtx, tBtampTLVHCI_Physical_Link_Recovery_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                        */

typedef v_U32_t (*pfnPackSizeTlvHCI_Physical_Link_Recovery_Event_t)(void *, tBtampTLVHCI_Physical_Link_Recovery_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Physical_Link_Recovery_Event ( 0x005b )

v_U32_t btampGetPackedTlvHCI_Qos_Violation_Event(void * pCtx, tBtampTLVHCI_Qos_Violation_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackSizeTlvHCI_Qos_Violation_Event_t)(void *, tBtampTLVHCI_Qos_Violation_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Qos_Violation_Event ( 0x005c )

v_U32_t btampGetPackedTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                              */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd ( 0x005d )

v_U32_t btampGetPackedTlvHCI_Read_Buffer_Size_Cmd(void * pCtx, tBtampTLVHCI_Read_Buffer_Size_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Buffer_Size_Cmd_t)(void *, tBtampTLVHCI_Read_Buffer_Size_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Buffer_Size_Cmd ( 0x005e )

v_U32_t btampGetPackedTlvHCI_Read_Connection_Accept_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                              */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Connection_Accept_Timeout_Cmd ( 0x005f )

v_U32_t btampGetPackedTlvHCI_Read_Data_Block_Size_Cmd(void * pCtx, tBtampTLVHCI_Read_Data_Block_Size_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Data_Block_Size_Cmd_t)(void *, tBtampTLVHCI_Read_Data_Block_Size_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Data_Block_Size_Cmd ( 0x0060 )

v_U32_t btampGetPackedTlvHCI_Read_Failed_Contact_Counter_Cmd(void * pCtx, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                           */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(void *, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Failed_Contact_Counter_Cmd ( 0x0061 )

v_U32_t btampGetPackedTlvHCI_Read_Flow_Control_Mode_Cmd(void * pCtx, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                      */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Flow_Control_Mode_Cmd_t)(void *, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Flow_Control_Mode_Cmd ( 0x0062 )

v_U32_t btampGetPackedTlvHCI_Read_Link_Quality_Cmd(void * pCtx, tBtampTLVHCI_Read_Link_Quality_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                 */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Link_Quality_Cmd_t)(void *, tBtampTLVHCI_Read_Link_Quality_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Link_Quality_Cmd ( 0x0063 )

v_U32_t btampGetPackedTlvHCI_Read_Link_Supervision_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                             */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Link_Supervision_Timeout_Cmd ( 0x0064 )

v_U32_t btampGetPackedTlvHCI_Read_Local_AMP_Assoc_Cmd(void * pCtx, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(void *, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Local_AMP_Assoc_Cmd ( 0x0065 )

v_U32_t btampGetPackedTlvHCI_Read_Local_AMP_Information_Cmd(void * pCtx, tBtampTLVHCI_Read_Local_AMP_Information_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                          */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Local_AMP_Information_Cmd_t)(void *, tBtampTLVHCI_Read_Local_AMP_Information_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Local_AMP_Information_Cmd ( 0x0066 )

v_U32_t btampGetPackedTlvHCI_Read_Local_Supported_Cmds_Cmd(void * pCtx, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                         */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(void *, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Local_Supported_Cmds_Cmd ( 0x0067 )

v_U32_t btampGetPackedTlvHCI_Read_Local_Version_Info_Cmd(void * pCtx, tBtampTLVHCI_Read_Local_Version_Info_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Local_Version_Info_Cmd_t)(void *, tBtampTLVHCI_Read_Local_Version_Info_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Local_Version_Info_Cmd ( 0x0068 )

v_U32_t btampGetPackedTlvHCI_Read_Location_Data_Cmd(void * pCtx, tBtampTLVHCI_Read_Location_Data_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Location_Data_Cmd_t)(void *, tBtampTLVHCI_Read_Location_Data_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Location_Data_Cmd ( 0x0069 )

v_U32_t btampGetPackedTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                                */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd ( 0x006a )

v_U32_t btampGetPackedTlvHCI_Read_Loopback_Mode_Cmd(void * pCtx, tBtampTLVHCI_Read_Loopback_Mode_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_Loopback_Mode_Cmd_t)(void *, tBtampTLVHCI_Read_Loopback_Mode_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_Loopback_Mode_Cmd ( 0x006b )

v_U32_t btampGetPackedTlvHCI_Read_RSSI_Cmd(void * pCtx, tBtampTLVHCI_Read_RSSI_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                         */

typedef v_U32_t (*pfnPackSizeTlvHCI_Read_RSSI_Cmd_t)(void *, tBtampTLVHCI_Read_RSSI_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Read_RSSI_Cmd ( 0x006c )

v_U32_t btampGetPackedTlvHCI_Reset_Cmd(void * pCtx, tBtampTLVHCI_Reset_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        break;
    }
    return status;
} /*                                     */

typedef v_U32_t (*pfnPackSizeTlvHCI_Reset_Cmd_t)(void *, tBtampTLVHCI_Reset_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Reset_Cmd ( 0x006d )

v_U32_t btampGetPackedTlvHCI_Reset_Failed_Contact_Counter_Cmd(void * pCtx, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                            */

typedef v_U32_t (*pfnPackSizeTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(void *, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Reset_Failed_Contact_Counter_Cmd ( 0x006e )

v_U32_t btampGetPackedTlvHCI_Set_Event_Mask_Cmd(void * pCtx, tBtampTLVHCI_Set_Event_Mask_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 8;
        break;
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackSizeTlvHCI_Set_Event_Mask_Cmd_t)(void *, tBtampTLVHCI_Set_Event_Mask_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Set_Event_Mask_Cmd ( 0x006f )

v_U32_t btampGetPackedTlvHCI_Set_Event_Mask_Page_2_Cmd(void * pCtx, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 8;
        break;
    }
    return status;
} /*                                                     */

typedef v_U32_t (*pfnPackSizeTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(void *, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Set_Event_Mask_Page_2_Cmd ( 0x0070 )

v_U32_t btampGetPackedTlvHCI_Set_Short_Range_Mode_Cmd(void * pCtx, tBtampTLVHCI_Set_Short_Range_Mode_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackSizeTlvHCI_Set_Short_Range_Mode_Cmd_t)(void *, tBtampTLVHCI_Set_Short_Range_Mode_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Set_Short_Range_Mode_Cmd ( 0x0071 )

v_U32_t btampGetPackedTlvHCI_Short_Range_Mode_Change_Complete_Event(void * pCtx, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 1;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                                  */

typedef v_U32_t (*pfnPackSizeTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(void *, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Short_Range_Mode_Change_Complete_Event ( 0x0072 )

v_U32_t btampGetPackedTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        *pnNeeded += 4;
        break;
    }
    return status;
} /*                                                               */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd ( 0x0073 )

v_U32_t btampGetPackedTlvHCI_Write_Connection_Accept_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                               */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Connection_Accept_Timeout_Cmd ( 0x0074 )

v_U32_t btampGetPackedTlvHCI_Write_Flow_Control_Mode_Cmd(void * pCtx, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Flow_Control_Mode_Cmd_t)(void *, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Flow_Control_Mode_Cmd ( 0x0075 )

v_U32_t btampGetPackedTlvHCI_Write_Link_Supervision_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                              */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Link_Supervision_Timeout_Cmd ( 0x0076 )

v_U32_t btampGetPackedTlvHCI_Write_Location_Data_Cmd(void * pCtx, tBtampTLVHCI_Write_Location_Data_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 3;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Location_Data_Cmd_t)(void *, tBtampTLVHCI_Write_Location_Data_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Location_Data_Cmd ( 0x0077 )

v_U32_t btampGetPackedTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void * pCtx, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                                 */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd ( 0x0078 )

v_U32_t btampGetPackedTlvHCI_Write_Loopback_Mode_Cmd(void * pCtx, tBtampTLVHCI_Write_Loopback_Mode_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Loopback_Mode_Cmd_t)(void *, tBtampTLVHCI_Write_Loopback_Mode_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Loopback_Mode_Cmd ( 0x0079 )

v_U32_t btampGetPackedTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void * pCtx, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedTlvHCI_Write_Remote_AMP_ASSOC_Cmd\n"); 
#endif    

    while ( pTlv->present )
    {
        *pnNeeded += 1;
        *pnNeeded += 2;
        *pnNeeded += 2;
        *pnNeeded += pTlv->amp_assoc_remaining_length;
        break;
    }
    return status;
} /*                                                      */

typedef v_U32_t (*pfnPackSizeTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(void *, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Write_Remote_AMP_ASSOC_Cmd ( 0x007a )

v_U32_t btampGetPackedTlvHCI_Enhanced_Flush_Cmd(void * pCtx, tBtampTLVHCI_Enhanced_Flush_Cmd *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        *pnNeeded += 1;
        break;
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackSizeTlvHCI_Enhanced_Flush_Cmd_t)(void *, tBtampTLVHCI_Enhanced_Flush_Cmd*, v_U32_t*);
#define SigPackSizeTlvHCI_Enhanced_Flush_Cmd ( 0x007b )

v_U32_t btampGetPackedTlvHCI_Enhanced_Flush_Complete_Event(void * pCtx, tBtampTLVHCI_Enhanced_Flush_Complete_Event *pTlv, v_U32_t *pnNeeded)
{
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    (void)pCtx; (void)pTlv; (void)pnNeeded;
    while ( pTlv->present )
    {
        *pnNeeded += 2;
        break;
    }
    return status;
} /*                                                         */

typedef v_U32_t (*pfnPackSizeTlvHCI_Enhanced_Flush_Complete_Event_t)(void *, tBtampTLVHCI_Enhanced_Flush_Complete_Event*, v_U32_t*);
#define SigPackSizeTlvHCI_Enhanced_Flush_Complete_Event ( 0x007c )

v_U32_t btampGetPackedAMP_ASSOCSize(void * pCtx, tBtampAMP_ASSOC *pFrm, v_U32_t *pnNeeded)
{
    static tTLVDefn TLVS[ ] = {
        {BTAMP_TLV_AMP_ASSOC_MAC_ADDR, 0, 9, 9, offsetof(tBtampAMP_ASSOC, AMP_Assoc_MAC_Addr), offsetof(tBtampTLVAMP_Assoc_MAC_Addr, present), SigPackSizeTlvAMP_Assoc_MAC_Addr, (pfnGeneric_t)btampGetPackedTlvAMP_Assoc_MAC_Addr, "AMP_Assoc_MAC_Addr", 1, },
        {BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST, 0, 9, 12, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Preferred_Channel_List), offsetof(tBtampTLVAMP_Assoc_Preferred_Channel_List, present), SigPackSizeTlvAMP_Assoc_Preferred_Channel_List, (pfnGeneric_t)btampGetPackedTlvAMP_Assoc_Preferred_Channel_List, "AMP_Assoc_Preferred_Channel_List", 1, },
        {BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL, 0, 9, 12, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Connected_Channel), offsetof(tBtampTLVAMP_Assoc_Connected_Channel, present), SigPackSizeTlvAMP_Assoc_Connected_Channel, (pfnGeneric_t)btampGetPackedTlvAMP_Assoc_Connected_Channel, "AMP_Assoc_Connected_Channel", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES, 0, 7,  7, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Capabilities), offsetof(tBtampTLVAMP_Assoc_PAL_Capabilities, present), SigPackSizeTlvAMP_Assoc_PAL_Capabilities, (pfnGeneric_t)btampGetPackedTlvAMP_Assoc_PAL_Capabilities, "AMP_Assoc_PAL_Capabilities", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_VERSION, 0, 8, 8, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Version), offsetof(tBtampTLVAMP_Assoc_PAL_Version, present), SigPackSizeTlvAMP_Assoc_PAL_Version, (pfnGeneric_t)btampGetPackedTlvAMP_Assoc_PAL_Version, "AMP_Assoc_PAL_Version", 1, },
    { 0xffff, 0 },
    };

    v_U32_t status = 0;
    *pnNeeded = 0;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampGetPackedAMP_ASSOCSize\n"); 
#endif    

    status |= GetPackedSizeTlvCore(pCtx,(v_U8_t*)pFrm,pnNeeded,TLVS);
    return status;
} /*                                  */

static v_U32_t GetPackedSizeTlvCore(void * pCtx,
                                 v_U8_t *pFrm,
                                 v_U32_t *pnNeeded,
                                 tTLVDefn  TLVs[])
{
    tTLVDefn      *pTlv;
    v_U32_t  status, status2;
    tFRAMES_BOOL *pfFound;

    status = BTAMP_PARSE_SUCCESS;
    status2 = BTAMP_PARSE_SUCCESS;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In GetPackedSizeTlvCore\n"); 
#endif    

    pTlv = &( TLVs[0] );
    while ( 0xffff != pTlv->id )
    {
        pfFound = (tFRAMES_BOOL*)(pFrm + pTlv->offset +
                                  pTlv->presenceOffset);
        if ( *pfFound )
        {
            *pnNeeded += 4U;
            if ( pTlv->pec ) *pnNeeded += 3U;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
            VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
              "In GetPackedSizeTlvCore, pTlv->sig - %d\n", pTlv->sig); 
#endif

            switch (pTlv->sig)
            {
                case SigPackSizeTlvAMP_Assoc_Connected_Channel:
                        status2 = ( (pfnPackSizeTlvAMP_Assoc_Connected_Channel_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_Connected_Channel* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvAMP_Assoc_MAC_Addr:
                        status2 = ( (pfnPackSizeTlvAMP_Assoc_MAC_Addr_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_MAC_Addr* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvAMP_Assoc_PAL_Capabilities:
                        status2 = ( (pfnPackSizeTlvAMP_Assoc_PAL_Capabilities_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_PAL_Capabilities* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvAMP_Assoc_PAL_Version:
                        status2 = ( (pfnPackSizeTlvAMP_Assoc_PAL_Version_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_PAL_Version* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvAMP_Assoc_Preferred_Channel_List:
                        status2 = ( (pfnPackSizeTlvAMP_Assoc_Preferred_Channel_List_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_Preferred_Channel_List* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvFlow_Spec:
                        status2 = ( (pfnPackSizeTlvFlow_Spec_t)(pTlv->pfn) )(pCtx, ( tBtampTLVFlow_Spec* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Accept_Logical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Accept_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Accept_Logical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Accept_Physical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Accept_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Accept_Physical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Channel_Selected_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Channel_Selected_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Channel_Selected_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Command_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Command_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Command_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Command_Status_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Command_Status_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Command_Status_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Create_Logical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Create_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Create_Logical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Create_Physical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Create_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Create_Physical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Data_Buffer_Overflow_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Data_Buffer_Overflow_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Data_Buffer_Overflow_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Disconnect_Logical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Disconnect_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Logical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Disconnect_Logical_Link_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Disconnect_Physical_Link_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Disconnect_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Physical_Link_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Disconnect_Physical_Link_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Flow_Spec_Modify_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Flow_Spec_Modify_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flow_Spec_Modify_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Flow_Spec_Modify_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Flow_Spec_Modify_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flow_Spec_Modify_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Flush_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Flush_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flush_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Flush_Occurred_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Flush_Occurred_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flush_Occurred_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Generic_AMP_Link_Key_Notification_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Hardware_Error_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Hardware_Error_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Hardware_Error_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Logical_Link_Cancel_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Logical_Link_Cancel_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Logical_Link_Cancel_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Logical_Link_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Logical_Link_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Loopback_Command_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Loopback_Command_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Loopback_Command_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Physical_Link_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Physical_Link_Loss_Warning_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Physical_Link_Loss_Warning_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Loss_Warning_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Physical_Link_Recovery_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Physical_Link_Recovery_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Recovery_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Qos_Violation_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Qos_Violation_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Qos_Violation_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Buffer_Size_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Buffer_Size_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Buffer_Size_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Data_Block_Size_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Data_Block_Size_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Data_Block_Size_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Flow_Control_Mode_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Link_Quality_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Link_Quality_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Link_Quality_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Local_AMP_Assoc_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Local_AMP_Information_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Local_AMP_Information_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_AMP_Information_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Local_Supported_Cmds_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Local_Version_Info_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Local_Version_Info_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_Version_Info_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Location_Data_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Location_Data_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_Loopback_Mode_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Loopback_Mode_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Read_RSSI_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Read_RSSI_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_RSSI_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Reset_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Reset_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Reset_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Reset_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Set_Event_Mask_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Set_Event_Mask_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Event_Mask_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Set_Event_Mask_Page_2_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Set_Short_Range_Mode_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Set_Short_Range_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Short_Range_Mode_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Short_Range_Mode_Change_Complete_Event:
                        status2 = ( (pfnPackSizeTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Flow_Control_Mode_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Location_Data_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Location_Data_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Loopback_Mode_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Loopback_Mode_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
                case SigPackSizeTlvHCI_Write_Remote_AMP_ASSOC_Cmd:
                        status2 = ( (pfnPackSizeTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd* )(pFrm + pTlv->offset), pnNeeded);
                        if (status2) status |= status2;
                    break;
            default:
                FRAMES_LOG1(pCtx, FRLOGE, FRFL("INTERNAL ERROR-- I don"
                    "'t know about the TLV signature %d; this is most l"
                    "ikely a bug in 'framesc'.\n"), pTlv->sig);
                return BTAMP_INTERNAL_ERROR;
            }
        }
        ++pTlv;
    }
    return status;
}
v_U32_t btampPackTlvAMP_Assoc_Connected_Channel(void * pCtx,
                                                tBtampTLVAMP_Assoc_Connected_Channel *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampPackTlvAMP_Assoc_Connected_Channel\n"); 
#endif    
    //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvAMP_Assoc_Connected_Channel(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3, 0);
        else *pBuf = 3;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->country, 3);
        *pnConsumed += 3;
        pBuf += 3;
        nBuf -= 3;
        if ( pSrc->num_triplets )        {
            BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->triplets ), ( pSrc->num_triplets * 3 ));
            *pnConsumed += ( pSrc->num_triplets * 3 );
            pBuf += ( ( pSrc->num_triplets * 3 ) );
            nBuf -= ( ( pSrc->num_triplets * 3 ) );
        }
        else break;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } 
    else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvAMP_Assoc_Connected_Channel_t)(void *, tBtampTLVAMP_Assoc_Connected_Channel *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvAMP_Assoc_Connected_Channel ( 0x007b )

v_U32_t btampPackTlvAMP_Assoc_MAC_Addr(void * pCtx,
                                       tBtampTLVAMP_Assoc_MAC_Addr *pSrc,
                                       v_U8_t *pBuf,
                                       v_U32_t nBuf,
                                       v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampPackTlvAMP_Assoc_MAC_Addr\n"); 
#endif    
    //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvAMP_Assoc_MAC_Addr(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1, 0);
        else *pBuf = 1;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->mac_addr, 6);
        *pnConsumed += 6;
        pBuf += 6;
        nBuf -= 6;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                     */

typedef v_U32_t (*pfnPackTlvAMP_Assoc_MAC_Addr_t)(void *, tBtampTLVAMP_Assoc_MAC_Addr *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvAMP_Assoc_MAC_Addr ( 0x007c )

v_U32_t btampPackTlvAMP_Assoc_PAL_Capabilities(void * pCtx,
                                               tBtampTLVAMP_Assoc_PAL_Capabilities *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampPackTlvAMP_Assoc_PAL_Capabilities\n"); 
#endif    
    //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvAMP_Assoc_PAL_Capabilities(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 4, 0);
        else *pBuf = 4;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtonl(pCtx, pBuf, pSrc->pal_capabilities, 0);
        *pnConsumed += 4;
        pBuf += 4;
        nBuf -= 4;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvAMP_Assoc_PAL_Capabilities_t)(void *, tBtampTLVAMP_Assoc_PAL_Capabilities *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvAMP_Assoc_PAL_Capabilities ( 0x007d )

v_U32_t btampPackTlvAMP_Assoc_PAL_Version(void * pCtx,
                                          tBtampTLVAMP_Assoc_PAL_Version *pSrc,
                                          v_U8_t *pBuf,
                                          v_U32_t nBuf,
                                          v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampPackTlvAMP_Assoc_PAL_Version\n"); 
#endif    
    //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvAMP_Assoc_PAL_Version(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5, 0);
        else *pBuf = 5;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->pal_version;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->pal_CompanyID, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->pal_subversion, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                        */

typedef v_U32_t (*pfnPackTlvAMP_Assoc_PAL_Version_t)(void *, tBtampTLVAMP_Assoc_PAL_Version *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvAMP_Assoc_PAL_Version ( 0x007e )

v_U32_t btampPackTlvAMP_Assoc_Preferred_Channel_List(void * pCtx,
                                                     tBtampTLVAMP_Assoc_Preferred_Channel_List *pSrc,
                                                     v_U8_t *pBuf,
                                                     v_U32_t nBuf,
                                                     v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 2;
#ifdef WLAN_BAPHCI_ENABLE_LOGGING
    VOS_TRACE(VOS_MODULE_ID_BAP,VOS_TRACE_LEVEL_ERROR,
      "In btampPackTlvAMP_Assoc_Preferred_Channel_List\n"); 
#endif    
    //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvAMP_Assoc_Preferred_Channel_List(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 2, 0);
        else *pBuf = 2;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->country, 3);
        *pnConsumed += 3;
        pBuf += 3;
        nBuf -= 3;
        if ( pSrc->num_triplets )        {
            BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->triplets ), ( pSrc->num_triplets * 3 ));
            *pnConsumed += ( pSrc->num_triplets * 3 );
            pBuf += ( ( pSrc->num_triplets * 3 ) );
            nBuf -= ( ( pSrc->num_triplets * 3 ) );
        }
        else break;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackTlvAMP_Assoc_Preferred_Channel_List_t)(void *, tBtampTLVAMP_Assoc_Preferred_Channel_List *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvAMP_Assoc_Preferred_Channel_List ( 0x007f )

v_U32_t btampPackTlvFlow_Spec(void * pCtx,
                              tBtampTLVFlow_Spec *pSrc,
                              v_U8_t *pBuf,
                              v_U32_t nBuf,
                              v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvFlow_Spec(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 6, 0);
        else *pBuf = 6;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->flow_spec_id;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->service_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->max_sdu, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtonl(pCtx, pBuf, pSrc->sdu_inter_arrival, 0);
        *pnConsumed += 4;
        pBuf += 4;
        nBuf -= 4;
        frameshtonl(pCtx, pBuf, pSrc->access_latency, 0);
        *pnConsumed += 4;
        pBuf += 4;
        nBuf -= 4;
        frameshtonl(pCtx, pBuf, pSrc->flush_timeout, 0);
        *pnConsumed += 4;
        pBuf += 4;
        nBuf -= 4;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen) 
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                            */

typedef v_U32_t (*pfnPackTlvFlow_Spec_t)(void *, tBtampTLVFlow_Spec *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvFlow_Spec ( 0x0080 )

v_U32_t btampPackTlvHCI_Accept_Logical_Link_Cmd(void * pCtx,
                                                tBtampTLVHCI_Accept_Logical_Link_Cmd *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Accept_Logical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1081, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->tx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->rx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvHCI_Accept_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Accept_Logical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Accept_Logical_Link_Cmd ( 0x0081 )

v_U32_t btampPackTlvHCI_Accept_Physical_Link_Cmd(void * pCtx,
                                                 tBtampTLVHCI_Accept_Physical_Link_Cmd *pSrc,
                                                 v_U8_t *pBuf,
                                                 v_U32_t nBuf,
                                                 v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Accept_Physical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1078, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->key_length;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->key_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->key_material ), pSrc->key_length);
        *pnConsumed += pSrc->key_length;
        pBuf += ( pSrc->key_length );
        nBuf -= ( pSrc->key_length );
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackTlvHCI_Accept_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Accept_Physical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Accept_Physical_Link_Cmd ( 0x0082 )

v_U32_t btampPackTlvHCI_Channel_Selected_Event(void * pCtx,
                                               tBtampTLVHCI_Channel_Selected_Event *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Channel_Selected_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 65, 0);
        else *pBuf = 65;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvHCI_Channel_Selected_Event_t)(void *, tBtampTLVHCI_Channel_Selected_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Channel_Selected_Event ( 0x0083 )

v_U32_t btampPackTlvHCI_Command_Complete_Event(void * pCtx,
                                               tBtampTLVHCI_Command_Complete_Event *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Command_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 14, 0);
        else *pBuf = 14;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->num_hci_command_packets;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->command_opcode, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        switch (pSrc->command_opcode)
        {
            case 3075:
                *pBuf = pSrc->cc_event.Reset.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3080:
                *pBuf = pSrc->cc_event.Flush.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Flush.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 1083:
                *pBuf = pSrc->cc_event.Logical_Link_Cancel.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Logical_Link_Cancel.phy_link_handle;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Logical_Link_Cancel.tx_flow_spec_id;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3077:
                *pBuf = pSrc->cc_event.Set_Event_Mask.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3093:
                *pBuf = pSrc->cc_event.Read_Connection_Accept_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Connection_Accept_TO.connection_accept_timeout, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 3094:
                *pBuf = pSrc->cc_event.Write_Connection_Accept_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3126:
                *pBuf = pSrc->cc_event.Read_Link_Supervision_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Link_Supervision_TO.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Link_Supervision_TO.link_supervision_timeout, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 3127:
                *pBuf = pSrc->cc_event.Write_Link_Supervision_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Write_Link_Supervision_TO.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 3169:
                *pBuf = pSrc->cc_event.Read_Logical_Link_Accept_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Logical_Link_Accept_TO.logical_link_accept_timeout, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 3170:
                *pBuf = pSrc->cc_event.Write_Logical_Link_Accept_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3171:
                *pBuf = pSrc->cc_event.Set_Event_Mask_Page_2.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3172:
                *pBuf = pSrc->cc_event.Read_Location_Data.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Location_Data.loc_domain_aware;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                BTAMP_MEMCPY(pCtx, pBuf, pSrc->cc_event.Read_Location_Data.loc_domain, 3);
                *pnConsumed += 3;
                pBuf += 3;
                nBuf -= 3;
                *pBuf = pSrc->cc_event.Read_Location_Data.loc_options;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3173:
                *pBuf = pSrc->cc_event.Write_Location_Data.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3174:
                *pBuf = pSrc->cc_event.Read_Flow_Control_Mode.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Flow_Control_Mode.flow_control_mode;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3175:
                *pBuf = pSrc->cc_event.Write_Flow_Control_Mode.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3177:
                *pBuf = pSrc->cc_event.Read_BE_Flush_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_BE_Flush_TO.best_effort_flush_timeout, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
            break;
            case 3178:
                *pBuf = pSrc->cc_event.Write_BE_Flush_TO.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 3179:
                *pBuf = pSrc->cc_event.Set_Short_Range_Mode.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 4097:
                *pBuf = pSrc->cc_event.Read_Local_Version_Info.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Local_Version_Info.HC_HCI_Version;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Local_Version_Info.HC_HCI_Revision, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                *pBuf = pSrc->cc_event.Read_Local_Version_Info.HC_PAL_Version;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Local_Version_Info.HC_Manufac_Name, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Local_Version_Info.HC_PAL_Sub_Version, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 4098:
                *pBuf = pSrc->cc_event.Read_Local_Supported_Cmds.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                BTAMP_MEMCPY(pCtx, pBuf, pSrc->cc_event.Read_Local_Supported_Cmds.HC_Support_Cmds, 64);
                *pnConsumed += 64;
                pBuf += 64;
                nBuf -= 64;
            break;
            case 4101:
                *pBuf = pSrc->cc_event.Read_Buffer_Size.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Buffer_Size.HC_ACL_Data_Packet_Length, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                *pBuf = pSrc->cc_event.Read_Buffer_Size.HC_SCO_Packet_Length;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Buffer_Size.HC_Total_Num_ACL_Packets, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Buffer_Size.HC_Total_Num_SCO_Packets, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 4106:
                *pBuf = pSrc->cc_event.Read_Data_Block_Size.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Data_Block_Size.HC_Max_ACL_Data_Packet_Length, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Data_Block_Size.HC_Data_Block_Length, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Data_Block_Size.HC_Total_Num_Data_Blocks, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 5121:
                *pBuf = pSrc->cc_event.Read_Failed_Contact_Counter.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Failed_Contact_Counter.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Failed_Contact_Counter.failed_contact_counter, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 5122:
                *pBuf = pSrc->cc_event.Reset_Failed_Contact_Counter.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Reset_Failed_Contact_Counter.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
            break;
            case 5123:
                *pBuf = pSrc->cc_event.Read_Link_Quality.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Link_Quality.log_link_handle, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                *pBuf = pSrc->cc_event.Read_Link_Quality.link_quality;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 5125:
                *pBuf = pSrc->cc_event.Read_RSSI.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_RSSI.phy_link_handle;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_RSSI.rssi;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 5129:
                *pBuf = pSrc->cc_event.Read_Local_AMP_Info.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Local_AMP_Info.HC_AMP_Status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_Total_BW, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_Max_Guaranteed_BW, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_Min_Latency, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_Max_PDU_Size, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
                *pBuf = pSrc->cc_event.Read_Local_AMP_Info.HC_Controller_Type;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_PAL_Capabilities, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_AMP_Assoc_Length, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_Max_Flush_Timeout, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
                frameshtonl(pCtx, pBuf, pSrc->cc_event.Read_Local_AMP_Info.HC_BE_Flush_Timeout, 0);
                *pnConsumed += 4;
                pBuf += 4;
                nBuf -= 4;
            break;
            case 5130:
                *pBuf = pSrc->cc_event.Read_Read_Local_AMP_Assoc.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Read_Local_AMP_Assoc.phy_link_handle;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                frameshtons(pCtx, pBuf, pSrc->cc_event.Read_Read_Local_AMP_Assoc.remaining_length, 0);
                *pnConsumed += 2;
                pBuf += 2;
                nBuf -= 2;
                BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->cc_event.Read_Read_Local_AMP_Assoc.AMP_assoc_fragment ), pSrc->cc_event.Read_Read_Local_AMP_Assoc.remaining_length);
                *pnConsumed += pSrc->cc_event.Read_Read_Local_AMP_Assoc.remaining_length;
                pBuf += ( pSrc->cc_event.Read_Read_Local_AMP_Assoc.remaining_length );
                nBuf -= ( pSrc->cc_event.Read_Read_Local_AMP_Assoc.remaining_length );
            break;
            case 5131:
                *pBuf = pSrc->cc_event.Write_Remote_AMP_Assoc.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Write_Remote_AMP_Assoc.phy_link_handle;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 6145:
                *pBuf = pSrc->cc_event.Read_Loopback_Mode.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
                *pBuf = pSrc->cc_event.Read_Loopback_Mode.loopback_mode;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
            case 6146:
                *pBuf = pSrc->cc_event.Write_Loopback_Mode.status;
                *pnConsumed += 1;
                pBuf += 1;
                nBuf -= 1;
            break;
        }
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvHCI_Command_Complete_Event_t)(void *, tBtampTLVHCI_Command_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Command_Complete_Event ( 0x0084 )

v_U32_t btampPackTlvHCI_Command_Status_Event(void * pCtx,
                                             tBtampTLVHCI_Command_Status_Event *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Command_Status_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 15, 0);
        else *pBuf = 15;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->num_hci_command_packets;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->command_opcode, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                           */

typedef v_U32_t (*pfnPackTlvHCI_Command_Status_Event_t)(void *, tBtampTLVHCI_Command_Status_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Command_Status_Event ( 0x0085 )

v_U32_t btampPackTlvHCI_Create_Logical_Link_Cmd(void * pCtx,
                                                tBtampTLVHCI_Create_Logical_Link_Cmd *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }

    nConsumedOnEntry = *pnConsumed;
    status = btampGetPackedTlvHCI_Create_Logical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1080, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->tx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->rx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvHCI_Create_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Create_Logical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Create_Logical_Link_Cmd ( 0x0086 )

v_U32_t btampPackTlvHCI_Create_Physical_Link_Cmd(void * pCtx,
                                                 tBtampTLVHCI_Create_Physical_Link_Cmd *pSrc,
                                                 v_U8_t *pBuf,
                                                 v_U32_t nBuf,
                                                 v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Create_Physical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1077, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->key_length;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->key_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->key_material ), pSrc->key_length);
        *pnConsumed += pSrc->key_length;
        pBuf += ( pSrc->key_length );
        nBuf -= ( pSrc->key_length );
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackTlvHCI_Create_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Create_Physical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Create_Physical_Link_Cmd ( 0x0087 )

v_U32_t btampPackTlvHCI_Data_Buffer_Overflow_Event(void * pCtx,
                                                   tBtampTLVHCI_Data_Buffer_Overflow_Event *pSrc,
                                                   v_U8_t *pBuf,
                                                   v_U32_t nBuf,
                                                   v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Data_Buffer_Overflow_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 26, 0);
        else *pBuf = 26;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->link_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                 */

typedef v_U32_t (*pfnPackTlvHCI_Data_Buffer_Overflow_Event_t)(void *, tBtampTLVHCI_Data_Buffer_Overflow_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Data_Buffer_Overflow_Event ( 0x0088 )

v_U32_t btampPackTlvHCI_Disconnect_Logical_Link_Cmd(void * pCtx,
                                                    tBtampTLVHCI_Disconnect_Logical_Link_Cmd *pSrc,
                                                    v_U8_t *pBuf,
                                                    v_U32_t nBuf,
                                                    v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Disconnect_Logical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1082, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackTlvHCI_Disconnect_Logical_Link_Cmd_t)(void *, tBtampTLVHCI_Disconnect_Logical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Disconnect_Logical_Link_Cmd ( 0x0089 )

v_U32_t btampPackTlvHCI_Disconnect_Logical_Link_Complete_Event(void * pCtx,
                                                               tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event *pSrc,
                                                               v_U8_t *pBuf,
                                                               v_U32_t nBuf,
                                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Disconnect_Logical_Link_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 70, 0);
        else *pBuf = 70;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        *pBuf = pSrc->reason;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                             */

typedef v_U32_t (*pfnPackTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Disconnect_Logical_Link_Complete_Event ( 0x008a )

v_U32_t btampPackTlvHCI_Disconnect_Physical_Link_Cmd(void * pCtx,
                                                     tBtampTLVHCI_Disconnect_Physical_Link_Cmd *pSrc,
                                                     v_U8_t *pBuf,
                                                     v_U32_t nBuf,
                                                     v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Disconnect_Physical_Link_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1079, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->reason;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackTlvHCI_Disconnect_Physical_Link_Cmd_t)(void *, tBtampTLVHCI_Disconnect_Physical_Link_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Disconnect_Physical_Link_Cmd ( 0x008b )

v_U32_t btampPackTlvHCI_Disconnect_Physical_Link_Complete_Event(void * pCtx,
                                                                tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event *pSrc,
                                                                v_U8_t *pBuf,
                                                                v_U32_t nBuf,
                                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Disconnect_Physical_Link_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 66, 0);
        else *pBuf = 66;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->reason;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                              */

typedef v_U32_t (*pfnPackTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Disconnect_Physical_Link_Complete_Event ( 0x008c )

v_U32_t btampPackTlvHCI_Flow_Spec_Modify_Cmd(void * pCtx,
                                             tBtampTLVHCI_Flow_Spec_Modify_Cmd *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Flow_Spec_Modify_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1084, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        *pBuf = pSrc->be_aggr_counter;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->tx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->rx_flow_spec, 18);
        *pnConsumed += 18;
        pBuf += 18;
        nBuf -= 18;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                           */

typedef v_U32_t (*pfnPackTlvHCI_Flow_Spec_Modify_Cmd_t)(void *, tBtampTLVHCI_Flow_Spec_Modify_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Flow_Spec_Modify_Cmd ( 0x008d )

v_U32_t btampPackTlvHCI_Flow_Spec_Modify_Complete_Event(void * pCtx,
                                                        tBtampTLVHCI_Flow_Spec_Modify_Complete_Event *pSrc,
                                                        v_U8_t *pBuf,
                                                        v_U32_t nBuf,
                                                        v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Flow_Spec_Modify_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 71, 0);
        else *pBuf = 71;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                      */

typedef v_U32_t (*pfnPackTlvHCI_Flow_Spec_Modify_Complete_Event_t)(void *, tBtampTLVHCI_Flow_Spec_Modify_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Flow_Spec_Modify_Complete_Event ( 0x008e )

v_U32_t btampPackTlvHCI_Flush_Cmd(void * pCtx,
                                  tBtampTLVHCI_Flush_Cmd *pSrc,
                                  v_U8_t *pBuf,
                                  v_U32_t nBuf,
                                  v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Flush_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3080, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                */

typedef v_U32_t (*pfnPackTlvHCI_Flush_Cmd_t)(void *, tBtampTLVHCI_Flush_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Flush_Cmd ( 0x008f )

v_U32_t btampPackTlvHCI_Flush_Occurred_Event(void * pCtx,
                                             tBtampTLVHCI_Flush_Occurred_Event *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Flush_Occurred_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 17, 0);
        else *pBuf = 17;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                           */

typedef v_U32_t (*pfnPackTlvHCI_Flush_Occurred_Event_t)(void *, tBtampTLVHCI_Flush_Occurred_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Flush_Occurred_Event ( 0x0090 )

v_U32_t btampPackTlvHCI_Num_Completed_Pkts_Event(void * pCtx,
                                             tBtampTLVHCI_Num_Completed_Pkts_Event *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Num_Completed_Pkts_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
//                           
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 19, 0);
        else *pBuf = 19;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->num_handles;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->conn_handles[0], 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->num_completed_pkts[0], 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
#if 0
        //    
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
//           
#endif
//              
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

v_U32_t btampPackTlvHCI_Num_Completed_Data_Blocks_Event(void * pCtx,
                                             tBtampTLVHCI_Num_Completed_Data_Blocks_Event *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Num_Completed_Data_Blocks_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
//                           
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 72, 0);
        else *pBuf = 72;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->total_num_data_blocks, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        *pBuf = pSrc->num_handles;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->conn_handles[0], 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->num_completed_pkts[0], 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->num_completed_blocks[0], 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
#if 0
        //    
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, 0, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
//           
#endif
//              
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                      */

//                                                                                                                                         
//                                                         

v_U32_t btampPackTlvHCI_Generic_AMP_Link_Key_Notification_Event(void * pCtx,
                                                                tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event *pSrc,
                                                                v_U8_t *pBuf,
                                                                v_U32_t nBuf,
                                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Generic_AMP_Link_Key_Notification_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 62, 0);
        else *pBuf = 62;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->bd_addr, 6);
        *pnConsumed += 6;
        pBuf += 6;
        nBuf -= 6;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->generic_amp_link_key, 32);
        *pnConsumed += 32;
        pBuf += 32;
        nBuf -= 32;
        *pBuf = pSrc->key_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                              */

typedef v_U32_t (*pfnPackTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(void *, tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Generic_AMP_Link_Key_Notification_Event ( 0x0091 )

v_U32_t btampPackTlvHCI_Hardware_Error_Event(void * pCtx,
                                             tBtampTLVHCI_Hardware_Error_Event *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Hardware_Error_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 16, 0);
        else *pBuf = 16;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->hardware_code;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                           */

typedef v_U32_t (*pfnPackTlvHCI_Hardware_Error_Event_t)(void *, tBtampTLVHCI_Hardware_Error_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Hardware_Error_Event ( 0x0092 )

v_U32_t btampPackTlvHCI_Logical_Link_Cancel_Cmd(void * pCtx,
                                                tBtampTLVHCI_Logical_Link_Cancel_Cmd *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Logical_Link_Cancel_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 1083, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->tx_flow_spec_id;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvHCI_Logical_Link_Cancel_Cmd_t)(void *, tBtampTLVHCI_Logical_Link_Cancel_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Logical_Link_Cancel_Cmd ( 0x0093 )

v_U32_t btampPackTlvHCI_Logical_Link_Complete_Event(void * pCtx,
                                                    tBtampTLVHCI_Logical_Link_Complete_Event *pSrc,
                                                    v_U8_t *pBuf,
                                                    v_U32_t nBuf,
                                                    v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Logical_Link_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 69, 0);
        else *pBuf = 69;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->flow_spec_id;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackTlvHCI_Logical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Logical_Link_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Logical_Link_Complete_Event ( 0x0094 )

v_U32_t btampPackTlvHCI_Loopback_Command_Event(void * pCtx,
                                               tBtampTLVHCI_Loopback_Command_Event *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Loopback_Command_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 25, 0);
        else *pBuf = 25;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->hci_command_packet, 64);
        *pnConsumed += 64;
        pBuf += 64;
        nBuf -= 64;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvHCI_Loopback_Command_Event_t)(void *, tBtampTLVHCI_Loopback_Command_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Loopback_Command_Event ( 0x0095 )

v_U32_t btampPackTlvHCI_Physical_Link_Complete_Event(void * pCtx,
                                                     tBtampTLVHCI_Physical_Link_Complete_Event *pSrc,
                                                     v_U8_t *pBuf,
                                                     v_U32_t nBuf,
                                                     v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Physical_Link_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 64, 0);
        else *pBuf = 64;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackTlvHCI_Physical_Link_Complete_Event_t)(void *, tBtampTLVHCI_Physical_Link_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Physical_Link_Complete_Event ( 0x0096 )

v_U32_t btampPackTlvHCI_Physical_Link_Loss_Warning_Event(void * pCtx,
                                                         tBtampTLVHCI_Physical_Link_Loss_Warning_Event *pSrc,
                                                         v_U8_t *pBuf,
                                                         v_U32_t nBuf,
                                                         v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Physical_Link_Loss_Warning_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 67, 0);
        else *pBuf = 67;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->reason;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackTlvHCI_Physical_Link_Loss_Warning_Event_t)(void *, tBtampTLVHCI_Physical_Link_Loss_Warning_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Physical_Link_Loss_Warning_Event ( 0x0097 )

v_U32_t btampPackTlvHCI_Physical_Link_Recovery_Event(void * pCtx,
                                                     tBtampTLVHCI_Physical_Link_Recovery_Event *pSrc,
                                                     v_U8_t *pBuf,
                                                     v_U32_t nBuf,
                                                     v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Physical_Link_Recovery_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 68, 0);
        else *pBuf = 68;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                   */

typedef v_U32_t (*pfnPackTlvHCI_Physical_Link_Recovery_Event_t)(void *, tBtampTLVHCI_Physical_Link_Recovery_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Physical_Link_Recovery_Event ( 0x0098 )

v_U32_t btampPackTlvHCI_Qos_Violation_Event(void * pCtx,
                                            tBtampTLVHCI_Qos_Violation_Event *pSrc,
                                            v_U8_t *pBuf,
                                            v_U32_t nBuf,
                                            v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Qos_Violation_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 30, 0);
        else *pBuf = 30;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                          */

typedef v_U32_t (*pfnPackTlvHCI_Qos_Violation_Event_t)(void *, tBtampTLVHCI_Qos_Violation_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Qos_Violation_Event ( 0x0099 )

v_U32_t btampPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(void * pCtx,
                                                           tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd *pSrc,
                                                           v_U8_t *pBuf,
                                                           v_U32_t nBuf,
                                                           v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3177, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                         */

typedef v_U32_t (*pfnPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd ( 0x009a )

v_U32_t btampPackTlvHCI_Read_Buffer_Size_Cmd(void * pCtx,
                                             tBtampTLVHCI_Read_Buffer_Size_Cmd *pSrc,
                                             v_U8_t *pBuf,
                                             v_U32_t nBuf,
                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Buffer_Size_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 4101, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                           */

typedef v_U32_t (*pfnPackTlvHCI_Read_Buffer_Size_Cmd_t)(void *, tBtampTLVHCI_Read_Buffer_Size_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Buffer_Size_Cmd ( 0x009b )

v_U32_t btampPackTlvHCI_Read_Connection_Accept_Timeout_Cmd(void * pCtx,
                                                           tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd *pSrc,
                                                           v_U8_t *pBuf,
                                                           v_U32_t nBuf,
                                                           v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Connection_Accept_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3093, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                         */

typedef v_U32_t (*pfnPackTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Connection_Accept_Timeout_Cmd ( 0x009c )

v_U32_t btampPackTlvHCI_Read_Data_Block_Size_Cmd(void * pCtx,
                                                 tBtampTLVHCI_Read_Data_Block_Size_Cmd *pSrc,
                                                 v_U8_t *pBuf,
                                                 v_U32_t nBuf,
                                                 v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Data_Block_Size_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 4106, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackTlvHCI_Read_Data_Block_Size_Cmd_t)(void *, tBtampTLVHCI_Read_Data_Block_Size_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Data_Block_Size_Cmd ( 0x009d )

v_U32_t btampPackTlvHCI_Read_Failed_Contact_Counter_Cmd(void * pCtx,
                                                        tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd *pSrc,
                                                        v_U8_t *pBuf,
                                                        v_U32_t nBuf,
                                                        v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Failed_Contact_Counter_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5121, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                      */

typedef v_U32_t (*pfnPackTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(void *, tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Failed_Contact_Counter_Cmd ( 0x009e )

v_U32_t btampPackTlvHCI_Read_Flow_Control_Mode_Cmd(void * pCtx,
                                                   tBtampTLVHCI_Read_Flow_Control_Mode_Cmd *pSrc,
                                                   v_U8_t *pBuf,
                                                   v_U32_t nBuf,
                                                   v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Flow_Control_Mode_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3174, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }
    
    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                 */

typedef v_U32_t (*pfnPackTlvHCI_Read_Flow_Control_Mode_Cmd_t)(void *, tBtampTLVHCI_Read_Flow_Control_Mode_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Flow_Control_Mode_Cmd ( 0x009f )

v_U32_t btampPackTlvHCI_Read_Link_Quality_Cmd(void * pCtx,
                                              tBtampTLVHCI_Read_Link_Quality_Cmd *pSrc,
                                              v_U8_t *pBuf,
                                              v_U32_t nBuf,
                                              v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Link_Quality_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5123, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }
    
    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                            */

typedef v_U32_t (*pfnPackTlvHCI_Read_Link_Quality_Cmd_t)(void *, tBtampTLVHCI_Read_Link_Quality_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Link_Quality_Cmd ( 0x00a0 )

v_U32_t btampPackTlvHCI_Read_Link_Supervision_Timeout_Cmd(void * pCtx,
                                                          tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd *pSrc,
                                                          v_U8_t *pBuf,
                                                          v_U32_t nBuf,
                                                          v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Link_Supervision_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3126, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                        */

typedef v_U32_t (*pfnPackTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Link_Supervision_Timeout_Cmd ( 0x00a1 )

v_U32_t btampPackTlvHCI_Read_Local_AMP_Assoc_Cmd(void * pCtx,
                                                 tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd *pSrc,
                                                 v_U8_t *pBuf,
                                                 v_U32_t nBuf,
                                                 v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Local_AMP_Assoc_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5130, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->length_so_far, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->max_remote_amp_assoc_length, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(void *, tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Local_AMP_Assoc_Cmd ( 0x00a2 )

v_U32_t btampPackTlvHCI_Read_Local_AMP_Information_Cmd(void * pCtx,
                                                       tBtampTLVHCI_Read_Local_AMP_Information_Cmd *pSrc,
                                                       v_U8_t *pBuf,
                                                       v_U32_t nBuf,
                                                       v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Local_AMP_Information_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5129, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                     */

typedef v_U32_t (*pfnPackTlvHCI_Read_Local_AMP_Information_Cmd_t)(void *, tBtampTLVHCI_Read_Local_AMP_Information_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Local_AMP_Information_Cmd ( 0x00a3 )

v_U32_t btampPackTlvHCI_Read_Local_Supported_Cmds_Cmd(void * pCtx,
                                                      tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd *pSrc,
                                                      v_U8_t *pBuf,
                                                      v_U32_t nBuf,
                                                      v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Local_Supported_Cmds_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 4098, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(void *, tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Local_Supported_Cmds_Cmd ( 0x00a4 )

v_U32_t btampPackTlvHCI_Read_Local_Version_Info_Cmd(void * pCtx,
                                                    tBtampTLVHCI_Read_Local_Version_Info_Cmd *pSrc,
                                                    v_U8_t *pBuf,
                                                    v_U32_t nBuf,
                                                    v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Local_Version_Info_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 4097, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen) 
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackTlvHCI_Read_Local_Version_Info_Cmd_t)(void *, tBtampTLVHCI_Read_Local_Version_Info_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Local_Version_Info_Cmd ( 0x00a5 )

v_U32_t btampPackTlvHCI_Read_Location_Data_Cmd(void * pCtx,
                                               tBtampTLVHCI_Read_Location_Data_Cmd *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Location_Data_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3172, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvHCI_Read_Location_Data_Cmd_t)(void *, tBtampTLVHCI_Read_Location_Data_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Location_Data_Cmd ( 0x00a6 )

v_U32_t btampPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(void * pCtx,
                                                             tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd *pSrc,
                                                             v_U8_t *pBuf,
                                                             v_U32_t nBuf,
                                                             v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3169, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                           */

typedef v_U32_t (*pfnPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd ( 0x00a7 )

v_U32_t btampPackTlvHCI_Read_Loopback_Mode_Cmd(void * pCtx,
                                               tBtampTLVHCI_Read_Loopback_Mode_Cmd *pSrc,
                                               v_U8_t *pBuf,
                                               v_U32_t nBuf,
                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_Loopback_Mode_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 6145, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                             */

typedef v_U32_t (*pfnPackTlvHCI_Read_Loopback_Mode_Cmd_t)(void *, tBtampTLVHCI_Read_Loopback_Mode_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_Loopback_Mode_Cmd ( 0x00a8 )

v_U32_t btampPackTlvHCI_Read_RSSI_Cmd(void * pCtx,
                                      tBtampTLVHCI_Read_RSSI_Cmd *pSrc,
                                      v_U8_t *pBuf,
                                      v_U32_t nBuf,
                                      v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Read_RSSI_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5125, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                    */

typedef v_U32_t (*pfnPackTlvHCI_Read_RSSI_Cmd_t)(void *, tBtampTLVHCI_Read_RSSI_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Read_RSSI_Cmd ( 0x00a9 )

v_U32_t btampPackTlvHCI_Reset_Cmd(void * pCtx,
                                  tBtampTLVHCI_Reset_Cmd *pSrc,
                                  v_U8_t *pBuf,
                                  v_U32_t nBuf,
                                  v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Reset_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3075, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                */

typedef v_U32_t (*pfnPackTlvHCI_Reset_Cmd_t)(void *, tBtampTLVHCI_Reset_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Reset_Cmd ( 0x00aa )

v_U32_t btampPackTlvHCI_Reset_Failed_Contact_Counter_Cmd(void * pCtx,
                                                         tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd *pSrc,
                                                         v_U8_t *pBuf,
                                                         v_U32_t nBuf,
                                                         v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Reset_Failed_Contact_Counter_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5122, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                       */

typedef v_U32_t (*pfnPackTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(void *, tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Reset_Failed_Contact_Counter_Cmd ( 0x00ab )

v_U32_t btampPackTlvHCI_Set_Event_Mask_Cmd(void * pCtx,
                                           tBtampTLVHCI_Set_Event_Mask_Cmd *pSrc,
                                           v_U8_t *pBuf,
                                           v_U32_t nBuf,
                                           v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Set_Event_Mask_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3077, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->event_mask, 8);
        *pnConsumed += 8;
        pBuf += 8;
        nBuf -= 8;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                         */

typedef v_U32_t (*pfnPackTlvHCI_Set_Event_Mask_Cmd_t)(void *, tBtampTLVHCI_Set_Event_Mask_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Set_Event_Mask_Cmd ( 0x00ac )

v_U32_t btampPackTlvHCI_Set_Event_Mask_Page_2_Cmd(void * pCtx,
                                                  tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd *pSrc,
                                                  v_U8_t *pBuf,
                                                  v_U32_t nBuf,
                                                  v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Set_Event_Mask_Page_2_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3171, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->event_mask_page_2, 8);
        *pnConsumed += 8;
        pBuf += 8;
        nBuf -= 8;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                */

typedef v_U32_t (*pfnPackTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(void *, tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Set_Event_Mask_Page_2_Cmd ( 0x00ad )

v_U32_t btampPackTlvHCI_Set_Short_Range_Mode_Cmd(void * pCtx,
                                                 tBtampTLVHCI_Set_Short_Range_Mode_Cmd *pSrc,
                                                 v_U8_t *pBuf,
                                                 v_U32_t nBuf,
                                                 v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Set_Short_Range_Mode_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3179, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->short_range_mode;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                               */

typedef v_U32_t (*pfnPackTlvHCI_Set_Short_Range_Mode_Cmd_t)(void *, tBtampTLVHCI_Set_Short_Range_Mode_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Set_Short_Range_Mode_Cmd ( 0x00ae )

v_U32_t btampPackTlvHCI_Short_Range_Mode_Change_Complete_Event(void * pCtx,
                                                               tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event *pSrc,
                                                               v_U8_t *pBuf,
                                                               v_U32_t nBuf,
                                                               v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Short_Range_Mode_Change_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 76, 0);
        else *pBuf = 76;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->status;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        *pBuf = pSrc->short_range_mode;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                             */

typedef v_U32_t (*pfnPackTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(void *, tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Short_Range_Mode_Change_Complete_Event ( 0x00af )

v_U32_t btampPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(void * pCtx,
                                                            tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd *pSrc,
                                                            v_U8_t *pBuf,
                                                            v_U32_t nBuf,
                                                            v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3178, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtonl(pCtx, pBuf, pSrc->best_effort_flush_timeout, 0);
        *pnConsumed += 4;
        pBuf += 4;
        nBuf -= 4;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                          */

typedef v_U32_t (*pfnPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd ( 0x00b0 )

v_U32_t btampPackTlvHCI_Write_Connection_Accept_Timeout_Cmd(void * pCtx,
                                                            tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd *pSrc,
                                                            v_U8_t *pBuf,
                                                            v_U32_t nBuf,
                                                            v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Connection_Accept_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3094, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->connection_accept_timeout, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                          */

typedef v_U32_t (*pfnPackTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Connection_Accept_Timeout_Cmd ( 0x00b1 )

v_U32_t btampPackTlvHCI_Write_Flow_Control_Mode_Cmd(void * pCtx,
                                                    tBtampTLVHCI_Write_Flow_Control_Mode_Cmd *pSrc,
                                                    v_U8_t *pBuf,
                                                    v_U32_t nBuf,
                                                    v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Flow_Control_Mode_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3175, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->flow_control_mode;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                  */

typedef v_U32_t (*pfnPackTlvHCI_Write_Flow_Control_Mode_Cmd_t)(void *, tBtampTLVHCI_Write_Flow_Control_Mode_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Flow_Control_Mode_Cmd ( 0x00b2 )

v_U32_t btampPackTlvHCI_Write_Link_Supervision_Timeout_Cmd(void * pCtx,
                                                           tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd *pSrc,
                                                           v_U8_t *pBuf,
                                                           v_U32_t nBuf,
                                                           v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Link_Supervision_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3127, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->link_supervision_timeout, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                         */

typedef v_U32_t (*pfnPackTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Link_Supervision_Timeout_Cmd ( 0x00b3 )

v_U32_t btampPackTlvHCI_Write_Location_Data_Cmd(void * pCtx,
                                                tBtampTLVHCI_Write_Location_Data_Cmd *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Location_Data_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3173, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->loc_domain_aware;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        BTAMP_MEMCPY(pCtx, pBuf, pSrc->loc_domain, 3);
        *pnConsumed += 3;
        pBuf += 3;
        nBuf -= 3;
        *pBuf = pSrc->loc_options;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvHCI_Write_Location_Data_Cmd_t)(void *, tBtampTLVHCI_Write_Location_Data_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Location_Data_Cmd ( 0x00b4 )

v_U32_t btampPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(void * pCtx,
                                                              tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd *pSrc,
                                                              v_U8_t *pBuf,
                                                              v_U32_t nBuf,
                                                              v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3170, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->logical_link_accept_timeout, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                            */

typedef v_U32_t (*pfnPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(void *, tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd ( 0x00b5 )

v_U32_t btampPackTlvHCI_Write_Loopback_Mode_Cmd(void * pCtx,
                                                tBtampTLVHCI_Write_Loopback_Mode_Cmd *pSrc,
                                                v_U8_t *pBuf,
                                                v_U32_t nBuf,
                                                v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Loopback_Mode_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 6146, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->loopback_mode;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                              */

typedef v_U32_t (*pfnPackTlvHCI_Write_Loopback_Mode_Cmd_t)(void *, tBtampTLVHCI_Write_Loopback_Mode_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Loopback_Mode_Cmd ( 0x00b6 )

v_U32_t btampPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd(void * pCtx,
                                                   tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd *pSrc,
                                                   v_U8_t *pBuf,
                                                   v_U32_t nBuf,
                                                   v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Write_Remote_AMP_ASSOC_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 5131, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        *pBuf = pSrc->phy_link_handle;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        frameshtons(pCtx, pBuf, pSrc->length_so_far, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        frameshtons(pCtx, pBuf, pSrc->amp_assoc_remaining_length, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        BTAMP_MEMCPY(pCtx, pBuf, &( pSrc->amp_assoc_fragment ), pSrc->amp_assoc_remaining_length);
        *pnConsumed += pSrc->amp_assoc_remaining_length;
        pBuf += ( pSrc->amp_assoc_remaining_length );
        nBuf -= ( pSrc->amp_assoc_remaining_length );
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                 */

typedef v_U32_t (*pfnPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(void *, tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd ( 0x00b7 )

v_U32_t btampPackTlvHCI_Enhanced_Flush_Cmd(void * pCtx,
                                           tBtampTLVHCI_Enhanced_Flush_Cmd *pSrc,
                                           v_U8_t *pBuf,
                                           v_U32_t nBuf,
                                           v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 2;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Enhanced_Flush_Cmd(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 3167, 0);
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        *pBuf = pSrc->packet_type;
        *pnConsumed += 1;
        pBuf += 1;
        nBuf -= 1;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                         */

typedef v_U32_t (*pfnPackTlvHCI_Enhanced_Flush_Cmd_t)(void *, tBtampTLVHCI_Enhanced_Flush_Cmd *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Enhanced_Flush_Cmd ( 0x00b8 )

v_U32_t btampPackTlvHCI_Enhanced_Flush_Complete_Event(void * pCtx,
                                                      tBtampTLVHCI_Enhanced_Flush_Complete_Event *pSrc,
                                                      v_U8_t *pBuf,
                                                      v_U32_t nBuf,
                                                      v_U32_t *pnConsumed)
{
    v_U8_t* pTlvLen = 0;
    v_U32_t nConsumedOnEntry;
    v_U32_t status = BTAMP_PARSE_SUCCESS;
    v_U32_t nNeeded = 0U;
    v_U32_t sType = 0U;
    v_U32_t sLen = 0U;
    sType = 1;
    sLen = 1;
        //                
    if( pCtx == NULL || pSrc == NULL ||
        pBuf == NULL || pnConsumed == NULL)
    {
        VOS_TRACE( VOS_MODULE_ID_BAP, VOS_TRACE_LEVEL_ERROR, "bad input" );
        return BTAMP_BAD_INPUT_BUFFER;
    }
    nConsumedOnEntry = *pnConsumed;

    status = btampGetPackedTlvHCI_Enhanced_Flush_Complete_Event(pCtx, pSrc, &nNeeded);
    if ( ! BTAMP_SUCCEEDED( status ) ) return status;
    nNeeded += sType + sLen;
    if ( nNeeded > nBuf ) return BTAMP_BUFFER_OVERFLOW;
    pTlvLen = pBuf;
    while ( pSrc->present )
    {
        if( sType == 2) frameshtons( pCtx, pBuf, 57, 0);
        else *pBuf = 57;
        pBuf += sType; nBuf -= sType; *pnConsumed += sType;
        pTlvLen = pBuf;
        pBuf += sLen; nBuf -= sLen; *pnConsumed += sLen;
        frameshtons(pCtx, pBuf, pSrc->log_link_handle, 0);
        *pnConsumed += 2;
        pBuf += 2;
        nBuf -= 2;
        break;
    }

    if (pTlvLen && sLen == 2)
    {
        frameshtons( pCtx, pTlvLen, *pnConsumed - nConsumedOnEntry - sType - sLen, 0);
    } else if(NULL != pTlvLen)
    {
        *pTlvLen = (v_U8_t)(*pnConsumed - nConsumedOnEntry - sType - sLen);
    }
    return status;
} /*                                                    */

typedef v_U32_t (*pfnPackTlvHCI_Enhanced_Flush_Complete_Event_t)(void *, tBtampTLVHCI_Enhanced_Flush_Complete_Event *, v_U8_t*, v_U32_t, v_U32_t*);
#define SigPackTlvHCI_Enhanced_Flush_Complete_Event ( 0x00b9 )

v_U32_t btampPackAMP_ASSOC(void * pCtx, tBtampAMP_ASSOC *pFrm, v_U8_t *pBuf, v_U32_t nBuf, v_U32_t *pnConsumed)
{
    v_U32_t i;
    static tTLVDefn TLVS[ ] = {
        {BTAMP_TLV_AMP_ASSOC_MAC_ADDR, 0, 9, 9, offsetof(tBtampAMP_ASSOC, AMP_Assoc_MAC_Addr), offsetof(tBtampTLVAMP_Assoc_MAC_Addr, present), SigPackTlvAMP_Assoc_MAC_Addr, (pfnGeneric_t)btampPackTlvAMP_Assoc_MAC_Addr, "AMP_Assoc_MAC_Addr", 1, },
        {BTAMP_TLV_AMP_ASSOC_PREFERRED_CHANNEL_LIST, 0, 9, 12, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Preferred_Channel_List), offsetof(tBtampTLVAMP_Assoc_Preferred_Channel_List, present), SigPackTlvAMP_Assoc_Preferred_Channel_List, (pfnGeneric_t)btampPackTlvAMP_Assoc_Preferred_Channel_List, "AMP_Assoc_Preferred_Channel_List", 1, },
        {BTAMP_TLV_AMP_ASSOC_CONNECTED_CHANNEL, 0, 9, 12, offsetof(tBtampAMP_ASSOC, AMP_Assoc_Connected_Channel), offsetof(tBtampTLVAMP_Assoc_Connected_Channel, present), SigPackTlvAMP_Assoc_Connected_Channel, (pfnGeneric_t)btampPackTlvAMP_Assoc_Connected_Channel, "AMP_Assoc_Connected_Channel", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_CAPABILITIES, 0, 7, 7, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Capabilities), offsetof(tBtampTLVAMP_Assoc_PAL_Capabilities, present), SigPackTlvAMP_Assoc_PAL_Capabilities, (pfnGeneric_t)btampPackTlvAMP_Assoc_PAL_Capabilities, "AMP_Assoc_PAL_Capabilities", 0, },
        {BTAMP_TLV_AMP_ASSOC_PAL_VERSION, 0, 8, 8, offsetof(tBtampAMP_ASSOC, AMP_Assoc_PAL_Version), offsetof(tBtampTLVAMP_Assoc_PAL_Version, present), SigPackTlvAMP_Assoc_PAL_Version, (pfnGeneric_t)btampPackTlvAMP_Assoc_PAL_Version, "AMP_Assoc_PAL_Version", 1, },
    { 0xffff, 0 },
    };

    v_U32_t idx = 0;
    v_U32_t status = 0;
    (void)i;
    *pnConsumed = 0U;
    status |= PackTlvCore(pCtx,(v_U8_t*)pFrm,pBuf,nBuf,pnConsumed,TLVS,&idx);

#   ifdef BTAMP_DUMP_FRAMES
    if (!BTAMP_FAILED(status))
    {
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Packed the AMP_ASSOC:\n"));
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_MAC_Addr:\n"));
        if (!pFrm->AMP_Assoc_MAC_Addr.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_MAC_Addr.mac_addr, 6);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_Preferred_Channel_List:\n"));
        if (!pFrm->AMP_Assoc_Preferred_Channel_List.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_Preferred_Channel_List.country, 3);
            FRAMES_LOG1(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("num_triplets: %d.\n"), pFrm->AMP_Assoc_Preferred_Channel_List.num_triplets);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* ) pFrm->AMP_Assoc_Preferred_Channel_List.triplets, 3 * pFrm->AMP_Assoc_Preferred_Channel_List.num_triplets);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_Connected_Channel:\n"));
        if (!pFrm->AMP_Assoc_Connected_Channel.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_Connected_Channel.country, 3);
            FRAMES_LOG1(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("num_triplets: %d.\n"), pFrm->AMP_Assoc_Connected_Channel.num_triplets);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* ) pFrm->AMP_Assoc_Connected_Channel.triplets, 3 * pFrm->AMP_Assoc_Connected_Channel.num_triplets);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_PAL_Capabilities:\n"));
        if (!pFrm->AMP_Assoc_PAL_Capabilities.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Capabilities.pal_capabilities, 4);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("AMP_Assoc_PAL_Version:\n"));
        if (!pFrm->AMP_Assoc_PAL_Version.present)
        {
            FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("Not present.\n"));
        }
        else
        {
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_version, 1);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_CompanyID, 2);
            FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), ( v_U8_t* )&pFrm->AMP_Assoc_PAL_Version.pal_subversion, 2);
        }
        FRAMES_LOG0(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), FRFL("to:\n"));
        FRAMES_DUMP(pCtx, FRAMES_SEV_FOR_FRAME(pCtx, BTAMP_AMP_ASSOC), pBuf, nBuf);
    }
#   endif //                  
    return status;

} /*                           */


static v_U32_t PackTlvCore(void * pCtx,
                        v_U8_t *pSrc,
                        v_U8_t *pBuf,
                        v_U32_t  nBuf,
                        v_U32_t *pnConsumed,
                        tTLVDefn  TLVs[],
                        v_U32_t *pidx)
{
    tTLVDefn     *pTlv;
    tFRAMES_BOOL *pfFound;
    v_U8_t *pBufRemaining;
    v_U32_t nBufRemaining, status, status2, len;

    BTAMP_PARAMETER_CHECK2(pSrc, pBuf, nBuf, pnConsumed);

    (void)pCtx;
    status = BTAMP_PARSE_SUCCESS;
    status2 = BTAMP_PARSE_SUCCESS;
    pBufRemaining = pBuf;
    nBufRemaining = nBuf;

    pTlv = &( TLVs[0] );
    while ( 0xffff != pTlv->id )
    {
        pfFound = (tFRAMES_BOOL*)(pSrc + pTlv->offset +
                                  pTlv->presenceOffset);
        if ( *pfFound && pTlv->minSize > nBufRemaining )
        {
            FRAMES_LOG3(pCtx, FRLOGE, FRFL("The TLV %s takes at least"
                " %d bytes, but there are only %d left in the buffer."
                "\n"), pTlv->name, pTlv->minSize, nBufRemaining);
            return BTAMP_BUFFER_OVERFLOW;
        }

        len = 0U;

        if ( *pfFound ) {
        switch ( pTlv->sig )
        {
                case SigPackTlvAMP_Assoc_Connected_Channel:
                        status2 = ( (pfnPackTlvAMP_Assoc_Connected_Channel_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_Connected_Channel* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvAMP_Assoc_MAC_Addr:
                        status2 = ( (pfnPackTlvAMP_Assoc_MAC_Addr_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_MAC_Addr* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvAMP_Assoc_PAL_Capabilities:
                        status2 = ( (pfnPackTlvAMP_Assoc_PAL_Capabilities_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_PAL_Capabilities* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvAMP_Assoc_PAL_Version:
                        status2 = ( (pfnPackTlvAMP_Assoc_PAL_Version_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_PAL_Version* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvAMP_Assoc_Preferred_Channel_List:
                        status2 = ( (pfnPackTlvAMP_Assoc_Preferred_Channel_List_t)(pTlv->pfn) )(pCtx, ( tBtampTLVAMP_Assoc_Preferred_Channel_List* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvFlow_Spec:
                        status2 = ( (pfnPackTlvFlow_Spec_t)(pTlv->pfn) )(pCtx, ( tBtampTLVFlow_Spec* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Accept_Logical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Accept_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Accept_Logical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Accept_Physical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Accept_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Accept_Physical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Channel_Selected_Event:
                        status2 = ( (pfnPackTlvHCI_Channel_Selected_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Channel_Selected_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Command_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Command_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Command_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Command_Status_Event:
                        status2 = ( (pfnPackTlvHCI_Command_Status_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Command_Status_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Create_Logical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Create_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Create_Logical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Create_Physical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Create_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Create_Physical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Data_Buffer_Overflow_Event:
                        status2 = ( (pfnPackTlvHCI_Data_Buffer_Overflow_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Data_Buffer_Overflow_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Disconnect_Logical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Disconnect_Logical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Logical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Disconnect_Logical_Link_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Disconnect_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Logical_Link_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Disconnect_Physical_Link_Cmd:
                        status2 = ( (pfnPackTlvHCI_Disconnect_Physical_Link_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Physical_Link_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Disconnect_Physical_Link_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Disconnect_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Disconnect_Physical_Link_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Flow_Spec_Modify_Cmd:
                        status2 = ( (pfnPackTlvHCI_Flow_Spec_Modify_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flow_Spec_Modify_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Flow_Spec_Modify_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Flow_Spec_Modify_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flow_Spec_Modify_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Flush_Cmd:
                        status2 = ( (pfnPackTlvHCI_Flush_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flush_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Flush_Occurred_Event:
                        status2 = ( (pfnPackTlvHCI_Flush_Occurred_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Flush_Occurred_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Generic_AMP_Link_Key_Notification_Event:
                        status2 = ( (pfnPackTlvHCI_Generic_AMP_Link_Key_Notification_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Generic_AMP_Link_Key_Notification_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Hardware_Error_Event:
                        status2 = ( (pfnPackTlvHCI_Hardware_Error_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Hardware_Error_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Logical_Link_Cancel_Cmd:
                        status2 = ( (pfnPackTlvHCI_Logical_Link_Cancel_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Logical_Link_Cancel_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Logical_Link_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Logical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Logical_Link_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Loopback_Command_Event:
                        status2 = ( (pfnPackTlvHCI_Loopback_Command_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Loopback_Command_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Physical_Link_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Physical_Link_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Physical_Link_Loss_Warning_Event:
                        status2 = ( (pfnPackTlvHCI_Physical_Link_Loss_Warning_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Loss_Warning_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Physical_Link_Recovery_Event:
                        status2 = ( (pfnPackTlvHCI_Physical_Link_Recovery_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Physical_Link_Recovery_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Qos_Violation_Event:
                        status2 = ( (pfnPackTlvHCI_Qos_Violation_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Qos_Violation_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Best_Effort_Flush_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Buffer_Size_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Buffer_Size_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Buffer_Size_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Connection_Accept_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Data_Block_Size_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Data_Block_Size_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Data_Block_Size_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Failed_Contact_Counter_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Flow_Control_Mode_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Link_Quality_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Link_Quality_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Link_Quality_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Link_Supervision_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Local_AMP_Assoc_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Local_AMP_Assoc_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_AMP_Assoc_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Local_AMP_Information_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Local_AMP_Information_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_AMP_Information_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Local_Supported_Cmds_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Local_Supported_Cmds_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_Supported_Cmds_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Local_Version_Info_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Local_Version_Info_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Local_Version_Info_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Location_Data_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Location_Data_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Logical_Link_Accept_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_Loopback_Mode_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_Loopback_Mode_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Read_RSSI_Cmd:
                        status2 = ( (pfnPackTlvHCI_Read_RSSI_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Read_RSSI_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Reset_Cmd:
                        status2 = ( (pfnPackTlvHCI_Reset_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Reset_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Reset_Failed_Contact_Counter_Cmd:
                        status2 = ( (pfnPackTlvHCI_Reset_Failed_Contact_Counter_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Reset_Failed_Contact_Counter_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Set_Event_Mask_Cmd:
                        status2 = ( (pfnPackTlvHCI_Set_Event_Mask_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Event_Mask_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Set_Event_Mask_Page_2_Cmd:
                        status2 = ( (pfnPackTlvHCI_Set_Event_Mask_Page_2_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Event_Mask_Page_2_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Set_Short_Range_Mode_Cmd:
                        status2 = ( (pfnPackTlvHCI_Set_Short_Range_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Set_Short_Range_Mode_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Short_Range_Mode_Change_Complete_Event:
                        status2 = ( (pfnPackTlvHCI_Short_Range_Mode_Change_Complete_Event_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Short_Range_Mode_Change_Complete_Event* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Best_Effort_Flush_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Best_Effort_Flush_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Connection_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Connection_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Connection_Accept_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Flow_Control_Mode_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Flow_Control_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Flow_Control_Mode_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Link_Supervision_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Link_Supervision_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Link_Supervision_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Location_Data_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Location_Data_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Location_Data_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Logical_Link_Accept_Timeout_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Logical_Link_Accept_Timeout_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Loopback_Mode_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Loopback_Mode_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Loopback_Mode_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
                case SigPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd:
                        status2 = ( (pfnPackTlvHCI_Write_Remote_AMP_ASSOC_Cmd_t)(pTlv->pfn) )(pCtx, ( tBtampTLVHCI_Write_Remote_AMP_ASSOC_Cmd* )(pSrc + pTlv->offset), pBufRemaining, nBufRemaining, &len);
                        if (status2) status |= status2;
                    break;
        default:
            FRAMES_LOG1(pCtx, FRLOGE, FRFL("INTERNAL ERROR-- I don't "
                "know about the TLV %d; this is most likely a bug in "
                "'framesc'.\n"), pTlv->sig);
            return BTAMP_INTERNAL_ERROR;
        }

        } /*                    */
        pBufRemaining += len;
        nBufRemaining -= len;
        *pnConsumed   += len;
        ++pTlv;
        if(len) ++*pidx;
    }

    return status;

}

