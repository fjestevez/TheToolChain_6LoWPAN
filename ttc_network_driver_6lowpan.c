/*{ ttc_network_driver_6lowpan_driver_6lowpan.c ***************************************************

 This source is published under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).
 See file LEGAL.txt in this software package for details.

 Authors: <Gregor Rebel>

 Description: Low-Level network driver for 6lowpan network protocol

}*/

#include "ttc_network_driver_6lowpan.h"

//{ global variables ************************************************

#if RIMEADDR_SIZE == 1
    const rimeaddr_t addr_ff = { { 0xff } };
#else /*RIMEADDR_SIZE == 2*/
#if RIMEADDR_SIZE == 2
    const rimeaddr_t addr_ff = { { 0xff, 0xff } };
#else /*RIMEADDR_SIZE == 2*/
#if RIMEADDR_SIZE == 8
    const rimeaddr_t addr_ff = { { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff } };
#endif /*RIMEADDR_SIZE == 8*/
#endif /*RIMEADDR_SIZE == 2*/
#endif /*RIMEADDR_SIZE == 1*/

ttc_network_6lowpan_config_t* get_driver_config(ttc_network_config_t* Config) {
    Assert_Network(ttc_memory_is_writable(Config), ec_InvalidArgument);
    return (ttc_network_6lowpan_config_t*) &(Config->DriverConfig);
}

//}global variables
//{ function definitions ********************************************

void ttc_network_driver_6lowpan_load_defaults(ttc_network_config_t* Config){
    if (Config->DriverConfig == NULL) { // first call: create driver configuration
        Config->DriverConfig = ttc_memory_alloc_zeroed(sizeof(ttc_network_6lowpan_config_t));
    }
    ttc_network_6lowpan_config_t* DriverConfig = get_driver_config(Config);
}
void ttc_network_driver_6lowpan_prepare() {

    // Fill DriverConfig...

        queuebuf_init();
        netstack_init();
        rimeaddr_set_node_addr( &addr_ff );

        /*NETSTACK_RDC.init();
        NETSTACK_MAC.init();
        NETSTACK_NETWORK.init();*/

        //NETSTACK_RADIO.on();
        //NETSTACK_MAC.on();
        packetbuf_clear();
}
void ttc_network_driver_6lowpan_reset(void){

}
void ttc_network_driver_6lowpan_deinit(void){

}
void ttc_network_driver_6lowpan_send_packet(mac_callback_t TaskFunction, void *ptr){
    NETSTACK_MAC.send(TaskFunction, ptr);
}

//}function definitions
