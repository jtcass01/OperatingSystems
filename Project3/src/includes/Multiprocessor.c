/*
** File:         Multiprocessor.c
** Author:       Jacob Taylor Cassady
** Description:
*/

/* User Created Headers */
#include "../headers/Multiprocessor.h"

/* Function Defintions */
void create_map_processes(DoublyLinkedList *directoryPaths) {
	// DEBUG -- Display directory paths passed
	printf("I am the parent process (pid: %d).  Beginning to create %d processes to serve each directory path.\n\n", getpid() ,directoryPaths->size);
	dll_print(directoryPaths);

	// Initialize the parent process indicators to 0.  Start processes
	for (int process_index = 0; process_index < directoryPaths->size; process_index++) {
		if (fork() == 0) {
			// DEBUG -- Display process information
			printf("I am the child with pid = %d and process_index = %d, from parent = %d, BEGINNING WORK.\n", getpid(), process_index, getppid());
			
			// Do work with processes
			Node *process_node = dll_find_node_by_index(directoryPaths, process_index);
			printf("Creating map threads for directory: %s\n", process_node->word);
			create_map_threads(process_node->word);

			// exit child process
			printf("I am the child with pid = %d and process_index = %d, from parent = %d, DONE.\n", getpid(), process_index, getppid());
			exit(0);
		}
	}

	wait(NULL); /* parent will wait for the children to complete */
}
