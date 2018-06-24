#include <stdlib.h>
#include "hash_table.h"

void ht_resize (hash_table_t* ht) {
    //printf("start resize: %lu, %lu\n", ht->num_items, ht->capacity);
    //fflush(stdout);
    capacity_t new_capacity = ht->capacity * 2;
    hash_table_t* ht_new = ht_create_capacity(new_capacity);
    
    int i;
    //int count1 = 0;
    //int count2 = 0;
    for (i = 0; i < ht->capacity; i++) {
        //count2++;
        if (ht->items[i].exists) {
            //count1++;
            ht_insert(ht_new, ht->items[i]); 
        }
    }
    //printf("Iterated over %d\n items\n", count2);
    //printf("Attempted to insert %d\n items\n", count1);
            
    free(ht->items);
    ht->items = ht_new->items;
    ht->capacity = ht_new->capacity;
    ht->num_items = ht_new->num_items;

    free(ht_new);
    //printf("end resize: %lu, %lu\n", ht->num_items, ht->capacity);
    //fflush(stdout);
    return;
}

hash_index_t hash (key_t key) {
    return key;
}

hash_table_t* ht_create () {
    return ht_create_capacity(INIT_CAPACITY);
}

hash_table_t* ht_create_capacity (capacity_t init_capacity) {
    hash_item_t* items = calloc (init_capacity, sizeof(hash_item_t));
    hash_table_t* ht = malloc (sizeof(hash_table_t));
    ht->items = items;
    ht->capacity = init_capacity;
    ht->num_items = 0;
    return ht;
}

int ht_insert (hash_table_t* ht, hash_item_t item) {
    item.exists = 1;
    hash_index_t index = hash(item.key) % (ht->capacity);
    while (true) {
        hash_item_t current_item = ht->items[index];
        if (!current_item.exists) {
            ht->items[index] = item;
            ht->num_items++;
            break;
        }
        else if (current_item.key == item.key) {
            ht->items[index] = item;
            break;
        }
        index = (index + 1) % ht->capacity;
    }
    if (ht->num_items > (ht->capacity/2))
        ht_resize(ht);
    return 0;
}

value_t ht_lookup (hash_table_t* ht, key_t key) {
    hash_index_t index = hash(key) % ht->capacity;
    while (true) {
        hash_item_t item = ht->items[index];
        if (!item.exists)
            return EMPTY;
        else if (item.key == key) {
            return item.value;
        }
        index = (index + 1) % ht->capacity;
    }
}

