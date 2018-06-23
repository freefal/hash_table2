#include <stdbool.h>

#define INIT_CAPACITY 100
#define TRUE 1
#define EMPTY 0ul - 1

typedef unsigned long key_t;
typedef unsigned long value_t;
typedef unsigned long capacity_t;
typedef unsigned long hash_index_t;

typedef struct {
    bool exists;
    key_t key;
    value_t value;
} hash_item_t;

typedef struct {
    hash_item_t* items;
    capacity_t capacity;
    capacity_t num_items;
} hash_table_t;

hash_table_t* ht_create();
hash_table_t* ht_create_capacity(capacity_t init_capacity);
int ht_insert (hash_table_t* ht, hash_item_t item);
value_t ht_lookup (hash_table_t* ht, key_t key);
