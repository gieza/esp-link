#include <esp8266.h>
#include "config.h"
#include "serbridge.h"
#include "mcuwd.h"

static ETSTimer mcuwdTimer;
static uint32_t mcuwdNoActivitySeconds;

static void ICACHE_FLASH_ATTR mcuwdTimerCb(void *v) {
  if (serbridgeInMCUFlashing()) {
    mcuwdNoActivitySeconds=0; 
    return;
  }
  mcuwdNoActivitySeconds++;
  uint16_t timeout = flashConfig.mcu_wd_timeout;
  if (timeout>0 && mcuwdNoActivitySeconds>timeout) {
    mcuwdNoActivitySeconds=0;
    os_printf("Watchdog detected MCU inactivity for over %d seconds, attempting MCU reset...\n", timeout);
    serbridgeReset();
  }
}

void ICACHE_FLASH_ATTR mcuwd_init() {
  mcuwdNoActivitySeconds=0;
  os_timer_disarm(&mcuwdTimer);
  uint16_t timeout = flashConfig.mcu_wd_timeout;
  if (timeout>0) {
    os_timer_setfn(&mcuwdTimer, mcuwdTimerCb, NULL);
    os_timer_arm(&mcuwdTimer, 1000, 1);
    os_printf("MCU watchdog is set to %d seconds\n", timeout);
  } else os_printf("MCU watchdog disabled\n");
}

void ICACHE_FLASH_ATTR mcuwd_feed()
{
   mcuwdNoActivitySeconds=0;
}