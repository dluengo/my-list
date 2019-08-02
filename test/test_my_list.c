#include "my_list.h"

#define DEBUG 1

#include "my_log.h"

int Test_ListItem() {
    ListItem_t *item1, *item2;
    const int DATA1 = 0x01ec0ded;
    const int DATA2 = 0xdeadbeef;
    int *data1, *data2;
    int int_data1, int_data2;
    int ok = 1, err;

    Log_msg("Calling ListItem_create()...");
    item1 = ListItem_create();
    item2 = ListItem_create();
    if (item1 == item2) {
        Log_msg("Two ListItem_t created and seem to be pointing to the same memory.");
        ok = 0;
    }

    // Shall we use free(), ListItem_destroy() or let the memory leak?

    Log_msg("Calling ListItem_getData() on empty items...");
    data1 = ListItem_getData(item1);
    data2 = ListItem_getData(item2);
    if (data1 != NULL || data2 != NULL) {
        Log_msg("Data is not NULL in non-initialized ListItem_t");
        ok = 0;
    }

    Log_msg("Calling ListItem_setData() on empty items...");
    int_data1 = DATA1;
    int_data2 = DATA2;
    err = ListItem_setData(item1, &int_data1);
    if (err) {
        Log_msg("Error setting int_data1..");
        return 0;
    }

    err = ListItem_setData(item2, &int_data2);
    if (err) {
        Log_msg("Error setting int_data2..");
        return 0;
    }

    Log_msg("Calling ListItem_getData() on initialized ListItem_t");
    data1 = ListItem_getData(item1);
    data2 = ListItem_getData(item2);
    if (data1 == NULL || *data1 != DATA1) {
        Log_msg("Data contained in item1 is wrong");
        ok = 0;
    }

    if (data2 == NULL || *data2 != DATA2) {
        Log_msg("Data contained in item2 is wrong");
        ok = 0;
    }

    Log_msg("Calling ListItem_setData() on initialized ListItem_t");
    err = ListItem_setData(item1, &int_data2);
    if (err) {
        Log_msg("Error setting int_data2 in item1..");
        return 0;
    }

    err = ListItem_setData(item2, &int_data1);
    if (err) {
        Log_msg("Error setting int_data1 in item2..");
        return 0;
    }

    Log_msg("Calling ListItem_getData() again after swap...");
    data2 = ListItem_getData(item1);
    data1 = ListItem_getData(item2);
    if (data1 == NULL || *data1 != DATA1) {
        Log_msg("Data contained in item1 is wrong after swap");
        ok = 0;
    }

    if (data2 == NULL || *data2 != DATA2) {
        Log_msg("Data contained in item2 is wrong after swap");
        ok = 0;
    }

    Log_msg("Calling ListItem_destroy()...");
    ListItem_destroy(item1);
    ListItem_destroy(item2);
    return ok;
}

int Test_List() {
    List_t *list1;
    ListItem_t *item1, *item2, *item3;
    int nums[3] = {1,2,3};
    int data[3];
    int ok = 1;
    int size, err, i;

    // Create some lists.
    Log_msg("Calling List_create()...");
    list1 = List_create();
    if (list1 == NULL) {
        Log_msg("Error creating list1");
        return 0;
    }

    // Check they are empty.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 0) {
        Log_msg("Size of newly created lists is not 0");
        return 0;
    }

    // Try to get some item (error).
    Log_msg("Calling List_getItem() on empty list...");
    if (List_getItem(list1, 0) != NULL) {
        Log_msg("Error, empty list returned item");
        return 0;
    }

    // Add items to lists.
    Log_msg("Calling List_insertData()...");
    err = List_insertData(list1, &(nums[0]));
    err |= List_insertData(list1, &(nums[1]));
    err |= List_insertData(list1, &(nums[2]));
    if (err) {
        Log_msg("Errors inserting data into list");
        return 0;
    }

    // Check size of lists.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 3) {
        Log_msg("Error, list size is not 3. Aborting");
        return 0;
    }

    // Get some items.
    Log_msg("Calling List_getItem()...");
    item1 = List_getItem(list1, 0);
    item2 = List_getItem(list1, 1);
    item3 = List_getItem(list1, 2);
    if (item1 == NULL || item2 == NULL || item3 == NULL) {
        Log_msg("Error, one of the items inserted is NULL");
        return 0;
    }

    // Check the content of the items.
    data[0] = *(int *)ListItem_getData(item1);
    data[1] = *(int *)ListItem_getData(item2);
    data[2] = *(int *)ListItem_getData(item3);
    if (data[0] != 1 || data[1] != 2 || data[2] != 3) {
        Log_msg("Error, data recovered not expected");
        return 0;
    }

    // Remove some items.
    Log_msg("Calling List_removeByIndex()...");
    item1 = List_removeByIndex(list1, 1);
    if (item1 == NULL) {
        Log_msg("Error removing item from the list");
        return 0;
    }

    // Check size of lists.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 2) {
        Log_msg("Error, list size is not 2. Aborting");
        return 0;
    }

    // Add some items back.
    Log_msg("Calling List_insertData()...");
    err = List_insertData(list1, &(nums[1]));
    if (err) {
        Log_msg("Error inserting data back into the list.");
        return 0;
    }

    // Check size of lists.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 3) {
        Log_msg("Error, lize size is not 3.");
        return 0;
    }

    // Check the items in the list.
    item1 = List_getItem(list1, 0);
    item2 = List_getItem(list1, 1);
    item3 = List_getItem(list1, 2);
    if (item1 == NULL || item2 == NULL || item3 == NULL) {
        Log_msg("Error, one of the items is NULL");
        return 0;
    }

    data[0] = *(int *)ListItem_getData(item1);
    data[1] = *(int *)ListItem_getData(item2);
    data[2] = *(int *)ListItem_getData(item3);
    if (data[0] != 1 || data[1] != 3 || data[2] != 2) {
        Log_msg("Error, data recovered not expected after removing.");
        return 0;
    }

    // Remove all items.
    Log_msg("Calling List_removeByIndex()...");
    size = List_size(list1);
    for (i = 0; i < size; i++) {
        if (List_removeByIndex(list1, 0) == NULL) {
            Log_msg("Error while removing all items.");
            return 0;
        }
    }
    
    // Check size of lists.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 0) {
        Log_msg("Error, list supposed to be empty but it is not.");
        return 0;
    }
    
    // Add some items.
    Log_msg("Calling List_insertData()...");
    err = List_insertData(list1, &(nums[0]));
    err |= List_insertData(list1, &(nums[1]));
    err |= List_insertData(list1, &(nums[2]));
    if (err) {
        Log_msg("Error inserting items back to the list.");
        return 0;
    }
    
    // Check size of lists.
    Log_msg("Calling List_size()...");
    if (List_size(list1) != 3) {
        Log_msg("Error, size is not 3 after empty and insert.");
        return 0;
    }
    
    // Destroy items.
    Log_msg("Calling ListItem_destroy()...");
    ListItem_destroy(List_removeByIndex(list1, 0));
    ListItem_destroy(List_removeByIndex(list1, 0));
    ListItem_destroy(List_removeByIndex(list1, 0));
    
    // Destroy lists.
    Log_msg("Calling List_destroy()...");
    List_destroy(list1);

    return 1;
}

int main() {
    int ok;
    
    ok = Test_ListItem();
    ok |= Test_List();

    if (!ok) {
        Log_msg("Errors!!!");
    } else {
        Log_msg("*** Sucess ***");
    }

    return 0;
}

