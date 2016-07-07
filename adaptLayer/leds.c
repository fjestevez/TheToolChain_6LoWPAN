//
//  leds.c
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#include "inc/leds.h"

void leds_on(unsigned char leds){
    switch(leds){
        case 1: ttc_gpio_set_variable(TTC_LED1);
            break;
        case 2: ttc_gpio_set_variable(TTC_LED2);
            break;
        default: ttc_gpio_set_variable(TTC_LED1);
            break;
    }
}

void leds_off(unsigned char leds){
    switch(leds){
        case 1: ttc_gpio_clr_variable(TTC_LED1);
            break;
        case 2: ttc_gpio_clr_variable(TTC_LED2);
            break;
        default: ttc_gpio_clr_variable(TTC_LED1);
            break;
    }
}

void leds_toggle(unsigned char leds){
    u32_t TickCount = ttc_task_get_tick_count();
    u32_t NoToggleBefore = 0;
    
    if(TickCount > NoToggleBefore)
        switch(leds){
            case 1: ttc_gpio_set_variable(TTC_LED1);
                break;
            case 2: ttc_gpio_set_variable(TTC_LED2);
                break;
            default: ttc_gpio_set_variable(TTC_LED1);
                break;
        }
    else
        switch(leds){
            case 1: ttc_gpio_clr_variable(TTC_LED1);
                break;
            case 2: ttc_gpio_clr_variable(TTC_LED2);
                break;
            default: ttc_gpio_clr_variable(TTC_LED1);
                break;
        }
    
    NoToggleBefore = TickCount+1000;
}
