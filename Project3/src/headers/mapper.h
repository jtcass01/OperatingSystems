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
void process_command_file(char *, int);


#endif