test_hash : hash_table.o test.o
	cc -o test_hash hash_table.o test.o

test.o : test.c
	cc -c test.c
hash_table.o : hash_table.c hash_table.c
clean :
	rm test_hash test.o hash_table.o
