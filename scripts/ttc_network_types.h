/** { ttc_network_types.h ************************************************

                           The ToolChain

   High-Level interface for network device.
   
   Structures, Enums and Defines being required by both, high- and low-level network.
   

   Authors:
   
}*/

#ifndef TTC_NETWORK_TYPES_H
#define TTC_NETWORK_TYPES_H

#include "ttc_basic.h"
#include "ttc_list_types.h"

//{ Defines ***************************************************


//} Defines
//{ Static Configuration **************************************

//}Static Configuration
//{ Enums/ Structures *****************************************

typedef enum {
    tnts_undefined = 0, //
    tnts_uip,
    tnts_rime
} tnt_stack_e;

typedef enum {
    tntp_undefined = 0, //
    tntp_6lowpan,
    tntp_tcp,
    tntp_udp
} tnt_protocol_e;

typedef enum {    // return codes of network devices
  ec_network_OK = 0,
  
  // other warnings go here..

  ec_network_ERROR,           // general failure
  ec_network_DeviceNotFound,
  ec_network_InvalidImplementation
  
  // other failures go here..
} ttc_network_errorcode_e;

// TTC_NETWORK_ADDRESS_SIZE must be defined outside (Makefile)

// test
#define TTC_NETWORK_ADDRESS_SIZE 1

#if TTC_NETWORK_ADDRESS_SIZE == 1
#  define ttc_network_address_t u8_t
#  define TTC_NETWORK_BROADCAST 0xff
#endif
#if TTC_NETWORK_ADDRESS_SIZE == 2
#  define ttc_network_address_t u16_t
#  define TTC_NETWORK_BROADCAST 0xffff
#endif
#if TTC_NETWORK_ADDRESS_SIZE == 4
#  define ttc_network_address_t u32_t
#  define TTC_NETWORK_BROADCAST 0xffffffff
#endif
#if TTC_NETWORK_ADDRESS_SIZE == 8
#  define ttc_network_address_t struct { u8_t B1; u8_t B2; u8_t B3; u8_t B4; u8_t B5; u8_t B6; u8_t B7; u8_t B8; } __attribute__((__packed__))
#  define TTC_NETWORK_BROADCAST 0xffffffffffffffff
#endif
#ifndef ttc_network_address_t
#  warning Undefined constant TTC_NETWORK_ADDRESS_SIZE (using default size)
#  define ttc_network_address_t u8_t
#endif

typedef struct {
    // configuration of network that has created this Status
    struct ttc_network_config_s* Config;

    // protocol address of sender node
    ttc_network_address_t Sender;

    // received signal strength indicator (not yet implemented!)
    u8_t RSSI;

    // more to come..
} ttc_network_packet_status;

typedef struct ttc_network_config_s { // architecture independent configuration data

    // Note: Write-access to this structure is only allowed before first ttc_network_init() call!
    //       After initialization, only read accesses are allowed for high-level code.

    // local protocol address
    ttc_network_address_t LocalAddress;

    // bitmask identifying all nodes in same network
    ttc_network_address_t Netmask;

    // type of network stack to use
    tnt_stack_e    Stack;

    // type of protocol to use
    tnt_protocol_e Protocol;

    /** function that processes a packet being received by protocol
     * @param Config  configuration of network that has received this packet
     * @param Status  meta information about received packet
     * @param Buffer  data being received
     * @param Amount  amount of valid bytes in Buffer[]
     */
    void (*function_ReceivePacket)(ttc_network_packet_status* Status, u8_t* Buffer, Base_t Amount);

    // configuration of low-level driver
    void* DriverConfig;
    
} __attribute__((__packed__)) ttc_network_config_t;

typedef struct ttc_network_node_s {
    ttc_list_item_t* ListItem;

    // protocol address of single network node
    ttc_network_address_t Address;

    // average RSSI of this node (optional)
    u8_t RSSI;

} ttc_network_node_t;

//}Structures

#endif // TTC_NETWORK_TYPES_H
