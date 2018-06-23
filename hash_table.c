#include <stdlib.h>
#include "hash_table.h"

void ht_resize (hash_table_t* ht) {
    capacity_t new_capacity = ht->capacity*2;
    hash_table_t* ht_new = ht_create(new_capacity);
    
    int i;
    for (i = 0; i < ht->capacity; i++) {
        if (ht->items[i].exists) {
           ht_insert(ht_new, ht->items[i]); 
        }
    }
    
    free(ht->items);
    ht->items = ht_new->items;
    ht->capacity = ht_new->capacity;
    ht->num_items = ht_new->num_items;
    return;
}

hash_index_t hash (key_t key) {
    return key;
}

hash_table_t* ht_create () {
    return ht_create_capacity(INIT_CAPACITY);
}

hash_table_t* ht_create_capacity (capacity_t init_capacity) {
    hash_item_t* items = calloc (INIT_CAPACITY, sizeof(hash_item_t));
    hash_table_t* ht = malloc (sizeof(hash_table_t));
    ht->items = items;
    ht->capacity = init_capacity;
    ht->num_items = 0;
    return ht;
}

int ht_insert (hash_table_t* ht, hash_item_t item) {
    // Hash key to a non-zero value (0 means "no element") 
    item.exists = 1;
    hash_index_t index = hash(item.key) % (ht->capacity);
    hash_index_t i = -1;
    while (true) {
        i++;
        hash_item_t existing_item = ht->items[index+i];
        if (!existing_item.exists) {
            ht->items[index] = item;
            ht->num_items++;
            break;
        }
        else if (existing_item.key == item.key) {
            ht->items[index] = item;
            break;
        }
    }
    if (ht->num_items > (ht->capacity/2))
        ht_resize(ht);
    return 0;
}

value_t ht_lookup (hash_table_t* ht, key_t key) {
    hash_index_t index = hash(key) % ht->capacity;
    hash_index_t i = -1;
    while (true) {
        i++;
        hash_item_t item = ht->items[(index+i) % ht->capacity];
        if (!item.exists)
            return EMPTY;
        else if (item.key == key) {
            return item.value;
        }
    }
}

