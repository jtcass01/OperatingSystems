#ifndef MAPPER
#define MAPPER

#include <stdlib.h>
#include <stdio.h>

#include "constants.h"
#include "FileParser.h"
#include "DoublyLinkedList.h"
#include "Multiprocessor.h"

void process_command_file(char *, int);

// Thread functions
void create_map_threads(char *, int);
void *do_work(void *);
void *send_items(void *);


#endif