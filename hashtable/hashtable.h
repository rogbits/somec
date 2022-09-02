#ifndef C_HASHTABLE_H
#define C_HASHTABLE_H

#include "../linklist/linklist.h"

typedef struct hashtable_item {
	unsigned int int_key;
	char* string_key;
	void* val;
} hashtable_item;

typedef struct hashtable {
	hashtable_item** items;
	list** lists;
	int size;
	int count;
} hashtable;

hashtable* hashtable_create(int size);

void hashtable_free(hashtable* t);

void hashtable_int_key_add(hashtable* t, int k, void* p);

void hashtable_str_key_add(hashtable* t, char* key, void* p);

void* hashtable_int_key_get(hashtable* t, int key);

void* hashtable_string_key_get(hashtable* t, char* key);

#endif