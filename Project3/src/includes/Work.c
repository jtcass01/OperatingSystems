/*
** File:         Work.c
** Author:       Jacob Taylor Cassady
** Description:
*/

#include "../headers/Work.h"

/* Function Definitions */
Work *work_create(DoublyLinkedList *dll_buffer, int bufferSize, char *file_name) {
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

	#if DEBUG
		printf("Work successfully allocated and intitialized.  Returning...\n");
	#endif

	return work_load;
}

void *do_work(void *arg) {
	Work *work = arg;
	printf("(W): %s BEGINING.\n", work->file_name);



	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	return NULL;
}

void work_destroy(Work *work_load) {
	free(work_load->file_name);
	free(work_load);
}
