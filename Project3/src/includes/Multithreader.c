
#include "../headers/Multithreader.h"

void *worker_thread(void *arg) {
	char *id = arg;
	printf("(W): %s BEGINING.\n", id);

	printf("(W): %s DONE.", id);
	return NULL;
}

void *sender_thread(void *arg) {
	char *id = arg;
	printf("(S): %s BEGINING\n", id);

	printf("(S) %s: DONE\n", id);
	return NULL;
}

void create_pThread(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
	int rc = pthread_create(thread, attr, start_routine, arg);
	assert(rc == 0);
}

void join_pThread(pthread_t thread, void**value_ptr) {
	int rc = pthread_join(thread, value_ptr);
	assert(rc == 0);
}

void create_map_threads(char *directory_path) {
	DoublyLinkedList *file_list = dll_create();

	retrieve_file_list(file_list, directory_path);

	dll_print(file_list);

	// Create sender thread.
	pthread_t sender;
	create_pThread(&sender, NULL, sender_thread, "sender");

	// Create worker threads.
	pthread_t worker_threads[file_list->size];
	Node *current_file = file_list->head;
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		create_pThread(&worker_threads[thread_index], NULL, worker_thread, current_file->word);
		current_file = current_file->nextNode;
	}

	// Join worker threads.
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		join_pThread(worker_thread[thread_index], NULL);
	}

	// Join sender thread.
	join_pThread(sender, NULL);

	dll_destroy(file_list);
}