#include "my_list.h"
#include "my_log.h"

#include <stdlib.h>

ListItem_t * ListItem_create(void) {
    ListItem_t *new_item;

    new_item = malloc(sizeof(ListItem_t));
    if (new_item != NULL) {
        new_item->prev = new_item->next = new_item->data = NULL;
    }

    return new_item;
}

void ListItem_destroy(ListItem_t *this) {
    free(this);
    return;
}

int ListItem_setData(ListItem_t *this, void *data) {
    if (this == NULL) {
        Log_msg("this is NULL");
        return 1;
    }

    this->data = data;
    return 0;
}

//---------------------------------------------------------

List_t * List_create() {
    List_t *list;
    
    list = malloc(sizeof(List_t));
    if (list != NULL) {
        list->head = list->tail = NULL;
        list->length = 0;
    }

    return list;
}

void List_destroy(List_t *this) {
    free(this);
    return;
}

unsigned int List_size(List_t *this) {
    if (this != NULL) {
        return this->length;
    }

    return 0;
}

int List_insert(List_t *this, ListItem_t *item) {
    if (this == NULL) {
        Log_msg("this is NULL");
        return 1;
    }

    if (item == NULL) {
        Log_msg("item is NULL");
        return 1;
    }

    item->next = NULL;
    item->prev = this->tail;

    if (this->tail != NULL) {
        this->tail->next = item;
    }

    this->tail = item;

    if (this->length == 0) {
        this->head = item;
    }

    this->length++;
    return 0;
}

int List_remove(List_t *this, ListItem_t *item) {
    ListItem_t *iter;

    if (this == NULL) {
        Log_msg("this is NULL");
        return 1;
    }

    if (item == NULL) {
        Log_msg("item is NULL");
        return 1;
    }

    //TODO: O(n), can be improved to O(1).
    iter = this->head;
    while (iter != NULL) {
        if (iter == item) {
            if (item->prev != NULL) {
                item->prev->next = item->next;
            } else {
                this->head = item->next;
            }

            if (item->next != NULL) {
                item->next->prev = item->prev;
            } else {
                this->tail = item->prev;
            }

            item->prev = item->next = NULL;
            this->length--;
            return 0;
        }
    }

    return 1;
}

