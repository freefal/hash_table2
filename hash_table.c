#include <stdlib.h>
#include "hash_table.h"

int hash (int item) {
    return item;
}

hash_table_t* ht_create () {
    hash_item_t* items = calloc (INIT_BUCKETS, sizeof(hash_item_t));
    hash_table_t* ht = malloc (sizeof(hash_table_t));
    ht->items = items;
    ht->capacity = INIT_BUCKETS;
    ht->num_items = 0;
    return ht;
}

int ht_insert (hash_table_t* ht, hash_item_t item) {
    // Hash key to a non-zero value (0 means "no element") 
    hash_index_t index = (hash(item.key) % (ht->capacity-1)) + 1;
    long i = -1;
    while (TRUE) {
        i++;
        hash_item_t existing_item = ht->items[index+i];
        if (existing_item.key == 0) {
            ht->items[index] = item;
            ht->num_items++;
            break;
        }
        else if (existing_item.key == item.key) {
            ht->items[index] = item;
            break;
        }
    }       
    return 0;
}

value_t ht_lookup (hash_table_t* ht, key_t) {
    while (TRUE) {
        
    }
}
