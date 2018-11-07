/*
** File:         Work.c
** Author:       Jacob Taylor Cassady
** Description:
*/

#include "../headers/Work.h"

/* Function Definitions */
Work *work_create(DoublyLinkedList *dll_buffer, int bufferSize, char *file_name, sem_t *empty, sem_t *full, pthread_mutex_t *mutex) {
	Work *work_load = malloc(sizeof(Work));

	if (work_load == NULL) {
		printf("Unable to allocate memory for Work.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for Work.  Initializing attributes...\n");
	#endif

	// Intialize attributes.
	work_load->dll_buffer = dll_buffer;
	work_load->bufferSize = bufferSize;
	work_load->file_name = strdup(file_name);
	work_load->empty = empty;
	work_load->full = full;
	work_load->mutex = mutex;

	#if DEBUG
		printf("Work successfully allocated and intitialized.  Returning...\n");
	#endif

	return work_load;
}

void *do_work(void *args) {
	Work *work = args;
	printf("(W): %s BEGINING.\n", work->file_name);
	// Open work file. Rewind buffer to beginning.
	FILE *data_buffer = fopen(work->file_name, "r");
	rewind(data_buffer);

	char word[MAXWORDSIZE];

	while (fscanf(data_buffer, "%s", word) != EOF) {
		Node *word_node = create_node(word);

		// Acquire lock, sleep if full.
		lock_pThread_mutex(work->mutex);
		do {
			unlock_pThread_mutex(work->mutex);
			sem_wait(work->full);
			lock_pThread_mutex(work->mutex);
		} while (work->dll_buffer->size == work->bufferSize);

		// Insert work
		dll_insert_tail(work->dll_buffer, word_node);

		// Release lock, post to empty.
		pthread_mutex_unlock(work->mutex);
		sem_post(work->empty);

		printf("(W): Node inserted\n");
	}


	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	return NULL;
}


void work_destroy(Work *work_load) {
	free(work_load->file_name);
	free(work_load);
}

Sender *sender_create(DoublyLinkedList *dll_buffer, sem_t *empty, sem_t *full, pthread_mutex_t *mutex) {
	Sender *sender = malloc(sizeof(Sender));

	if (sender == NULL) {
		printf("Unable to allocate memory for sender.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for Sender.  Initializing attributes...\n");
	#endif

	// Intialize attributes.
	sender->dll_buffer = dll_buffer;
	sender->empty = empty;
	sender->full = full;
	sender->mutex = mutex;

	#if DEBUG
		printf("Sender successfully allocated and intitialized.  Returning...\n");
	#endif

	return sender;
}


void *send_items(void *args) {
	Sender *sender = args;

	printf("(S): BEGINING.\n");

	while (sender->dll_buffer->done != 1) {
		// Acquire lock. Sleep if empty.
		pthread_mutex_lock(sender->mutex);
		do {
			pthread_mutex_unlock(sender->mutex);
			sem_wait(sender->empty);
			pthread_mutex_lock(sender->mutex);
		} while (sender->dll_buffer->size == 0);

		// Pop a node off
		Node *retrieved_node = dll_pop_head(sender->dll_buffer);
		// Do work with retrieved node
		if (retrieved_node != NULL) {
			print_node(retrieved_node);
			delete_node(retrieved_node);
		}

		// Release lock, post to full.
		pthread_mutex_unlock(sender->mutex);
		sem_post(sender->full);
	}


	printf("(S): DONE.\n");

	sender_destroy(sender);

	return NULL;
}


void sender_destroy(Sender *sender) {
	free(sender);
}