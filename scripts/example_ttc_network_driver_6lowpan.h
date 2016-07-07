#ifndef EXAMPLE_NETWORK_H
#define EXAMPLE_NETWORK_H

// Basic set of helper functions
#include "../ttc-lib/ttc_basic.h"
#include "../ttc-lib/ttc_network.h"
#include "../ttc-lib/ttc_gpio.h"
#include "../ttc-lib/ttc_timer.h"

#include <string.h>

//} Includes
//{ Structures/ Enums ****************************************************

//} Structures/ Enums
//{ Global Variables *****************************************************



//} Global Variables
//{ Function prototypes **************************************************

/* Call before example_can_start() to initialize hardware.
 */
void example_network_init();

/* initializes + starts network example
 */
void example_ttc_network_driver_6lowpan_start();

/* Sends "Hello World" to initialized MAC
 */
void task_MAC_sender(void *TaskArgument);

/** processes a packet being received by protocol
 * @param Status  meta information about received packet
 * @param Buffer  data being received
 * @param Amount  amount of valid bytes in Buffer[]
 */
void receivePacket(ttc_network_packet_status* Status, u8_t* Buffer, Base_t Amount);


//} Function prototypes

#endif // EXAMPLE_NETWORK_H
