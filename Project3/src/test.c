#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>

#include "headers/Multithreader.h"

int max;
int items;
int *buffer;

int use = 0;
int fill = 0;

sem_t empty;
sem_t full;
sem_t mutex;

#define CMAX (10)
int consumers = 1;

void do_fill(int value) {
	buffer[fill] = value;
	fill++;
	if (fill == max) {
		fill = 0;
	}
}

int do_get() {
	int tmp = buffer[use];
	use++;
	if (use == max) {
		use = 0;
	}
	return tmp;
}

void * producer(void *arg) {
	int i;
	for (i = 0; i < items; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);
		do_fill(i);
		sem_post(&mutex);
		sem_post(&full);
		printf("Producer - Item: %d is inserted\n", i);
	}


	// end case
	for (i = 0; i < consumers; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);
		do_fill(-1);
		sem_post(&mutex);
		sem_post(&full);
	}

	return NULL;
}


typedef struct {
	int id;
	pthread_t thread;
	sem_t *empty;
	sem_t *full;
	sem_t *mutex;
} Sender_t;

Sender_t *sender_t_create(int id, sem_t *empty, sem_t *full, sem_t *mutex) {
	Sender_t *sender = malloc(sizeof(Sender_t));

	if (sender == NULL) {
		printf("Unable to allocate memory for sender.\n");

		return NULL;
	}

#if DEBUG
	printf("Successfully Allocated memory for Sender_t.  Initializing attributes...\n");
#endif

	// Intialize attributes.
	sender->id = id;
	sender->empty = empty;
	sender->full = full;
	sender->mutex = mutex;

#if DEBUG
	printf("Sender_t successfully allocated and intitialized.  Returning...\n");
#endif

	return sender;
}

void *send_t_items(void *args) {
	Sender_t *sender = args;
	int id = sender->id;

	int tmp = 0;
	while (tmp != -1) {
		sem_wait(sender->full);
		sem_wait(sender->mutex);
		tmp = do_get();
		sem_post(sender->mutex);
		sem_post(sender->empty);
		if (tmp != -1) {
			printf("Consumer%d - Item: %d is extracted.\n", id, tmp);
		}
	}
	return NULL;
}

void sender_t_destroy(Sender_t *sender) {
	free(sender);
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "usage: %s <buffersize> <items> <consumers>\n", argv[0]);
		exit(1);
	}
	max = atoi(argv[1]);
	items = atoi(argv[2]);
	consumers = atoi(argv[3]);
	assert(consumers <= CMAX);

	buffer = (int *)malloc(max * sizeof(int));
	int i;
	Sender_t *senders[CMAX];

	for (i = 0; i < max; i++) {
		buffer[i] = 0;
	}

	sem_init(&empty, 0, max); // max are empty 
	sem_init(&full, 0, 0);    // 0 are full
	sem_init(&mutex, 0, 1);   // mutex

	pthread_t pid;

	create_pThread(&pid, NULL, producer, NULL);
	for (i = 0; i < consumers; i++) {
		senders[i] = sender_t_create(i, &empty, &full, &mutex);
		create_pThread(&(senders[i]->thread), NULL, send_t_items, senders[i]);
	}

	join_pThread(pid, NULL);
	for (i = 0; i < consumers; i++) {
		join_pThread((senders[i]->thread), NULL);
		sender_t_destroy(senders[i]);
	}

	return 0;
}
