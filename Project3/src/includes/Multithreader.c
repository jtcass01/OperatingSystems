#include "../headers/Multithreader.h"

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

void lock_pThread(pthread_mutex_t *mutex) {
	int rc = pthread_mutex_lock(mutex);
	assert(rc == 0);
}

void unlock_pThread(pthread_mutex_t *mutex) {
	int rc = pthread_mutex_unlock(mutex);
	assert(rc == 0);
}

void create_map_threads(char *directory_path, int bufferSize) {
	DoublyLinkedList *file_list = dll_create();

	retrieve_file_list(file_list, directory_path);

	dll_print(file_list);

	// Create sender thread.
	pthread_t sender;
	create_pThread(&sender, NULL, sender_thread, "sender");

	// Create worker threads.
	Work *workers[file_list->size];
	pthread_mutex_t worker_lock = PTHREAD_MUTEX_INITIALIZER;
	Node *current_file = file_list->head;
	DoublyLinkedList *dll_buffer = dll_create();
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		//Create worker thread with given work load
		workers[thread_index] = work_create(dll_buffer, bufferSize, current_file->word, worker_lock);
		create_pThread(&(workers[thread_index]->thread), NULL, do_work, workers[thread_index]);

		current_file = current_file->nextNode;
	}

	// Join worker threads.
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		join_pThread(workers[thread_index]->thread, NULL);
	}

	// Join sender thread.
	join_pThread(sender, NULL);

	dll_print(dll_buffer);

	dll_destroy(file_list);
	dll_destroy(dll_buffer);
}