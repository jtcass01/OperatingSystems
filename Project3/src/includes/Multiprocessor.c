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

    while(currentProcess != NULL) {
      currentProcess->id = fork(); /* fork a child process */

      if (currentProcess->id < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
      } else if (currentProcess->id == 0) { /* child process */
        printf("I am the child with pid = %d, n = %d\n", getpid(), currentProcess->id);
        return execlp("/bin/ls", "ls", NULL);
      } else { /* parent process */
        printf("I am the parent with pid = %d, n = %d\n", getpid(), currentProcess->id);
        wait(NULL); /* parent will wait for the child to complete */
        printf("Child Complete\n");
        exit(0);
      }

      currentProcess = currentProcess->nextNode;
    }
}
