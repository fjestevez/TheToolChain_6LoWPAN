/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * @(#)$Id: process.h,v 1.17 2010/09/14 18:55:04 dak664 Exp $
 */

/**
 * \addtogroup sys
 * @{
 */

/**
 * \defgroup process Contiki processes
 *
 * A process in Contiki consists of a single \ref pt "protothread".
 *
 * @{
 */

/**
 * \file
 * Header file for the Contiki process interface.
 * \author
 * Francisco Estevez <fjestevez@fh-muenster.de>
 *
 */
#ifndef __PROCESS_H__
#define __PROCESS_H__

typedef unsigned char process_event_t;
typedef void *        process_data_t;
typedef unsigned char process_num_events_t;
static process_event_t lastevent;

/**
 * \name Return values
 * @{
 */

/**
 * \brief      Return value indicating that an operation was successful.
 *
 *             This value is returned to indicate that an operation
 *             was successful.
 */
#define PROCESS_ERR_OK        0
/**
 * \brief      Return value indicating that the event queue was full.
 *
 *             This value is returned from process_post() to indicate
 *             that the event queue was full and that an event could
 *             not be posted.
 */
#define PROCESS_ERR_FULL      1
/* @} */

#define PROCESS_NONE          NULL

#ifndef PROCESS_CONF_NUMEVENTS
#define PROCESS_CONF_NUMEVENTS 32
#endif /* PROCESS_CONF_NUMEVENTS */

#define PROCESS_EVENT_NONE            0x80
#define PROCESS_EVENT_INIT            0x81
#define PROCESS_EVENT_POLL            0x82
#define PROCESS_EVENT_EXIT            0x83
#define PROCESS_EVENT_SERVICE_REMOVED 0x84
#define PROCESS_EVENT_CONTINUE        0x85
#define PROCESS_EVENT_MSG             0x86
#define PROCESS_EVENT_EXITED          0x87
#define PROCESS_EVENT_TIMER           0x88
#define PROCESS_EVENT_COM             0x89
#define PROCESS_EVENT_MAX             0x8a

#define PROCESS_BROADCAST NULL
#define PROCESS_ZOMBIE ((struct process *)0x1)

/** @} */
/** @} */


#endif // __PROCESS_H__
