/*
** File:         Multiprocessor.c
** Author:       Jacob Taylor Cassady
** Description:
*/

/* User Created Headers */
#include "../headers/Multiprocessor.h"

/* Function Defintions */
void create_map_processes(DoublyLinkedList *directoryPaths) {
    pid_t *pid_array = initialize_pid_array(directoryPaths->size);

    for(unsigned int i = 0; i < directoryPaths->size; i++) {
      pid_array[i] = fork(); /* fork a child process */

      if (pid_array[i] < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
      } else if (pid_array[i] == 0) { /* child process */
        printf("I am the child with pid = %d, n = %d\n", getpid(), pid_array[i]);
        return execlp("/bin/ls", "ls", NULL);
      } else { /* parent process */
        printf("I am the parent with pid = %d, n = %d\n", getpid(), pid_array[i]);
        wait(NULL); /* parent will wait for the child to complete */
        printf("Child Complete\n");
        exit(0);
      }
    }
}

pid_t *initialize_pid_array(int array_size) {
  pid_t pid_array[array_size];

  for(unsigned int i = 0; i < array_size; i++) {
    pid_array[i] = 0;
  }

  return pid_array;
}
