//
//  watchdog.h
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

//#ifdef EXTENSION_200_cpu_stm32f10x
#include "../../../../../TTC-Library/ttc_watchdog.h"
//#endif

void watchdog_start(void);
void watchdog_periodic(void);
void watchdog_stop(void);

#endif /* __WATCHDOG_H__ */
