#ifndef CONSOLE_H
#define CONSOLE_H

#include "httpd.h"

#define CONSOLE_BUF_MAX (1024*3)

void consoleInit(void);
void ICACHE_FLASH_ATTR console_write_char(char c);
int ajaxConsole(HttpdConnData *connData);
int ajaxConsoleReset(HttpdConnData *connData);
int ajaxConsoleClear(HttpdConnData *connData);
int ajaxConsoleBaud(HttpdConnData *connData);
int ajaxConsoleFormat(HttpdConnData *connData);
int ajaxConsoleSend(HttpdConnData *connData);
int tplConsole(HttpdConnData *connData, char *token, void **arg);
int ICACHE_FLASH_ATTR consoleGetWr(void);
char* ICACHE_FLASH_ATTR consoleGetBufPtr(void);

#endif
