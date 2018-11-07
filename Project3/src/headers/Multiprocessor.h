#ifndef MULTIPROCESSOR
#define MULTIPROCESSOR

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "constants.h"
#include "FileParser.h"
#include "DoublyLinkedList.h"
#include "Multithreader.h"
#include "Node.h"
#include "Work.h"

void create_map_threads(char *, int);

void create_map_processes(DoublyLinkedList *, int);

#endif