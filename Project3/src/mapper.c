#include "headers/mapper.h"

sem_t empty;
sem_t full;
sem_t mutex;

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
			printf("(W): %s full waiting...\n", work->file_name);
			// Wait on empty and mutex.
			sem_wait(&empty);
			sem_wait(&mutex);

			// Insert work
			dll_insert_tail(work->dll_buffer, word_node);

			printf("(W): %s posting...\n", work->file_name);
			// Post to mutex and full.
			sem_post(&mutex);
			sem_post(&full);
		}
		else { // Previous entry was found.  Only need to wait on mutex.
			printf("(W): %s waiting...\n", work->file_name);
			sem_wait(&mutex);

			previous_entry->count++;

			printf("(W): %s posting...\n", work->file_name);
			sem_post(&mutex);
		}
	}


	printf("(W): %s DONE.\n", work->file_name);
	work_destroy(work);
	return NULL;
}


void *send_items(void *args) {
	Sender *sender = args;
	int tmp = 0;

	printf("(S): BEGINING.\n");

	while (tmp != -1) {
		printf("(S): waiting...\n");
		sem_wait(&full);
		sem_wait(&mutex);

		Node *retrieved_node = dll_pop_head(sender->dll_buffer);

		if (retrieved_node == NULL) {
			tmp = -1;
		}
		else {
			delete_node(retrieved_node);
		}

		printf("(S): posting...\n");
		sem_post(&mutex);
		sem_post(&empty);
	}


	printf("(S): DONE.\n");

	sender_destroy(sender);

	return NULL;
}

void create_map_threads(char *directory_path, int bufferSize) {
	// Retrieve file_list and store in a dll.
	DoublyLinkedList *file_list = dll_create();
	retrieve_file_list(file_list, directory_path);

#if DEBUG
	dll_print(file_list);
#endif

	// Create a buffer for communication between sender and workers
	DoublyLinkedList *dll_buffer = dll_create();

	// Create and initialize semaphores
	sem_init(&empty, 0, bufferSize);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);

	// Create worker threads.
	Work *workers[file_list->size];
	Node *current_file = file_list->head;
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		//Create worker thread with given work load
		workers[thread_index] = work_create(dll_buffer, current_file->word);
		create_pThread(&(workers[thread_index]->thread), NULL, do_work, workers[thread_index]);

		current_file = current_file->nextNode;
	}

	// Create sender thread.
	Sender *sender = sender_create(dll_buffer);
	create_pThread(&(sender->thread), NULL, send_items, sender);

	// Join worker threads.
	for (int thread_index = 0; thread_index < file_list->size; thread_index++) {
		join_pThread(workers[thread_index]->thread, NULL);
	}

	// Join sender thread.
	join_pThread(sender->thread, NULL);

	// Print file buffer
	dll_print(dll_buffer);

	// Destroy created dlls
	dll_destroy(file_list);
	dll_destroy(dll_buffer);
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
			printf("I am the child with pid = %d and process_index = %d, from parent = %d, DONE.\n", getpid(), process_index, getppid());
#endif

			exit(0);
		}
	}

	wait(NULL); /* parent will wait for the children to complete */
}

void process_command_file(char *commandFile, int bufferSize) {
	/*
	Function Description: The first step of the project is to
	Author: Jacob Taylor Cassady
	*/
	// Initialize DLL for holding each line of the command file
	DoublyLinkedList *directoryPaths = dll_create();

	// Parse the command file and store in DLL.  Print for DEBUG
	parse_file(directoryPaths, commandFile, MAXLINESIZE);

	// Create a process for each directory listed in the commandFile
	create_map_processes(directoryPaths, bufferSize);

	dll_destroy(directoryPaths);
}



int main(int argc, char *argv[]) {
	char *commandFile;
	int bufferSize;

	if (argc != 3) {
		printf("Invalid number of command line arguments.\n");

		return 1;
	} else {
		commandFile = *(argv + 1);
		bufferSize = atoi(*(argv + 2));
	}

	printf("\tcommandFile: %s\n\tbufferSize: %d\n", commandFile, bufferSize);

	process_command_file(commandFile, bufferSize);

	return 0;
}

