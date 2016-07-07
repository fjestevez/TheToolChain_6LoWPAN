/*{ ttc_network.c ***************************************************

 This source is published under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).
 See file LEGAL.txt in this software package for details.

 Authors: <Gregor Rebel>

 Description: Basic universal network support.

}*/

#include "ttc_network.h"

//{ global variables ************************************************

// configuration of all defined networks
ttc_network_config_t* tn_Networks[TTC_NETWORK_MAX];

//}global variables
//{ function definitions ********************************************

void ttc_network_prepare() {
#ifdef EXTENSION_450_ttc_network_driver_6lowpan
    ttc_network_driver_6lowpan_prepare();
#endif
}
ttc_network_config_t* ttc_network_get_configuration(u8_t LogicalIndex) {
    Assert_Network(LogicalIndex, ec_InvalidArgument); // logical index starts at 1
    Assert_Network(LogicalIndex <= TTC_NETWORK_MAX, ec_InvalidArgument); // indexed network not configured in Makefile!

    ttc_network_config_t* Config = tn_Networks[LogicalIndex];
    if (!Config) { // first call: create structure
        tn_Networks[LogicalIndex] = Config = ttc_memory_alloc_zeroed(sizeof(ttc_network_config_t));
        ttc_network_load_defaults(LogicalIndex);
    }

    return Config;
}
void ttc_network_load_defaults(u8_t LogicalIndex) {
    ttc_network_config_t* Config = ttc_network_get_configuration(LogicalIndex);

    if (!Config->DriverConfig) {
        DRIVER_ttc_network_load_defaults(Config);
    }
}
void ttc_network_init(u8_t LogicalIndex) {
    ttc_network_config_t* Config = ttc_network_get_configuration(LogicalIndex);

    DRIVER_ttc_network_init(Config);
}
void ttc_network_send_direct_raw(u8_t LogicalIndex, ttc_network_address_t Target, u8_t* Buffer, Base_t Amount) {
    ttc_network_config_t* Config = ttc_network_get_configuration(LogicalIndex);

    DRIVER_ttc_network_send_direct_raw(Config, Target, Buffer, Amount);
}
void ttc_network_send_broadcast_raw(u8_t LogicalIndex, u8_t* Buffer, Base_t Amount) {
    ttc_network_send_direct_raw(LogicalIndex, TTC_NETWORK_BROADCAST, Buffer, Amount);
}
void ttc_network_register_receive(u8_t LogicalIndex, void (*receivePacket)(ttc_network_packet_status* Status, u8_t* Buffer, Base_t Amount)) {
    ttc_network_config_t* Config = ttc_network_get_configuration(LogicalIndex);

    Config->function_ReceivePacket = receivePacket;
}
ttc_network_node_t* ttc_network_get_neighbours(u8_t LogicalIndex) {
    ttc_network_config_t* Config = ttc_network_get_configuration(LogicalIndex);

#ifdef DRIVER_ttc_network_get_neighbours
    DRIVER_ttc_network_get_neighbours(Config);
#else
    (void) Config;

    return NULL;
#endif
}

//}function definitions
