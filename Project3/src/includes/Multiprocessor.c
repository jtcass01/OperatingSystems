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
	pid_t n;

    while(currentProcess != NULL) {
      n = fork(); /* fork a child process */

      if (n < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
      } else if (n == 0) { /* child process */
        printf("I am the child with pid = %d, n = %d\n", getpid(), n);
        return execlp("/bin/ls", "ls", NULL);
      } else { /* parent process */
        printf("I am the parent with pid = %d, n = %d\n", getpid(), n);
        wait(NULL); /* parent will wait for the child to complete */
        printf("Child Complete\n");
        exit(0);
      }

      currentProcess = currentProcess->nextNode;
    }
}
