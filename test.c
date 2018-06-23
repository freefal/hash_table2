#include <stdlib.h>
#include <time.h>
#include "hash_table.h"

#define ITERS 1000000ul

// Performance test hash table implementations
int main(void) {
	unsigned long micros = 0;
	float millis = 0.0;	
	clock_t start, end;
	hash_table_t* ht = ht_create();
	int i;
	printf("RAND_MAX %d\n", RAND_MAX);
	printf("Starting insertions\n");
	start = clock();
	for (i = 0; i < ITERS; i++) {
            printf("%d\n", i);
            fflush(stdout);
            key_t key = rand();
            value_t value = rand();
            hash_item_t item = { .key = key, .value = value };
	    ht_insert(ht, item);
	}
	end = clock();
	micros = end - start;
	millis = micros / 1000;
	printf("Took %fms to perform %lu iterations\n", millis, ITERS);
	
        unsigned long successful_lookups = 0;
        printf("Starting lookups\n");
	start = clock();
	for (i = 0; i < ITERS; i++) {
            key_t key = rand();
	    value_t value = ht_lookup(ht, key);
            if (value != EMPTY) {
                printf("{%lu, %lu}\n", key, value);
                successful_lookups++;
            }
	}
	end = clock();
	micros = end - start;
	millis = micros / 1000;
	printf("Took %fms to perform %lu lookups\n", millis, ITERS);
        printf("Successfully lookuped up %lu keys of %lu attempts\n", successful_lookups, ITERS);
	return 0;
}
