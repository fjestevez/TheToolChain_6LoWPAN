//
//  clock.c
//  
//
//  Created by Francisco Estevez on 10/07/13.
//
//

#include "6lowpan_adapt_clock.h"

clock_time_t clock_time(void){
    return ttc_task_get_tick_count()/1000000;
}


