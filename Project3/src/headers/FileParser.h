#ifndef FILE_PARSER
#define FILE_PARSER

/* Compiler/OS Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/* User Created Headers */
#include "DoublyLinkedList.h"
#include "Node.h"
#include "constants.h"

/* Function Prototypes */
void retrieve_file_list(DoublyLinkedList *, char *);

void parse_file(DoublyLinkedList *, char *, int);

void add_words_from_line_to_list(DoublyLinkedList *, char *, int);

void get_word(char *, char *, long, long);

int line_has_word(char *);

void print_data_line_info(char *);

#endif
