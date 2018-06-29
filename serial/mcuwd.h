#ifndef MCUWD_H
#define MCUWD_H

/* 
   Watchdog functionality for the attached MCU.
   Since we have control of MCU's Reset pin anyways, 
   why not take this advantage and reset MCU if it's 
   become unresponsive. 
   For this to work, we assume that MCU regularly communicates with the ESP via the
   serial line. If you don't normally do that, you can simulate activity by calling
   any fuction in the cmd.h, for example, query WiFi signal strength every so often.
*/

/* Initialize, update or disable the watchdog depending on the mcu_wd_timeout in config:
   mcu_wd_timeout>0 - enable the watchdog (or update the timeout if already enabled),
   mcu_wd_timeout<=0 - disable the watchdog.
*/ 
void ICACHE_FLASH_ATTR mcuwd_init();
/*
   Once watchdog is enabled, mcuwd_feed() must be called regularly indicating MCU activity.
   If not called for more than timeout_ms milliseconds, the MCU will be reset.
   Watchdog continues to run after reset, so if the MCU is not coming to live after the first reset, 
   we will continue reset attempts infinitely.
*/
void ICACHE_FLASH_ATTR mcuwd_feed();

#endif
