#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include "Node.h"

typedef struct {
	Node *head;
	Node *tail;
	int size;
} DoublyLinkedList;

DoublyLinkedList *dll_create(void);

void dll_insert_tail(DoublyLinkedList *, Node *);

void dll_insert_head(DoublyLinkedList *, Node *);

void dll_swap_nodes(DoublyLinkedList*, Node *, Node *);

void dll_insertion_sort(DoublyLinkedList *doublyList);

void dll_print(DoublyLinkedList *doublyList);

void dll_destroy(DoublyLinkedList *);

#endif