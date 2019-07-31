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
        Log_msg("Error setting int_data1. Aborting...");
        return 0;
    }

    err = ListItem_setData(item2, &int_data2);
    if (err) {
        Log_msg("Error setting int_data2. Aborting...");
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
        Log_msg("Error setting int_data2 in item1. Aborting...");
        return 0;
    }

    err = ListItem_setData(item2, &int_data1);
    if (err) {
        Log_msg("Error setting int_data1 in item2. Aborting...");
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

int main() {
    int ok;
    
    ok = Test_ListItem();

    if (!ok) {
        Log_msg("Errors!!!");
    }

    return 0;
}

