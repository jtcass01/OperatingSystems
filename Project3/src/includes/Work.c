/*
** File:         Work.c
** Author:       Jacob Taylor Cassady
** Description:
*/

#include "../headers/Work.h"

/* Function Definitions */
Work *work_create(DoublyLinkedList *dll_buffer, int bufferSize, char *file_name, pthread_mutex_t lock) {
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
	work_load->bufferSize = bufferSize;
	work_load->lock = lock;

	#if DEBUG
		printf("Work successfully allocated and intitialized.  Returning...\n");
	#endif

	return work_load;
}

void *do_work(Work *work) {
	printf("(W): %s BEGINING.\n", work->file_name);
	// Open work file. Rewind buffer to beginning.
	FILE *data_buffer = fopen(work->file_name, "r");
	rewind(data_buffer);

	char word[MAXWORDSIZE];

	while (fscanf(data_buffer, "%s", word) != EOF) {
		Node *word_node = create_node(word);

		if (work->dll_buffer->size >= work->bufferSize) {
			// wait until unlocked.
		}


		lock_pThread(&work->lock);
		dll_insert_tail(work->dll_buffer, word_node);
		unlock_pThread(&work->lock);
	}


	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	return NULL;
}

void work_destroy(Work *work_load) {
	free(work_load->file_name);
	free(work_load);
}
