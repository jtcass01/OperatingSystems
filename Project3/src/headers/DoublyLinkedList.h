#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* User Created Headers */
#include "Node.h"
#include "constants.h"

typedef struct {
	Node *head;
	Node *tail;
	int size;
} DoublyLinkedList;


DoublyLinkedList *dll_create(void);
//Dynamically allocates memory for a DoublyLinkedList, initializes the list's
//attributes and returns a pointer to the struct.

void dll_destroy(DoublyLinkedList *);
// Dynamically deallocates memory stored within a DoublyLinkedList and each of it's nodes.

void dll_insert_tail(DoublyLinkedList *, Node *);
// Inserts a node into the tail end of a DoublyLinkedList.

void dll_insert_head(DoublyLinkedList *, Node *);
// Inserts a node into the head end of a DoublyLinkedList.

void dll_delete_node_by_word(DoublyLinkedList *, char *);
// Searches for a Node within a DoublyLinkedList using a word identifier and deletes it if found.

Node *dll_find_node_by_index(DoublyLinkedList *, int);
// Searches for a Node within a DoublyLinkedList by index.

Node *dll_find_node_by_word(DoublyLinkedList *, char *);
// Searches for a Node within a DoublyLinkedList using a word identifier.

void dll_swap_nodes(DoublyLinkedList*, Node *, Node *);
// Swaps two nodes.

void dll_insertion_sort(DoublyLinkedList *);
// Sorts a DoublyLinkedList using the insertion sort algorithm.

DoublyLinkedList *dll_merge_lists(DoublyLinkedList *, DoublyLinkedList *, DoublyLinkedList *);
// Sorts two lists using insertion sort and merges them after into a new DoublyLinkedList.

void dll_print(DoublyLinkedList *);
// Prints information on a DoublyLinkedList and the nodes within.

void dll_log(DoublyLinkedList *, char *);
// Logs node word and count information from a DoublyLinkedList into a log specified by log_destiantion path.

#endif