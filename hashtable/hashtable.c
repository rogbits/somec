#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"


hashtable* hashtable_create(int size) {
	hashtable* t = malloc(sizeof(hashtable));
	t->count = 0;
	t->size = size;
	t->items = malloc(sizeof(hashtable_item*) * size);
	t->lists = malloc(sizeof(list*) * size);
	for (int i = 0; i < size; i++) {
		t->items[i] = NULL;
		t->lists[i] = NULL;
	}

	return t;
}

void hashtable_free(hashtable* t) {
	for (int i = 0; i < t->size; i++) {
		hashtable_item* item = t->items[i];
		list* list = t->lists[i];
		free(item);
		free_list(list);
	}

	free(t->items);
	free(t->lists);
	free(t);
}

unsigned long hash_int(int key) {
	return key * 2654435761;
}

unsigned long hash_string(char* str) {
	unsigned long hash = 0;
	int i = 0;
	while (*str) {
		hash += *str * pow(31, i++);
		str++;
	}

	return hash;
}

void* hashtable_get(hashtable* t, int i, int* int_key, char* str_key) {
	hashtable_item* item = t->items[i];
	if (item
	    && int_key != NULL
	    && item->int_key == *int_key) {
		return item->val;
	}
	if (item &&
	    str_key != NULL
	    && strcmp(item->string_key, str_key) == 0) {
		return item->val;
	}

	list* list = t->lists[i];
	if (!list) return NULL;

	void* next = list->head;
	void* p = list_next_item(&next);
	while (p) {
		item = (hashtable_item*) p;
		if (int_key != NULL
		    && item->int_key == *int_key) {
			return item->val;
		}
		if (str_key != NULL
		    && strcmp(item->string_key, str_key) == 0) {
			return item->val;
		}
		p = list_next_item(&next);
	}

	return NULL;
}

void* hashtable_int_key_get(hashtable* t, int key) {
	unsigned long hash = hash_int(key);
	int i = hash % t->size;
	return hashtable_get(t, i, &key, NULL);
}

void* hashtable_string_key_get(hashtable* t, char* key) {
	unsigned long hash = hash_string(key);
	int i = hash % t->size;
	return hashtable_get(t, i, NULL, key);
}

void hashtable_add(hashtable* t, int i, int* int_key, char* str_key, void* p) {
	hashtable_item* item = malloc(sizeof(hashtable_item));
	if (int_key) item->int_key = *int_key;
	item->string_key = str_key;
	item->val = p;

	if (t->items[i] == NULL) {
		t->items[i] = item;
		t->count++;
		return;
	}

	list* l = t->lists[i] ? t->lists[i] : make_list();
	t->lists[i] = l;
	list_insert(l, item);
	t->count++;
}

void hashtable_int_key_add(hashtable* t, int k, void* p) {
	hashtable_item* current = hashtable_int_key_get(t, k);
	if (current != NULL) {
		current->val = p;
		return;
	}

	unsigned long hash = hash_int(k);
	int i = hash % t->size;
	hashtable_add(t, i, &k, NULL, p);
}

void hashtable_str_key_add(hashtable* t, char* key, void* p) {
	hashtable_item* current = hashtable_string_key_get(t, key);
	if (current != NULL) {
		current->val = p;
		return;
	}

	unsigned long hash = hash_string(key);
	int i = hash % t->size;
	hashtable_add(t, i, NULL, key, p);
}
