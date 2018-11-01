#ifndef MULTIPROCESSOR
#define MULTIPROCESSOR

/* Compiler/OS Headers */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"
#include "Node.h"

/* Function Prototypes */
void create_map_processes(DoublyLinkedList *);

pid_t *initialize_pid_array(int);

#endif
