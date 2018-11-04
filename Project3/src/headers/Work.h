#ifndef WORK
#define WORK

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"

/* Struct definitions */
typedef struct {
	DoublyLinkedList *dll_buffer;
	int bufferSize;
	char *file_name;
	pthread_t thread;
} Work;

/* Function Prototypes */
Work *work_create(DoublyLinkedList *, int, char *);

void *do_work(void *arg);

void work_destroy(Work *);

#endif