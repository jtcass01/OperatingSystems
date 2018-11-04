#ifndef WORK
#define WORK

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* User Created Headers */
#include "constants.h"

/* Struct definitions */
typedef struct {
	DoublyLinkedList *bounded_buffer;
	char *file_name;
	pthread_t thread;
} Work;

/* Function Prototypes */
Work *work_create(DoublyLinkedList *, char *);

void work_destroy(Work *);

#endif