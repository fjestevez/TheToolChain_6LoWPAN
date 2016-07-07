//
//  list.h
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//
#ifndef __LIST_NETWORK_H__
#define __LIST_NETWORK_H__

#include "../ttc_list.h"

#define list_t ttc_list_t*

#define LIST(name) \
    list_t name

#define LIST_STRUCT(name) \
    list_t name

#define LIST_STRUCT_INIT(struct_ptr, name)  \
    (struct_ptr)->name = ttc_list_create(name); \
    ttc_list_init((struct_ptr)->name, (struct_ptr)->name)

void * list_head(list_t list);
void * list_pop (list_t list);
void * list_push(list_t list, void *item);

void * list_chop(list_t list);

void   list_add(list_t list, void *item);
void   list_remove(list_t list, void *item);

int    list_length(list_t list);

void * list_item_next(void *item);

#endif /* __LIST_NETWORK_H__ */
