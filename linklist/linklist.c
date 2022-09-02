#include <stdlib.h>
#include "linklist.h"
#include <stdio.h>

list* make_list() {
	list* l = malloc(sizeof(list));
	l->head = NULL;
	return l;
}

void free_list(list* l) {
	list_node* p = l->head;
	while (p) {
		list_node* next = p->next;
		free(p);
		p = next;
	}
	free(l);
}

list_node* make_list_node(void* item) {
	list_node* n = malloc(sizeof(list_node));
	n->item = item;
	n->next = NULL;
	return n;
}

void list_insert(list* l, void* item) {
	if (l->head == NULL) {
		l->head = make_list_node(item);
		return;
	}

	list_node* p = l->head;
	while (p->next)
		p = p->next;
	p->next = make_list_node(item);
}

void list_remove(list* l, list_node* target) {
	list_node** p = &l->head;
	while (*p != target) {
		p = &(*p)->next;
	}
	*p = target->next;
	free(target);
}

void* list_next_item(void** p) {
	if (*p == NULL) return NULL;
	list_node* tmp = (list_node*) *p;
	*p = tmp->next;
	return tmp->item;
}

