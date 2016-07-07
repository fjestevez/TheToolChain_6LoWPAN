/**
 *
 * $Id: 6lowpan_radio_serialradio.h, 15.11.2013 fjestevez Exp $
 */

/**
 * \file
 *         Serial Radio definition
 * \author
 *         Francisco Estevez <fjestevez@fh-muenster.de>
 */

#ifndef __SERIALRADIO_H__
#define __SERIALRADIO_H__

#include "6lowpan_radio_radio.h"
#include "../ttc_basic.h"
#include "../ttc_gpio.h"
#include "../ttc_usart.h"
#include "../ttc_string.h"
#include "../ttc_queue.h"

extern const struct radio_driver serialradio_driver;

#define USART1_INDEX 1                    // using first  USART available on current board

ttc_memory_pool_t* TXMemPool = NULL;
ttc_memory_pool_t* RXMemPool = NULL;

typedef struct buffer_s {
    void* Payload;
    unsigned short Length;
    struct buffer_s* Next;
} buffer_t;

#endif /* __SERIALRADIO_H__ */


/** @} */
/** @} */
