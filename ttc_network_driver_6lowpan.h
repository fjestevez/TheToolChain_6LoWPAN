#ifndef ttc_network_driver_6lowpan_DRIVER_6LOWPAN_H
#define ttc_network_driver_6lowpan_DRIVER_6LOWPAN_H

/*{ ttc_network.h ***************************************************

 This source is published under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).
 See file LEGAL.txt in this software package for details.

 Authors: <Gregor Rebel>


 Description:

 Basic universal network support.
 Creation of flexible, reusable memory blocks for network packets.

}*/
//{ Defines/ TypeDefs ****************************************************

// These shall be defined somewhere before

#ifndef TTC_ASSERT_NETWORK    // any previous definition set (Makefile)?
#define TTC_ASSERT_NETWORK 1  // string asserts are enabled by default
#endif
#if (TTC_ASSERT_NETWORK == 1)  // use Assert()s in NETWORK code (somewhat slower but alot easier to debug)
  #define Assert_Network(Condition, ErrorCode) Assert(Condition, ErrorCode)
#else  // us no Assert()s in NETWORK code (somewhat smaller + faster, but crashes are hard to debug)
  #define Assert_Network(Condition, ErrorCode)
#endif

#define PRINTF(...)
#define PRINT6ADDR(addr)
#define PRINTLLADDR(addr)

//} Defines
//{ Includes *************************************************************

#include "../ttc_network_types.h"
#include "../ttc_memory.h"
#include "../ttc_task.h"
#include "6lowpan_net_packetbuf.h"
#include "6lowpan_rime_rimeaddr.h"
#include "6lowpan_mac_mac.h"
#include "6lowpan_net_netstack.h"

//} Includes
//{ Structures/ Enums ****************************************************

typedef struct {
    u8_t Unused;
} ttc_network_6lowpan_config_t;

//} Structures/ Enums
//{ DRIVER interface to ttc_network.h

#define DRIVER_ttc_network_load_defaults(Config) ttc_network_driver_6lowpan_load_defaults(Config)

//}
//{ Function prototypes **************************************************

/** loads all defaults parameter on the network structures
 * @return  == 0:       configuration was loaded successfully
 */
void ttc_network_driver_6lowpan_load_defaults(ttc_network_config_t* Config);

/** basic network intitialization
 */
void ttc_network_driver_6lowpan_prepare();

/** reset the network interface
 * @param Network_Interface     device reference to reset
 * @return                      != NULL: pointer to struct ttc_spi_generic_t
 */
void ttc_network_driver_6lowpan_reset(void);

/** deactivate the network interface
 * @param Network_Interface     device reference to reset
 * @return                      != NULL: pointer to struct ttc_spi_generic_t
 */
void ttc_network_driver_6lowpan_deinit(void);

/** Send a packet to the activated network/s
 * @param Buffer     memory location from which to read data
 * @return               == 0: Buffer has been sent successfully; != 0: error-code
 */
void ttc_network_driver_6lowpan_send_packet(mac_callback_t TaskFunction, void *ptr);





















#if 1==0 // { DEPRECATED
/* allocates a memory block that can store given amount of bytes + some extra data for sending data over a network.
 *
 * Network packets are mostly like memory blocks as described in ttc_memory.h.
 * They can store a limited amount of payload data + some extra data before and after the payload.
 * When a network packet is created for transmission, it normally is processed in several layers of
 * a network stack. Each layer adds some extra data before the payload (called header) and after the
 * payload (called footer). When the packet build is complete, it is handed over to the hardware
 * to transmit it. For this final stage, it is fastest if the final packet including all of its
 * headers and footers builds one contiguos block in memory.
 * A smart network stack acvoids to copy data from the payload area as much as possible.
 * ttc_network_driver_6lowpan_packet_t allows to reserve extra space in before and after Payload[].
 * When a ttc_network_driver_6lowpan_packet_t enters the trans
 *
 * Note: All ttc_malloc() functions will call Assert_Halt_EC(ec_OutOfMemory) if allocation fails.
 *
 * @param Size_Payload   AmountBytes of bytes to be allocated for Payload[]
 * @param Size_Header    AmountBytes of bytes to be extra allocated for packet header (before Payload[])
 * @param Size_Footer    AmountBytes of bytes to be extra allocated for packet footer (after Payload[])
 * @param Hint           argument passed to releaseBuffer() to allow fast release of buffers from different pools by single function
 * @param releaseBuffer  pointer to function that will take back ownership of block
 * @return               pointer to newly allocated packet
 */
ttc_network_driver_6lowpan_packet_t* ttc_network_driver_6lowpan_alloc_packet(u16_t Size_Payload, u8_t Size_Header, u8_t Size_Footer, u8_t Hint, void (*releaseBuffer)(ttc_network_driver_6lowpan_packet_t* Packet));

/* returns given packet to its creator by calling the stored release function
 *
 * @param Packet         instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 */
void ttc_network_driver_6lowpan_release_packet(ttc_network_driver_6lowpan_packet_t* Packet);

/* resets pointer in given packet back to empty state
 *
 * @param Packet         instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 */
void ttc_network_driver_6lowpan_reset_packet(ttc_network_driver_6lowpan_packet_t* Packet);

/* moves header pointer backward to allow prepending given amount of bytes
 *
 * Note: Will Assert if allocated header is exceeded!
 *
 * @param Packet     instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 * @param Size       amount of extra bytes to reserve for additional header
 */
void ttc_network_driver_6lowpan_add_header(ttc_network_driver_6lowpan_packet_t* Packet, u8_t Size);

/* moves footer pointer forward to allow appending given amount of bytes
 *
 * Note: Will Assert if allocated footer is exceeded!
 *
 * @param Packet        instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 * @param Size          amount of extra bytes to reserve for additional header
 * @param PacketMaxSize = Size_Payload + Size_Header + Size_Footer as given to ttc_network_driver_6lowpan_alloc_packet() before
 */
void ttc_network_driver_6lowpan_add_footer(ttc_network_driver_6lowpan_packet_t* Packet, u8_t Size);

/* moves header pointer forward to remove given amount of bytes from header
 *
 * Note: Will Assert if allocated header is exceeded!
 *
 * @param Packet     instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 * @param Size       amount bytes to remove from header
 */
void ttc_network_driver_6lowpan_del_header(ttc_network_driver_6lowpan_packet_t* Packet, u8_t Size);

/* moves footer pointer backward to remove given amount of bytes from footer
 *
 * Note: Will Assert if allocated footer is exceeded!
 *
 * @param Packet     instance of network packet allocated by ttc_network_driver_6lowpan_alloc_packet() before
 * @param Size       amount bytes to remove from footer
 */
void ttc_network_driver_6lowpan_del_footer(ttc_network_driver_6lowpan_packet_t* Packet, u8_t Size);

#endif // DEPRECATED }


//} Function prototypes

#endif //ttc_network_driver_6lowpan_H
