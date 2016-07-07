//#include <stdio.h>

#include "6lowpan_net_uip.h"

#include "6lowpan_adapt_memb.h"

#include "6lowpan_net_uip_packetqueue.h"

#define MAX_NUM_QUEUED_PACKETS 2
MEMB(packets_memb, struct uip_packetqueue_packet, MAX_NUM_QUEUED_PACKETS);

#define DEBUG 0
#if DEBUG
//#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*---------------------------------------------------------------------------*/
static void
packet_timedout(void *ptr)
{
  struct uip_packetqueue_handle *h = ptr;

  PRINTF("uip_packetqueue_free timed out %p\n", h);
  memb_free(&packets_memb, h->packet);
  h->packet = NULL;
}
/*---------------------------------------------------------------------------*/
void
uip_packetqueue_new(struct uip_packetqueue_handle *handle)
{
  PRINTF("uip_packetqueue_new %p\n", handle);
  handle->packet = NULL;
}
/*---------------------------------------------------------------------------*/
struct uip_packetqueue_packet *
uip_packetqueue_alloc(struct uip_packetqueue_handle *handle, clock_time_t lifetime)
{
  PRINTF("uip_packetqueue_alloc %p\n", handle);
  if(handle->packet != NULL) {
    PRINTF("alloced\n");
    return NULL;
  }
  handle->packet = memb_alloc(&packets_memb);
  if(handle->packet != NULL) {
    ctimer_set(&handle->packet->lifetimer, lifetime,
               packet_timedout, handle);
  } else {
    PRINTF("uip_packetqueue_alloc failed\n");
  }
  return handle->packet;
}
/*---------------------------------------------------------------------------*/
void
uip_packetqueue_free(struct uip_packetqueue_handle *handle)
{
  PRINTF("uip_packetqueue_free %p\n", handle);
  if(handle->packet != NULL) {
    ctimer_stop(&handle->packet->lifetimer);
    memb_free(&packets_memb, handle->packet);
    handle->packet = NULL;
  }
}
/*---------------------------------------------------------------------------*/
u8_t *
uip_packetqueue_buf(struct uip_packetqueue_handle *h)
{
  return h->packet != NULL? h->packet->queue_buf: NULL;
}
/*---------------------------------------------------------------------------*/
u16_t
uip_packetqueue_buflen(struct uip_packetqueue_handle *h)
{
  return h->packet != NULL? h->packet->queue_buf_len: 0;
}
/*---------------------------------------------------------------------------*/
void
uip_packetqueue_set_buflen(struct uip_packetqueue_handle *h, u16_t len)
{
  if(h->packet != NULL) {
    h->packet->queue_buf_len = len;
  }
}
/*---------------------------------------------------------------------------*/
