#ifndef MULTITHREADER
#define MULTITHREADER

/* Compiler/OS Headers */
#include <pthread.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"
#include "Node.h"
#include "FileParser.h"

void create_map_threads(char *);

#endif