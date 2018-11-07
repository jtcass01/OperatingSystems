#ifndef WORK
#define WORK

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"
#include "Multithreader.h"

/* Struct definitions */
typedef struct {
	DoublyLinkedList *dll_buffer;
	char *file_name;
	pthread_t thread;
} Work;

typedef struct {
	DoublyLinkedList *dll_buffer;
	pthread_t thread;
} Sender;

/* Function Prototypes */
// Work Functions
Work *work_create(DoublyLinkedList *, char *);
void work_destroy(Work *);

// Sender Functions
Sender *sender_create(DoublyLinkedList *);
void sender_destroy(Sender *);

#endif