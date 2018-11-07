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

/* Struct definitions */
typedef struct {
	pthread_t thread;
	DoublyLinkedList *dll_buffer;
	int bufferSize;
	char *file_name;
	sem_t *empty;
	sem_t *full;
	pthread_mutex_t *mutex;
} Work;

typedef struct {
	pthread_t thread;
	DoublyLinkedList *dll_buffer;
	sem_t *empty;
	sem_t *full;
	pthread_mutex_t *mutex;
} Sender;

/* Function Prototypes */
// Work Functions
Work *work_create(DoublyLinkedList *, char *, sem_t *, sem_t *, pthread_mutex_t *);
void *do_work(void *);
void work_destroy(Work *);

// Sender Functions
Sender *sender_create(DoublyLinkedList *, sem_t *, sem_t *, pthread_mutex_t *);
void *send_items(void *);
void sender_destroy(Sender *);

#endif