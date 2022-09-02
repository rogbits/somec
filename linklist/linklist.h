#ifndef C_LINKLIST_H
#define C_LINKLIST_H

typedef struct list {
	struct list_node* head;
} list;

typedef struct list_node {
	void* item;
	struct list_node* next;
} list_node;

list* make_list();

void free_list(list* l);

void list_insert(list* l, void* item);

void list_remove(list* l, list_node* target);

void* list_next_item(void** p);

#endif