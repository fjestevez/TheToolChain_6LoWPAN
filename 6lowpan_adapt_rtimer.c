/**
 * \file
 *         Implementation of the architecture-agnostic parts of the real-time timer module.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *	   Francisco Estevez <fjestevez@ieee.org>
 *
 */


/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)$Id: rtimer.c,v 1.7 2010/01/19 13:08:24 adamdunkels Exp $
 */

#include "6lowpan_adapt_rtimer.h"
//#include "contiki.h"

#define DEBUG 0
#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

//static struct rtimer *next_rtimer;

/*---------------------------------------------------------------------------*/
void
rtimer_init(void)
{
  //rtimer_arch_init(); 
  ttc_timer_reset();
}
/*---------------------------------------------------------------------------*/
int
rtimer_set(struct rtimer *rtimer, Base_t time,
           Base_t duration,
	   rtimer_callback_t func, void *ptr)
{
  int* aux = (int*)ptr;
  int continuous = 0;
  if(*aux == 0)
  	continuous = 1;
  
  (*rtimer).timer = ttc_timer_new_timer((void*)func,(void*)(rtimer, ptr), time, continuous);
  
  if((*rtimer).timer != NULL){
          (*rtimer).func = func;
          (*rtimer).ptr = ptr;
          (*rtimer).time = time;

          return RTIMER_OK;
  }
  else return 0;

/*
  int first = 0;

  PRINTF("rtimer_set time %d\n", time);

  if(next_rtimer == NULL) {
    first = 1;
  }

  rtimer->func = func;
  rtimer->ptr = ptr;

  rtimer->time = time;
  next_rtimer = rtimer;

  if(first == 1) {
    rtimer_arch_schedule(time);
  }
  return RTIMER_OK; */

}
/*---------------------------------------------------------------------------*/
void
rtimer_run_next(void)
{
 /* struct rtimer *t;
  if(next_rtimer == NULL) {
    return;
  }
  t = next_rtimer;
  next_rtimer = NULL;
  //t->func(t, t->ptr);
  //if(next_rtimer != NULL) {
    //rtimer_arch_schedule(next_rtimer->time);
  //}
//  return;*/
}
/*---------------------------------------------------------------------------*/
