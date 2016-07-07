#include "6lowpan_radio_serialradio.h"

buffer_t* TXHead = NULL;
buffer_t* RXHead = NULL;

/*---------------------------------------------------------------------------*/
static int
init(void)
{  
    u8_t MaxUSART = ttc_usart_get_max_logicalindex();
    Assert(MaxUSART > 0, ec_UNKNOWN); // no USARTs defined by board makefile!
    ttc_usart_errorcode_e UsartError = tue_UnknownError;

    if (USART1_INDEX <= MaxUSART) { // USART defined by board: initialize it
        ttc_usart_generic_t* Config = ttc_usart_get_configuration(USART1_INDEX);
        Assert(Config, ec_UNKNOWN);

        // change some settings
        Config->Flags.Bits.IrqOnRxNE = 1; // enable IRQ on Rx-buffer not empty
        Config->Char_EndOfLine = 13;      // packets end at carriage return

        if (0)
            Config->Flags.Bits.DelayedTransmits = 1; // all transmits are queued and sent in interrupt service routin parallel to this task
        else
            Config->Flags.Bits.DelayedTransmits = 0; // all transmits are blocking until data is send (can loose rx-data while waiting for transmit!)

        // register activity indicators (will be called from interrupt service routine!)
        //Config->activity_rx_isr = exu_activity_rx;
        //Config->activity_tx_isr = exu_activity_tx;

        UsartError = ttc_usart_init(USART1_INDEX); // note: first bytes might get lost until ttc_usart_register_receive()
        Assert(UsartError == tue_OK, ec_UNKNOWN);
    }

    TXMemPool = ttc_memory_pool_create(sizeof(buffer_t), 5);
    RXMemPool = ttc_memory_pool_create(sizeof(buffer_t), 5);

    if((UsartError == tue_OK) && (TXMemPool != NULL) && (RXMemPool != NULL))
        return 1;
    else return 0;
}
/*---------------------------------------------------------------------------*/
static int
prepare(const void *payload, unsigned short payload_len)
{
    if(!TXHead) {
        TXHead = (buffer_t*) ttc_memory_pool_block_get(TXMemPool);
        if(TXHead != NULL) {
            TXHead->Payload = payload;
            TXHead->Length = payload_len;
            TXHead->Next = NULL;
            return 1;
        }
        else return 0;
    }
    else {
        buffer_t* NewMessage = TXHead;
        while(NewMessage->Next != NULL)
            NewMessage = NewMessage->Next;

        NewMessage->Next = (buffer_t*) ttc_memory_pool_block_get(TXMemPool);
        if(NewMessage->Next != NULL) {
            NewMessage = NewMessage->Next;
            NewMessage->Payload = payload;
            NewMessage->Length = payload_len;
            NewMessage->Next = NULL;
            return 1;
        }
        else return 0;
    }
}
/*---------------------------------------------------------------------------*/
static int
transmit(unsigned short transmit_len)
{
  buffer_t* TempBuffer = TXHead;

      ttc_usart_send_string(USART1_INDEX, "Serial Radio TX Message: ", -1);
      ttc_usart_send_string(USART1_INDEX, TempBuffer->Payload, -1);
      ttc_usart_send_string(USART1_INDEX, "\n", -1);
      ttc_usart_flush_tx(USART1_INDEX);

      if(!RXHead) {
          RXHead = (buffer_t*) ttc_memory_pool_block_get(RXMemPool);
          if(RXHead != NULL) {
              RXHead->Payload = TempBuffer->Payload;
              RXHead->Length = TempBuffer->Length;
              RXHead->Next = NULL;
              TXHead = TXHead->Next;
              ttc_memory_pool_block_free((ttc_memory_from_pool_t*) TempBuffer);
              return RADIO_TX_OK;
          }
          else return RADIO_TX_ERR;
      }
      else {
          buffer_t* NewMessage = RXHead;
          while(NewMessage->Next != NULL)
              NewMessage = NewMessage->Next;

          NewMessage->Next = (buffer_t*) ttc_memory_pool_block_get(RXMemPool);
          if(NewMessage->Next != NULL) {
              NewMessage = NewMessage->Next;
              NewMessage->Payload = TempBuffer->Payload;
              NewMessage->Length = TempBuffer->Length;
              NewMessage->Next = NULL;
              TXHead = TXHead->Next;
              ttc_memory_pool_block_free((ttc_memory_from_pool_t*) TempBuffer);
                return RADIO_TX_OK;
          }
          else return RADIO_TX_ERR;
      }
}
/*---------------------------------------------------------------------------*/
static int
send(const void *payload, unsigned short payload_len)
{
  if(prepare(payload, payload_len))
      return transmit(payload_len);
  else return RADIO_TX_ERR;
}
/*---------------------------------------------------------------------------*/
static int
read(void *buf, unsigned short buf_len)
{
    if(RXHead != NULL) {
        buffer_t* TempBuffer = RXHead;
        buf = TempBuffer->Payload;
        buf_len = TempBuffer->Length;
        RXHead = RXHead->Next;
        ttc_memory_pool_block_free((ttc_memory_from_pool_t*) TempBuffer);
        return 1;
    }
    else return 0;
}
/*---------------------------------------------------------------------------*/
static int
channel_clear(void)
{
  return 1;
}
/*---------------------------------------------------------------------------*/
static int
receiving_packet(void)
{
    if(RXHead != NULL)
        return 1;
    else return 0;
}
/*---------------------------------------------------------------------------*/
static int
pending_packet(void)
{
    if(TXHead != NULL){
        transmit(TXHead->Length);
        return 1;
    }
    else return 0;
}
/*---------------------------------------------------------------------------*/
static int
on(void)
{
    return 1;
}
/*---------------------------------------------------------------------------*/
static int
off(void)
{
  return 0;
}
/*---------------------------------------------------------------------------*/
const struct radio_driver serialradio_driver =
  {
    init,
    prepare,
    transmit,
    send,
    read,
    channel_clear,
    receiving_packet,
    pending_packet,
    on,
    off,
  };
/*---------------------------------------------------------------------------*/
