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
	sem_t empty;
	sem_t full;
	sem_t mutex;
} Work;

typedef struct {
	DoublyLinkedList *dll_buffer;
	pthread_t thread;
	sem_t empty;
	sem_t full;
	sem_t mutex;
} Sender;

/* Function Prototypes */
// Work Functions
Work *work_create(DoublyLinkedList *, int, char *, sem_t, sem_t, sem_t);
void *do_work(void *);
void work_destroy(Work *);

// Sender Functions
Sender *sender_create(DoublyLinkedList *, sem_t, sem_t, sem_t);
void *send_items(void *);
void sender_destroy(Sender *);

#endif