//
//  memb.c
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#include "6lowpan_adapt_memb.h"

void  memb_init(ttc_memory_pool_t *m){
    //ttc_memory_pool_init(m, name_size, name_num);
}

void *memb_alloc(ttc_memory_pool_t *m){
    m = ttc_memory_pool_block_get(m);
    return (void *) m;
}

char memb_free(ttc_memory_pool_t* m, void *ptr){
    ttc_memory_block_release((ttc_memory_block_t*) m);
//#error ToDo: FIX!
    
    return 0; //0 - Sucessfully desallocated
              //-1 - Error in the process
} //memb_free - Probably Fails

int memb_inmemb(ttc_memory_pool_t *m, void *ptr){
    return 1;
}

