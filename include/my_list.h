#ifndef __MY_LIST__
#define __MY_LIST__

//----------------------------------------------------------

typedef struct list_item {
    struct list_item *prev, *next;
    void *data;
} ListItem_t;

/**
 * Creates a new list item.
 *
 * @return A pointer to the newly created item or NULL.
 */
ListItem_t * ListItem_create(void);

/**
 * Destroy a list item.
 *
 * @this: The item to be destroyed.
 */
void ListItem_destroy(ListItem_t *this);

/**
 * Set the data contained in this item.
 *
 * @this: The list item that will contain the data.
 * @data: A pointer to whatever data we want to hold on this item.
 * @return: 0 on success, non-zero otherwise.
 */
int ListItem_setData(ListItem_t *this, void *data);

/**
 * Get the data contained in this item.
 *
 * @this: The ListItem_t from where to get the data.
 * @return: A pointer to the data contained or NULL.
 */
void * ListItem_getData(ListItem_t *this);

//----------------------------------------------------------

typedef struct list {
    ListItem_t *head, *tail;
    unsigned int length;
} List_t;

/**
 * Creates an empty initialized list.
 *
 * @return A pointer to the newly created list or NULL;
 */
List_t * List_create(void);

/**
 * Initializes a list. Doesn't check if the list was already
 *
 * @this: The list to be destroyed.
 */
void List_destroy(List_t *this);

/**
 * Get the size of the list.
 *
 * @this: The list to which get the size.
 */
unsigned int List_size(List_t *this);

/**
 * Insert an item into the list. Use with caution.
 *
 * @this: The list to where insert the element.
 * @item: The item to insert in the list.
 * @return: 0 if the item was successfully inserted, 1 otherwise.
 */
int List_insertItem(List_t *this, ListItem_t *item);

/**
 * Insert some data into the list. The ListItem will be handled underneath.
 *
 * @this: The list to where insert the element.
 * @data: A pointer to the data to insert.
 * @return: 0 if the item was successfully inserted, 1 otherwise.
 */
int List_insertData(List_t *this, void *data);

/**
 * Remove an element from the list. Use with caution.
 *
 * @this: The list from where to remove the element.
 * @item: The item to remove from the list.
 * @return: 0 if the item was successfully removed, 1 otherwise.
 */
int List_removeItem(List_t *this, ListItem_t *item);

/**
 * Remove an element from the list based on index. Use with caution.
 *
 * @this: The list from where to remove the element.
 * @index: The index of the item to remove.
 * @return: A pointer to the element removed from the list or NULL.
 */
ListItem_t * List_removeByIndex(List_t *this, unsigned int index);

/**
 * Get an item from the list.
 *
 * @this: The list from where to get the item.
 * @index: The index of the item we want to get.
 * @return: A pointer to the item or NULL.
 */
ListItem_t * List_getItem(List_t *this, unsigned int index);

//TODO: Add List method that destroy the list destroying elements.

#endif

