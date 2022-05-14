#define _CRTDBG_MAP_ALLOC
#include "HashTable.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void print_str(char* key, Pointer data)
{
	printf("key is: %s and data is: %s\n", key, (char*)data);
}

unsigned hf_1(char* key) 
{
	return 1;
}



int main()
{
	HashTable ht;
	//test collisions test

	//init test
	ht_init(&ht, 1, hf_1, 0);
	assert(ht.size == 1);
	assert(ht.hashfunc != 0);
	assert(ht.dtor == 0);

	ht_set(&ht, "Vasya", (Pointer)"333-45-67");
	ht_set(&ht, "Police", (Pointer)"02");


	//get test and set
	assert(!strcmp(ht_get(&ht, "Vasya"), "333-45-67"));
	assert(!strcmp(ht_get(&ht, "Police"), "02"));

	//traverse test
	ht_traverse(&ht, print_str);

	//has test
	assert(ht_has(&ht, "Police") == 1);
	assert(ht_has(&ht, "lul") == 0);

	//resize test
	ht_resize(&ht, 200);
	assert(ht.size == 200);

	//delete test
	ht_delete(&ht, "Police");
	assert(ht_has(&ht, "Vasya") == 1);
	assert(ht_has(&ht, "Police") == 0);


	ht_destroy(&ht);

	//test 2

	ht_init(&ht, 200, 0, 0);
	assert(ht.size == 200);
	assert(ht.hashfunc != 0);
	assert(ht.dtor == 0);

	ht_set(&ht, "Police", (Pointer)"02");
	ht_set(&ht, "Vasya", (Pointer)"333-45-67");
	ht_set(&ht, "Vasya1", (Pointer)"333-45-671");
	ht_set(&ht, "Vasya2", (Pointer)"333-45-672");
	ht_set(&ht, "Vasya3", (Pointer)"333-45-673");
	ht_set(&ht, "Vasya4", (Pointer)"333-45-674");

	printf("BEFORE RESIZE %g\n", ht_collision_ratio(&ht));

	//get test and set
	assert(!strcmp(ht_get(&ht, "Vasya"), "333-45-67"));
	assert(!strcmp(ht_get(&ht, "Police"), "02"));

	//traverse test
	ht_traverse(&ht, print_str);

	//has test
	assert(ht_has(&ht, "Police") == 1);
	assert(ht_has(&ht, "lul") == 0);

	//resize test
	ht_resize(&ht, 2000);
	assert(ht.size == 2000);
	printf("AFTER RESIZE %g\n", ht_collision_ratio(&ht));

	//delete test
	ht_delete(&ht, "Police");
	assert(ht_has(&ht, "Vasya") == 1);
	assert(ht_has(&ht, "Police") == 0);

	ht_destroy(&ht);

	assert(_CrtDumpMemoryLeaks() == 0);
	return 0;
}