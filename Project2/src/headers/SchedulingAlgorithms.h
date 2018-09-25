#ifndef SCHEDULING_ALGORITHMS
#define SCHEDULING_ALGORITHMS

#include <stdio.h>

/* User Created Headers */
#include "DoublyLinkedList.h"
#include "Process.h"
#include "constants.h"

/* Function Prototypes */
void schedule_process(Process *, int *, int);

void first_come_first_serve(DoublyLinkedList *, DoublyLinkedList *);

void preemptive_priority(DoublyLinkedList *, DoublyLinkedList *, DoublyLinkedList *);

void update_process_lists(DoublyLinkedList *, DoublyLinkedList *, DoublyLinkedList *, int);

#endif