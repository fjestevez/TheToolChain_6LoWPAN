//
//  clock.h
//  
//
//  Created by Francisco Estevez on 10/07/13.
//
//

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "../ttc_task.h"

#define CLOCK_CONF_SECOND 1000000*ttc_task_get_elapsed_usecs()
#define CLOCK_SECOND CLOCK_CONF_SECOND

typedef unsigned int clock_time_t;

clock_time_t clock_time(void);

#endif /* __CLOCK_H__ */

