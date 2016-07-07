//
//  gen-task.h
//  
//
//  Created by Francisco Estevez on 12/07/13.
//
//

#ifndef _GEN_TASK_H
#define _GEN_TASK_H

#include "../../../../../TTC-Library/ttc_task.h"

#define task_create(task, name, size, arg1, priority, arg2) \
ttc_task_create(task, name, size, arg1, priority, arg2);

#define task_yield() ttc_task_yield()

struct pt {
    unsigned short lc;
};

#endif
