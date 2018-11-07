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
		/*
		// Acquire lock, sleep if full.
		printf("(W %s): Locking mutex.\n", work->file_name);
		lock_pThread_mutex(work->mutex);
		do {
			printf("(W %s): unlocking mutex.\n", work->file_name);
			unlock_pThread_mutex(work->mutex);

			printf("(W %s): Waiting on full...\n", work->file_name);
			sem_wait(work->full);

			printf("(W %s): Locking mutex.\n", work->file_name);
			lock_pThread_mutex(work->mutex);
		} while (work->dll_buffer->size == work->bufferSize);
		*/
		sem_wait(work->full);
		lock_pThread_mutex(work->mutex);

		// Insert work
		dll_insert_tail(work->dll_buffer, word_node);

		unlock_pThread_mutex(work->mutex);
		sem_post(work->empty);
		/*
		// Release lock, post to empty.
		printf("(W %s): unlocking mutex.\n", work->file_name);
		pthread_mutex_unlock(work->mutex);
		printf("(W %s): Posting to empty.\n", work->file_name);
		sem_post(work->empty);
		*/
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
	DoublyLinkedList *popped_nodes = dll_create();
	printf("(S): BEGINING.\n");

	int currentSize = 1;
//	while (i++ < 2) {
		// Acquire lock. Sleep if empty.
	while (currentSize != 0) {
		/*
		printf("(S): Locking mutex.\n");
		pthread_mutex_lock(sender->mutex);
		do {
			printf("(S): Unlocking mutex.\n");
			pthread_mutex_unlock(sender->mutex);

			printf("(S): Waiting on empty.\n");
			sem_wait(sender->empty);

			printf("(S): Locking mutex.\n");
			pthread_mutex_lock(sender->mutex);
		} while (sender->dll_buffer->size == 0);*/

		sem_wait(sender->empty);
		lock_pThread_mutex(sender->mutex);

		// Pop a node off
		Node *retrieved_node = dll_pop_head(sender->dll_buffer);
		currentSize = sender->dll_buffer->size;

		unlock_pThread_mutex(sender->mutex);
		sem_post(sender->full);

		/*
		// Release lock, post to full.
		printf("(S): Unlocking mutex.\n");
		pthread_mutex_unlock(sender->mutex);
		printf("(S): Posting to full.\n");
		sem_post(sender->full);*/

		// Consume item
		dll_insert_tail(popped_nodes, retrieved_node);
		printf("(S): Node popped -- Current popped list.\n");
		dll_print(popped_nodes);
		if (currentSize == 0) {
			printf("Popped all the nodes for now.");
		}
	}


	printf("(S): DONE.\n");

	dll_print(popped_nodes);
	dll_destroy(popped_nodes);

	sender_destroy(sender);

	return NULL;
}


void sender_destroy(Sender *sender) {
	free(sender);
}