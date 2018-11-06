#ifndef WORK
#define WORK

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"

/* Struct definitions */
typedef struct {
	DoublyLinkedList *dll_buffer;
	int bufferSize;
	char *file_name;
	pthread_t thread;
	pthread_mutex_t lock;
} Work;

/* Function Prototypes */
Work *work_create(DoublyLinkedList *, int, char *, pthread_mutex_t);

void *do_work(Work *);

void work_destroy(Work *);

#endif