/*
                   
  
 */

/*
                              
 */
#include <linux/wakelock.h>

#include "felica_common.h"

/*
          
 */

/*
                         
 */

static struct wake_lock felica_wake_lock;

#ifdef FELICA_LED_SUPPORT
static struct wake_lock felica_rfs_wake_lock;
#endif

/*
                         
 */

/*
               
              
          
*/
void lock_felica_wake_lock(void)
{
  wake_lock(&felica_wake_lock);
}
/*
               
              
          
*/
void unlock_felica_wake_lock(void)
{
  wake_unlock(&felica_wake_lock);
}
/*
               
              
          
*/
void init_felica_wake_lock(void)
{
  wake_lock_init(&felica_wake_lock, WAKE_LOCK_SUSPEND, "felica");
}
/*
               
              
          
*/
void destroy_felica_wake_lock(void)
{
  wake_lock_destroy(&felica_wake_lock);
}

/*
               
              
                           
*/
int get_felica_uart_status(void)
{
#if defined(CONFIG_LGE_FELICA_NFC)
  int waitcount = 3;
  int retrycount = 10;
  int rval = FELICA_UART_NOTAVAILABLE;

  _e_snfc_uart_status uart_status = __snfc_uart_control_get_uart_status();
  
  switch(uart_status)
  {
    case UART_STATUS_READY:
    case UART_STATUS_FOR_FELICA:
      rval = FELICA_UART_AVAILABLE;
      break;

    default:
      rval = FELICA_UART_NOTAVAILABLE;
      break;
  }

  if(FELICA_UART_NOTAVAILABLE == rval)
  {
    FELICA_DEBUG_MSG_MED("[FELICA_COMMON] uart can be used - wait 30msec \n");

    while(0 < waitcount)
    {
      waitcount--;
      mdelay(10);

      if(UART_STATUS_READY == __snfc_uart_control_get_uart_status())
      {
        FELICA_DEBUG_MSG_MED("[FELICA_COMMON] uart state was changed : avalable \n");

        rval = FELICA_UART_AVAILABLE;
        break;
      }
    }
  }

  if(FELICA_UART_AVAILABLE != rval)
  {
    FELICA_DEBUG_MSG_MED("[FELICA_COMMON] uart can be used - wait 1sec \n");

    while(0 < retrycount)
    {
      retrycount--;
      mdelay(100);
      waitcount = 3;

      FELICA_DEBUG_MSG_MED("[FELICA_COMMON] uart can be used - wait 30msec during wait 1sec \n");

      while(0 < waitcount)
      {
        waitcount--;
        mdelay(10);
        if(UART_STATUS_READY == __snfc_uart_control_get_uart_status())
        {
          FELICA_DEBUG_MSG_MED("[FELICA_COMMON] uart state was changed : avalable \n");

          rval = FELICA_UART_AVAILABLE;
          break;
        }
      }

      if(FELICA_UART_AVAILABLE == rval)
      {
        break;
      }
    }
  }

  return rval;
#else
  return FELICA_UART_AVAILABLE;
#endif
}

/*
               
              
          
*/
void set_felica_uart_status(_e_snfc_uart_status uart_status)
{
#if defined(CONFIG_LGE_FELICA_NFC)
  FELICA_DEBUG_MSG_MED("[FELICA_COMMON] set_felica_uart_status : %d \n", uart_status);

  __snfc_uart_control_set_uart_status(uart_status);
#endif
}


/*
               
              
                           
*/
_e_snfc_i2c_status get_felica_i2c_status(void)
{
#if defined(CONFIG_LGE_FELICA_NFC)
  return __snfc_i2c_control_get_status();
#else
  return I2C_STATUS_NO_USE;
#endif
}

/*
               
              
          
*/
void set_felica_i2c_status(_e_snfc_i2c_status i2c_status)
{
#if defined(CONFIG_LGE_FELICA_NFC)
  FELICA_DEBUG_MSG_MED("[FELICA_COMMON] set_felica_i2c_status : %d \n", i2c_status);

  __snfc_i2c_control_set_status(i2c_status);
#endif
}

#ifdef FELICA_LED_SUPPORT
/*
               
              
          
*/
void lock_felica_rfs_wake_lock(void)
{
  wake_lock(&felica_rfs_wake_lock);
}
/*
               
              
          
*/
void unlock_felica_rfs_wake_lock(void)
{
  wake_unlock(&felica_rfs_wake_lock);
}
/*
               
              
          
*/
void init_felica_rfs_wake_lock(void)
{
  wake_lock_init(&felica_rfs_wake_lock, WAKE_LOCK_SUSPEND, "felica_rfs");
}
/*
               
              
          
*/
void destroy_felica_rfs_wake_lock(void)
{
  wake_lock_destroy(&felica_rfs_wake_lock);
}
#endif
