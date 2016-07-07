//
//  watchdog.c
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#include "inc/watchdog.h"

void watchdog_start(void){
    ttc_watchdog_init1(0,0);
}

void watchdog_periodic(void){
    ttc_watchdog_reload1();
}

void watchdog_stop(void){
    ttc_watchdog_deinit1();
}

