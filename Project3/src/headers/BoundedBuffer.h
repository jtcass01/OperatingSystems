#ifndef BOUNDED_BUFFER
#define BOUNDED_BUFFER

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* User Created Headers */
#include "constants.h"
#include "Node.h"

/* Struct Definitions */
typedef struct {
	Node *head;
	Node *tail;
	int size;
	int max_size;
} BoundedBuffer;

/* Function Prototypes */
BoundedBuffer *bb_create(void);
//Dynamically allocates memory for a BoundedBuffer, initializes the buffer's
//attributes and returns a pointer to the struct.

void bb_destroy(BoundedBuffer *);
// Dynamically deallocates memory stored within a DoublyLinkedList and each of it's nodes.

void bb_insert_tail(BoundedBuffer *, Node *);
// Inserts a node into the tail end of a BoundedBuffer.


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

void bb_print(DoublyLinkedList *);
// Prints information on a DoublyLinkedList and the nodes within.

#endif