#ifndef FILE_PARSER
#define FILE_PARSER

/* Compiler/OS Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* User Created Headers */
#include "DoublyLinkedList.h"
#include "Process.h"
#include "constants.h"

/* Function Prototypes */
DoublyLinkedList *parse_process_file(char *, DoublyLinkedList *, int);

#endif