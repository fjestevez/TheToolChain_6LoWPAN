
/*{ TemplateName::.c ************************************************

 Empty template for new c-files.
 Copy and adapt to your needs.

}*/

#include "example_ttc_network_driver_6lowpan.h"

//{ Global variables *************************************************

ttc_Port_t LEDA, LEDB;
bool LedState = 0;

const char* Message = "Hallo Welt";

//} Global variables
//{ Function definitions *************************************************

void example_ttc_network_driver_6lowpan_start(){
#ifdef TTC_LED1
    ttc_gpio_init_variable(&LEDA, TTC_LED1, tgm_output_push_pull);
#endif
#ifdef TTC_LED2
    ttc_gpio_init_variable(&LEDB, TTC_LED2, tgm_output_push_pull);
#else
    // no TTC_LEDB defined: use same LED
    LEDB = LEDA;
#endif

    ttc_network_config_t* NetConfig = ttc_network_get_configuration(1);
    NetConfig->LocalAddress           = 23;
    NetConfig->Protocol               = tntp_6lowpan;
    NetConfig->Stack                  = tnts_uip;
    ttc_network_register_receive(1, receivePacket);
    ttc_network_init(1);

    ttc_task_create(task_MAC_sender, "taskMACsender", 128,(void *) Message, 1, NULL);
}

void task_MAC_sender(void *TaskArgument) {
    const char* Message = (char*) TaskArgument;
    Base_t MessageLength = ttc_string_length16(Message, 1000);

    while(1) {
        ttc_network_send_broadcast_raw(1, Message, MessageLength);

        for (u8_t Repeat = 10; Repeat > 0; Repeat--) {
            ttc_network_node_t* Neighbour = ttc_network_get_neighbours(1);
            while (Neighbour) {
                ttc_network_send_direct_raw(1, Neighbour->Address, Message, MessageLength);
                Neighbour = Neighbour->ListItem->Next;
            }
            mSleep(1000);
        }
/*
        packetbuf_clear();
        packetbuf_copyfrom(Message, 10);
        ttc_network_send_packet(dummy_sent, NULL);
        */
    }
}
void receivePacket(ttc_network_packet_status* Status, u8_t* Buffer, Base_t Amount) {
    (void) Status;
    (void) Buffer;
    (void) Amount;

    // do something
}

/* DEPRECATED
void dummy_sent(void *ptr, int status, int num_tx){
    switch(status) {
      case MAC_TX_COLLISION:
        PRINTF("rime: collision after %d tx\n", num_tx);
        break;
      case MAC_TX_NOACK:
        PRINTF("rime: noack after %d tx\n", num_tx);
        break;
      case MAC_TX_OK:
        PRINTF("rime: sent after %d tx\n", num_tx);
        ttc_gpio_set_variable(&LEDA);
        LedState = 1;
        uSleep(1000000);
        break;
      case MAC_TX_ERR:
        ttc_gpio_set_variable(&LEDB);
        LedState = 1;
        uSleep(1000000);
      default:
        PRINTF("rime: error %d after %d tx\n", status, num_tx);
      }
}
*/


//} Function definitions
