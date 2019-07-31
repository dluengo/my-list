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

void * ListItem_getData(ListItem_t *this) {
    if (this == NULL) {
        Log_msg("this is NULL");
        return NULL;
    }

    return this->data;
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

int List_removeItem(List_t *this, ListItem_t *item) {
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

ListItem_t * List_removeItemByIndex(List_t *this, unsigned int index) {
    ListItem_t *iter;
    int i;

    if (this == NULL) {
        Log_msg("this is NULL");
        return NULL;
    }

    if (index >= this->length) {
        Log_msg("index out of bounds");
        return NULL;
    }

    //TODO: We could optimize a bit checking if we are closer starting from
    // the tail.
    for (i = 0, iter = this->head; i < index; i++, iter = iter->next);

    if (iter->prev != NULL) {
        iter->prev->next = iter->next;
    } else {
        this->head = iter->next;
    }

    if (iter->next != NULL) {
        iter->next->prev = iter->prev;
    } else {
        this->tail = iter->prev;
    }

    iter->prev = iter->next = NULL;
    this->length--;
    return iter;
}

ListItem_t * List_getItem(List_t *this, unsigned int index) {
    ListItem_t *iter;
    int i;

    if (this == NULL) {
        Log_msg("this is NULL");
        return NULL;
    }

    if (index >= this->length) {
        Log_msg("index %d out of bounds", index);
        return NULL;
    }

    //TODO: We could optimize a bit checking if we are closer starting from
    // the tail.
    for (i = 0, iter = this->head; i < index; iter = iter->next, i++);

    return iter;
}

