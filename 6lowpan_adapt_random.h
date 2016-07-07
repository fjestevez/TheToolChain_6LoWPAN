//
//  random.h
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "../ttc_random.h"

void random_init(unsigned short seed);
unsigned short random_rand(void);

// RAND_MAX should be defined in ttc_random.h
#define RANDOM_RAND_MAX RAND_MAX
//#define RANDOM_RAND_MAX 65535U

#endif /* __RANDOM_H__ */
