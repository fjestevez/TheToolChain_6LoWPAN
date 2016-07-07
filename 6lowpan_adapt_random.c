//
//  random.c
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#include "6lowpan_adapt_random.h"

void random_init(unsigned short seed){
    ttc_srand(seed);
}

unsigned short random_rand(void){
    return ttc_rand();
}
