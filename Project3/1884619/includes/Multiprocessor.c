#include "../headers/Multiprocessor.h"

void create_map_threads(char *directory_path, int bufferSize) {
	// Retrieve file_list and store in a dll.
	DoublyLinkedList *file_list = dll_create();
	retrieve_file_list(file_list, directory_path);

	#if DEBUG
		printf("(M %s) : Creating a sender and working threads for file_list: ", directory_path); dll_print(file_list);
	#endif

	// Create a buffer and semaphores for communication between sender and workers
	DoublyLinkedList *dll_buffer = dll_create();
	sem_t full;
	sem_t empty;
	pthread_mutex_t mutex;

	// Create and initialize semaphores
	sem_init(&empty, 0, bufferSize); // The whole buffer begins empty
	sem_init(&full, 0, 0);					 // None of the buffer is full
	pthread_mutex_init(&mutex, NULL);

	// Create worker threads.
	Work *workers[file_list->size];
	Node *current_file = file_list->head;
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		//Create worker thread with given work load
		workers[thread_index] = work_create(dll_buffer, bufferSize, current_file->word, &empty, &full, &mutex);
		create_pThread(&(workers[thread_index]->thread), NULL, do_work, workers[thread_index]);

		current_file = current_file->nextNode;
	}

	// Create sender thread.
	Sender *sender = sender_create(dll_buffer, &empty, &full, &mutex);
	create_pThread(&(sender->thread), NULL, send_items, sender);

	// Join worker threads.
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		join_pThread(workers[thread_index]->thread, NULL);
	}

	#if DEBUG
		printf("(M %s) : Worker threads joined... locking mutex\n", directory_path);
	#endif

	lock_pThread_mutex(&mutex);
	dll_buffer->done = 1;
	unlock_pThread_mutex(&mutex);

	#if DEBUG
		printf("(M %s) : dll_buffer done flag set.  Mutex is unlocked. Waiting on sender.\n", directory_path);
		printf("(M %s) : Posting to full to possibly free up sender.\n" , directory_path);
	#endif

	sem_post(&full);

	#if DEBUG
		printf("(M %s) : Done posting to full.\n", directory_path);
	#endif

	// Join sender thread.
	join_pThread(sender->thread, NULL);

	// Destroy created dlls
	#if DEBUG
		printf("(M %s) : Sender joined. Destroying dlls\n", directory_path);
	#endif

	dll_destroy(file_list);
	dll_destroy(dll_buffer);

	#if DEBUG
		printf("(M %s) : Destroying mutexes and semaphores\n", directory_path);
	#endif

	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	#if DEBUG
		printf("(M %s) : Ending create_map_threads.\n", directory_path);
	#endif
}

void create_map_processes(DoublyLinkedList *directoryPaths, int bufferSize) {

	#if DEBUG
		printf("I am the parent process (pid: %d).  Beginning to create %d processes to serve each directory path.\n\n", getpid(), directoryPaths->size);
		dll_print(directoryPaths);
	#endif

	// Initialize the parent process indicators to 0.  Start processes
	for (int process_index = 0; process_index < directoryPaths->size; process_index++) {
		if (fork() == 0) {
			#if DEBUG
				printf("I am the child with pid = %d and process_index = %d, from parent = %d, BEGINNING WORK.\n", getpid(), process_index, getppid());
			#endif

			// Do work with processes
			Node *process_node = dll_find_node_by_index(directoryPaths, process_index);
			#if DEBUG
				printf("Creating map threads for directory: %s\n", process_node->word);
			#endif

			create_map_threads(process_node->word, bufferSize);

			// exit child process
			#if DEBUG
				printf("I am the child with pid = %d and process_index = %d, from parent = %d, DONE with %s.\n", getpid(), process_index, getppid(), process_node->word);
			#endif

			delete_node(process_node);

			exit(0);
		}
	}

	wait(NULL); /* parent will wait for the children to complete */

	#if DEBUG
		printf("All children are complete.\n");
	#endif
}
