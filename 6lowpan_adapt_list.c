//
//  list.c
//  
//
//  Created by Francisco Estevez on 08/07/13.
//
//

#include "6lowpan_adapt_list.h"

/*void list_init(list_t list){
    const char* cad = "NWK-list";
    ttc_list_init(list, cad);
}*/

void * list_head(list_t list){
    return (void*) list->First;
}

void * list_pop (list_t list){
    return (void*) ttc_list_pop_front_single(list);
}

void * list_push(list_t list, void *item){
    ttc_list_item_t temp;
    ttc_list_item_t* aux = (ttc_list_item_t*)item;
    temp.Next = list->First;
    (*aux).Next = temp.Next;
    list->First = aux;
    return (void*) list->First;
}

void * list_chop(list_t list){
    ttc_list_item_t *it = list->First;
    ttc_list_item_t *temp = list->Last;
    int i, size = list->Size;
    for(i=0; i<size; i++){
        it = it->Next;
    }
    list->Last = it;
    return (void*) temp;
}

void   list_add(list_t list, void *item){
    ttc_list_push_back_single(list, (ttc_list_item_t*)item);
}

void list_remove(list_t list, void *item){
    ttc_list_item_t *it = list->First;
    ttc_list_item_t *prev = list->First;
    bool found = FALSE;
    while((it != list->Last) && !found){
        if(it == item){
            prev->Next = it->Next;
            found = TRUE;
        }
        
        *prev = *it;
        it = it->Next;
    }
}

int list_length(list_t list){
    return (int) ttc_list_size(list);
}

void * list_item_next(void *item){
    ttc_list_item_t* it = (ttc_list_item_t*)item;
    
    if(it->Next != NULL)
        return (void*) it->Next;
    else return NULL;
}
