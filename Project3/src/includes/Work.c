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
		Node *previous_entry = dll_find_node_by_word(work->dll_buffer, word_node->word);

		if (previous_entry == NULL) { // If no previous entry, create a new one.  Must wait on empty and post to full
			// Wait on empty and mutex.
			sem_wait(&(work->empty));
			sem_wait(&(work->mutex));

			// Insert work
			dll_insert_tail(work->dll_buffer, word_node);

			// Post to mutex and full.
			sem_post(&(work->mutex));
			sem_post(&(work->full));
		} else { // Previous entry was found.  Only need to wait on mutex.
			sem_wait(&(work->mutex));

			previous_entry->count++;

			sem_post(&(work->mutex));
		}
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
	int tmp = 0;

	printf("(S): BEGINING.\n");

	while (tmp != -1) {
		sem_wait(&(sender->full));
		sem_wait(&(sender->mutex));

		Node *retrieved_node = dll_pop_head(sender->dll_buffer);

		if (retrieved_node == NULL) {
			tmp = -1;
		} else {
			delete_node(retrieved_node);
		}

		sem_post(&(sender->mutex));
		sem_post(&(sender->empty));
	}


	printf("(S): DONE.\n");

	sender_destroy(sender);

	return NULL;
}

void sender_destroy(Sender *sender) {
	free(sender);
}