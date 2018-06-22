#define INIT_BUCKETS 100
#define TRUE 1
#define EMPTY 0

typedef unsigned long key_t;
typedef unsigned long value_t;
typedef unsigned long capacity_t;
typedef unsigned long hash_index_t;

typedef struct {
    key_t key;
    value_t value;
} hash_item_t;

typedef struct {
    hash_item_t* items;
    capacity_t capacity;
    capacity_t num_items;
} hash_table_t;

hash_table_t* ht_create();
int ht_insert (hash_table_t* ht, hash_item_t item);
value_t ht_lookup (hash_table_t* ht, key_t key);
