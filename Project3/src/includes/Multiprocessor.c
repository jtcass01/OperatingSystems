/*
** File:         Multiprocessor.c
** Author:       Jacob Taylor Cassady
** Description:
*/

/* User Created Headers */
#include "../headers/Multiprocessor.h"

/* Function Defintions */
void create_map_processes(DoublyLinkedList *directoryPaths, int bufferSize) {
	#if DEBUG
		printf("I am the parent process (pid: %d).  Beginning to create %d processes to serve each directory path.\n\n", getpid() ,directoryPaths->size);
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
