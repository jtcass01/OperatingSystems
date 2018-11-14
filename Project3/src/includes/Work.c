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
	int semaphore_value;
	Work *work = args;
	printf("(W): %s BEGINING.\n", work->file_name);
	// Open work file. Rewind buffer to beginning.
	FILE *data_buffer = fopen(work->file_name, "r");
	rewind(data_buffer);

	char word[MAXWORDSIZE];

	while (fscanf(data_buffer, "%s", word) != EOF) {
		Node *word_node = create_node(word);
		printf("(W %s) Ready to place Node: ", work->file_name);
		print_node(word_node);


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

		printf("(W %s): Waiting on empty...  ", work->file_name);
		sem_getvalue(work->empty, &semaphore_value);
		printf("Current empty sempahore_value: %i.\n", semaphore_value);

		sem_wait(work->empty);

		printf("(W %s): Done waiting on empty...  ", work->file_name);
		sem_getvalue(work->empty, &semaphore_value);
		printf("Current empty sempahore_value: %i.\n", semaphore_value);


		printf("(W %s): Locking mutex.\n", work->file_name);
		lock_pThread_mutex(work->mutex);
		printf("(W %s): Mutex locked.\n", work->file_name);

		// Insert work
		dll_insert_tail(work->dll_buffer, word_node);


		/*
		// Release lock, post to empty.
		printf("(W %s): unlocking mutex.\n", work->file_name);
		unlock_pThread_mutex(work->mutex);
		printf("(W %s): Posting to empty.\n", work->file_name);
		sem_post(work->empty);*/

		printf("(W %s): unlocking mutex.\n", work->file_name);
		unlock_pThread_mutex(work->mutex);
		printf("(W %s): mutex unlocked.\n", work->file_name);


		printf("(W %s): Posting to full...  ", work->file_name);
		sem_getvalue(work->full, &semaphore_value);
		printf("Current full sempahore_value: %i.\n", semaphore_value);

		sem_post(work->full);

		printf("(W %s): Finished posting to full.  ", work->file_name);
		sem_getvalue(work->full, &semaphore_value);
		printf("Current full sempahore_value: %i.\n", semaphore_value);
	}


	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	pthread_exit(0);
//	return NULL;
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
	sender->msq_connection = create_message_queue_connection("mapper.c", 1);

	#if DEBUG
		printf("Sender successfully allocated and intitialized.  Returning...\n");
	#endif

	return sender;
}


void *send_items(void *args) {
	Sender *sender = args;
	DoublyLinkedList *popped_nodes = dll_create();
	int done_flag = 0, semaphore_value;
	printf("(S): BEGINING.\n");

	while (!done_flag) {
		Node *retrieved_node;
/*		printf("(S): Locking mutex.\n");
		lock_pThread_mutex(sender->mutex);
		do {
			printf("(S): Unlocking mutex.\n");
			unlock_pThread_mutex(sender->mutex);

			printf("(S): Waiting on empty.\n");
			sem_wait(sender->empty);

			printf("(S): Locking mutex.\n");
			lock_pThread_mutex(sender->mutex);
		} while (sender->dll_buffer->size == 0);*/
		//wait on full

		printf("(S): Waiting on full.  ");
		sem_getvalue(sender->full, &semaphore_value);
		printf("Current full sempahore_value: %i.\n", semaphore_value);

		sem_wait(sender->full);

		printf("(S): Done waiting on full.  ");
		sem_getvalue(sender->full, &semaphore_value);
		printf("Current full sempahore_value: %i.\n", semaphore_value);

		//lock mutex
		printf("(S): locking mutex.\n");
		lock_pThread_mutex(sender->mutex);
		printf("(S): Mutex locked.\n");

		while(sender->dll_buffer->size > 0){
			// Pop a node off and send it across the message queue
			retrieved_node = dll_pop_head(sender->dll_buffer);

			printf("(S) : Sending retrieved node to message queue: "); print_node(retrieved_node);
			for(int i = 0; i < retrieved_node->count; i++) {
				send_node(sender->msq_connection, retrieved_node);
			}
			sem_post(sender->empty);
		}

		// Update done flag
		done_flag = sender->dll_buffer->done;

		/*
		// Release lock, post to full.
d		printf("(S): Unlocking mutex.\n");
		unlock_pThread_mutex(sender->mutex);
		printf("(S): Posting to full.\n");
		sem_post(sender->full);*/
		//Wait on full semaphore
		printf("(S): Unlocking mutex.\n");
		unlock_pThread_mutex(sender->mutex);
		printf("(S): mutex unlocked.\n");


		//post to full
		printf("(S): Posting to empty. ");
		sem_getvalue(sender->empty, &semaphore_value);
		printf("Current empty sempahore_value: %i.\n", semaphore_value);

		sem_post(sender->empty);

		printf("(S): Done posting to empty. ");
		sem_getvalue(sender->empty, &semaphore_value);
		printf("Current empty sempahore_value: %i.\n", semaphore_value);

		// Consume item
		printf("(S) : Node Retrieved = ");
		print_node(retrieved_node);
		delete_node(retrieved_node);
	}


	Node *stop_node = create_node("%%%STOPTIME%%%");
	printf("(S): DONE. Sending stop_node %s to reducer.\n", stop_node->word);
	send_node(sender->msq_connection, stop_node);
	delete_node(stop_node);


	dll_print(popped_nodes);
	dll_destroy(popped_nodes);

	sender_destroy(sender);

	pthread_exit(0);
	//	return NULL;
}


void sender_destroy(Sender *sender) {
	destroy_message_queue_connection(sender->msq_connection);
	free(sender);
}
