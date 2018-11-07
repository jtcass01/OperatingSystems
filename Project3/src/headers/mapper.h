#ifndef MAPPER
#define MAPPER

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


// Thread functions
void *do_work(void *);
void *send_items(void *);
void create_map_threads(char *, int);
void create_map_processes(DoublyLinkedList *, int);
void process_command_file(char *, int);


#endif