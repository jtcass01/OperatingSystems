/*
** File:         Multiprocessor.c
** Author:       Jacob Taylor Cassady
** Description:
*/

/* User Created Headers */
#include "../headers/Multiprocessor.h"

/* Function Defintions */
void create_map_processes(DoublyLinkedList *directoryPaths) {
	Node *currentProcess = directoryPaths->head;

	// DEBUG -- Display directory paths passed
	printf("I am the parent process (pid: %d).  Beginning to create %d processes to serve each directory path.\n\n", getpid() ,directoryPaths->size);
	dll_print(directoryPaths);

	// Initialize the parent process indicators to 0.  Start processes
	for (int process_index = 0; process_index < directoryPaths->size; process_index++) {
		if (fork() == 0) {
			// DEBUG -- Display process information
			printf("I am the child with pid = %d and process_index = %d, from parent = %d\n", getpid(), process_index, getppid());
			
			// Do work with processes

			// exit child process
			exit(0);
		}
	}

	wait(NULL); /* parent will wait for the children to complete */
}
