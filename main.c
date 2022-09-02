#include <stdio.h>
#include "linklist/linklist.h"
#include "hashtable/hashtable.h"

void test_list(int target);
void test_hash_table();
void hr();

int main() {
	printf("list test 1\n");
	test_list(3);
	hr();
	printf("list test 2\n");
	test_list(8);
	hr();
	printf("testing hash table\n");
	test_hash_table();
	return 0;
}

void test_list(int target) {
	struct list* l = make_list();
	int nums[] = {1, 2, 3, 4, 5};
	int length = sizeof(nums) / sizeof(nums[0]);
	for (int i = 0; i < length; i++) list_insert(l, &nums[i]);

	int i = 0;
	void* next = l->head;
	void* item = list_next_item(&next);
	while (item) {
		i++;
		int* num = (int*) item;
		if (*num == target) {
			printf("found %d, num iter: %d\n", *num, i);
			break;
		}
		item = list_next_item(&next);
	}

	if (item == NULL)
		printf("could not find target, "
		       "num iter: %d\n", i);
}

void test_hash_table() {
	hashtable* t = hashtable_create(100);
	int int_keys[] = {42, 106, 711, 411, 311, 777, 123, 0, 1999};
	int int_vals[] = {55, 44, 121, 888, 906, 1982, 185, 6, 42};
	int length = sizeof(int_keys) / sizeof(int_keys[0]);
	for (int i = 0; i < length; i++) {
		printf("inserting k:%d, v:%d\n", int_keys[i], int_vals[i]);
		hashtable_int_key_add(t, int_keys[i], &int_vals[i]);
	}

	hr();
	for (int i = 0; i < length; i++) {
		int val = *(int*) hashtable_int_key_get(t, int_keys[i]);
		printf("retrieved k:%d, v:%d\n", int_keys[i], val);
	}

	hr();
	char* str_keys[] = {"one", "two", "three", "four", "five",
	                    "apple", "banana", "computer", "sun"};

	for (int i = 0; i < length; i++) {
		printf("inserting k:%s, v:%d\n", str_keys[i], int_vals[i]);
		hashtable_str_key_add(t, str_keys[i], &int_vals[i]);
	}

	hr();
	for (int i = 0; i < length; i++) {
		int val = *(int*) hashtable_string_key_get(t, str_keys[i]);
		printf("retrieved k:%s, v:%d\n", str_keys[i], val);
	}
}

void hr() {
	printf("----------\n");
}