#ifndef TTC_NETWORK_H
#define TTC_NETWORK_H

/*{ ttc_network.h ***************************************************

 This source is published under the GNU LESSER GENERAL PUBLIC LICENSE (LGPL).
 See file LEGAL.txt in this software package for details.

 Authors: <Gregor Rebel>


 Description:

 Basic universal network support.
 Creation of flexible, reusable memory blocks for network packets.

}*/
//{ Defines/ TypeDefs ****************************************************

// check amount of networks configured by Makefile
#ifdef TTC_NETWORK1
#ifdef TTC_NETWORK2
#ifdef TTC_NETWORK3
#ifdef TTC_NETWORK4
#ifdef TTC_NETWORK5
#define TTC_NETWORK_MAX 5
#else
#define TTC_NETWORK_MAX 4
#endif
#else
#define TTC_NETWORK_MAX 3
#endif
#else
#define TTC_NETWORK_MAX 2
#endif
#else
#define TTC_NETWORK_MAX 1
#endif
#else
#define TTC_NETWORK_MAX 0
#endif

#ifndef TTC_ASSERT_NETWORK    // any previous definition set (Makefile)?
#define TTC_ASSERT_NETWORK 1  // string asserts are enabled by default
#endif
#if (TTC_ASSERT_NETWORK == 1)  // use Assert()s in NETWORK code (somewhat slower but alot easier to debug)
  #define Assert_Network(Condition, ErrorCode) Assert(Condition, ErrorCode)
#else  // us no Assert()s in NETWORK code (somewhat smaller + faster, but crashes are hard to debug)
  #define Assert_Network(Condition, ErrorCode)
#endif

//} Defines
//{ Includes *************************************************************

#include "ttc_network_types.h"
#include "ttc_memory.h"
#ifdef EXTENSION_450_ttc_network_driver_6lowpan
#  include "network/ttc_network_driver_6lowpan.h"
#endif

//} Includes
//{ Function prototypes **************************************************

/** Prepares network-interface for operation. Must be called before any other function!
 */
void ttc_network_prepare();

/** Delivers configuration of indexed network
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 * @return configuration data of indexed network
 */
ttc_network_config_t* ttc_network_get_configuration(u8_t LogicalIndex);

/** loads default values for index network
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 **/
void ttc_network_load_defaults(u8_t LogicalIndex);
void DRIVER_ttc_network_load_defaults(ttc_network_config_t* Config);
#ifndef DRIVER_ttc_network_load_defaults
#  warning Missing implementation for DRIVER_ttc_network_load_defaults()
#  define DRIVER_ttc_network_load_defaults(Config)
#endif

/** initializes indexed network for current configuration
 *
 * Note: Network configuration must be set by ttc_network_get_configuration() before!
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 **/
void ttc_network_init(u8_t LogicalIndex);
#ifndef DRIVER_ttc_network_init
#  warning Missing implementation for DRIVER_ttc_network_init()
#  define DRIVER_ttc_network_init(Config)
#endif
/** sends data from given buffer via network to given target address
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 * @param Target        protocol address of target node
 * @param Buffer        memory location from which to read data
 * @param Amount         amount of bytes to send from Buffer[] (even zero bytes are sent)
 */
void ttc_network_send_direct_raw(u8_t LogicalIndex, ttc_network_address_t Target, u8_t* Buffer, Base_t Amount);
#ifndef DRIVER_ttc_network_send_direct_raw
#warning Missing implementation for DRIVER_ttc_network_send_direct_raw()
#define DRIVER_ttc_network_send_direct_raw(Config, Target, Buffer, Amount)
#endif

/** sends data from given buffer via network to all other nodes
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 * @param Buffer        memory location from which to read data
 * @param Amount        amount of bytes to send from Buffer[] (even zero bytes are sent)
 */
void ttc_network_send_broadcast_raw(u8_t LogicalIndex, u8_t* Buffer, Base_t Amount);

/** registers function to be called for every packet being received from network
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 * @param receivePacket function will be called whenever a valid packet has beed received
 */
void ttc_network_register_receive(u8_t LogicalIndex, void (*receivePacket)(ttc_network_packet_status* Status, u8_t* Buffer, Base_t Amount));

/** returns list of all known neighbour nodes
 *
 * @param LogicalIndex  1..TTC_NETWORK_MAX
 * @return  list of protocol adresses of neighbour nodes
 */
ttc_network_node_t* ttc_network_get_neighbours(u8_t LogicalIndex);
#ifndef DRIVER_ttc_network_get_neighbours
#  warning Missing implementation for DRIVER_ttc_network_get_neighbours()
#endif

//} Function prototypes

#endif //TTC_NETWORK_H
