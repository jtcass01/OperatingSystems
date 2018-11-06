/*
** File:         Work.c
** Author:       Jacob Taylor Cassady
** Description:
*/

#include "../headers/Work.h"

/* Function Definitions */
Work *work_create(DoublyLinkedList *dll_buffer, char *file_name, sem_t empty, sem_t full, sem_t mutex) {
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

		// Wait on empty and mutex.
		sem_wait(&(work->empty));
		sem_wait(&(work->mutex));

		// Insert work
		dll_insert_tail(work->dll_buffer, word_node);

		// Post to mutex and full.
		sem_post(&(work->mutex));
		sem_post(&(work->full));

	}


	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	return NULL;
}

void work_destroy(Work *work_load) {
	free(work_load->file_name);
	free(work_load);
}

Sender *sender_create(DoublyLinkedList *dll_buffer, sem_t empty, sem_t full, sem_t mutex) {
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

	printf("(S): DONE.\n");

	sender_destroy(sender);

	return NULL;
}

void sender_destroy(Sender *sender) {
	free(sender);
}