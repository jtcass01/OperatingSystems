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
	pid_t process_indicators[directoryPaths->size];

	// DEBUG -- Display directory paths passed
	dll_print(directoryPaths);

	// Initialize the process indicators to 0.
	for (int process_index = 0; process_index < directoryPaths->size; process_index++) {
		process_indicators[process_index] = 0;
		process_indicators[process_index] = fork(); /* fork a child process */

		if (process_indicators[process_index] < 0) { /* error occurred */
			fprintf(stderr, "Fork Failed\n");
			exit(-1);
		}
		else if (process_indicators[process_index] == 0) { /* child process */
			printf("I am the child with pid = %d, n = %d\n", getpid(), process_indicators[process_index]);
			execlp("/bin/ls", "ls", NULL);
		}
		else { /* parent process */
			printf("I am the parent with pid = %d, n = %d\n", getpid(), process_indicators[process_index]);
			wait(NULL); /* parent will wait for the child to complete */
			printf("Child Complete\n");
			exit(0);
		}

		currentProcess = currentProcess->nextNode;

	}

}
