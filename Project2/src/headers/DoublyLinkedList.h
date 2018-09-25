#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* User Created Headers */
#include "Process.h"
#include "constants.h"

typedef struct {
	Process *head;
	Process *tail;
	int size;
} DoublyLinkedList;


DoublyLinkedList *dll_create(void);
//Dynamically allocates memory for a DoublyLinkedList, initializes the list's
//attributes and returns a pointer to the struct.

void dll_destroy(DoublyLinkedList *);
// Dynamically deallocates memory stored within a DoublyLinkedList and each of it's nodes.

void dll_copy(DoublyLinkedList *, DoublyLinkedList *);
//

void dll_insert_tail(DoublyLinkedList *, Process *);
// Inserts a process into the tail end of a DoublyLinkedList.

void dll_insert_head(DoublyLinkedList *, Process *);
// Inserts a process into the head end of a DoublyLinkedList.

void dll_snip(DoublyLinkedList *, int);
// Curtails a DoublyLinkedList to a specific size.

void dll_delete_process_by_id(DoublyLinkedList *, int);
// Searches for a Process within a DoublyLinkedList using a pid identifier and deletes it if found.

Process *dll_find_process_by_id(DoublyLinkedList *, int);
// Searches for a Process within a DoublyLinkedList using a pid identifier.

Process *dll_find_minimum_process(DoublyLinkedList *, char *);
//

void dll_move_process(DoublyLinkedList *, DoublyLinkedList *, Process *);
//

void dll_swap_processes(DoublyLinkedList*, Process *, Process *);
// Swaps two processes.

void dll_insertion_sort(DoublyLinkedList *, char *);
// Sorts a DoublyLinkedList using the insertion sort algorithm.

void dll_print(DoublyLinkedList *);
// Prints information on a DoublyLinkedList and the processes within.

void dll_log(char *, DoublyLinkedList *);
// Logs process information from a DoublyLinkedList into a log specified by log_destiantion path.

#endif