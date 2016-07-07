//
//  memb.h
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#ifndef __MEMB_NETWORK_H__
#define __MEMB_NETWORK_H__

#include "../ttc_memory.h"

typedef struct memb{} ContikiMemb;
#define ContikiMemb ttc_memory_pool_t

void  memb_init(ttc_memory_pool_t *m);

void *memb_alloc(ttc_memory_pool_t *m);

char  memb_free(ttc_memory_pool_t *m, void *ptr);

int memb_inmemb(ttc_memory_pool_t *m, void *ptr);

#endif /* __MEMB_NETWORK_H__ */

