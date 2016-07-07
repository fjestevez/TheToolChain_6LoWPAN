#ifndef UIP_PACKETQUEUE_H
#define UIP_PACKETQUEUE_H

#include "6lowpan_adapt_ctimer.h"
#include "6lowpan_net_uipopt.h"

struct uip_packetqueue_handle;

struct uip_packetqueue_packet {
  struct uip_ds6_queued_packet *next;
  u8_t queue_buf[UIP_BUFSIZE - UIP_LLH_LEN];
  u16_t queue_buf_len;
  ctimer lifetimer;
  struct uip_packetqueue_handle *handle;
};

struct uip_packetqueue_handle {
  struct uip_packetqueue_packet *packet;
};

void uip_packetqueue_new(struct uip_packetqueue_handle *handle);


struct uip_packetqueue_packet *
uip_packetqueue_alloc(struct uip_packetqueue_handle *handle, clock_time_t lifetime);


void
uip_packetqueue_free(struct uip_packetqueue_handle *handle);

u8_t *uip_packetqueue_buf(struct uip_packetqueue_handle *h);
u16_t uip_packetqueue_buflen(struct uip_packetqueue_handle *h);
void uip_packetqueue_set_buflen(struct uip_packetqueue_handle *h, u16_t len);


#endif /* UIP_PACKETQUEUE_H */
