#ifndef FILE_PARSER
#define FILE_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DoublyLinkedList.h"
#include "Node.h"
#include "constants.h"

void parse_and_merge_files(char *, char *);

void parse_file(DoublyLinkedList *, char *);

void add_words_from_line_to_list(DoublyLinkedList *, char *);

void get_word(char *, char *, long, long);

long get_line_size(char *);

int line_has_word(char *);

void print_data_line_info(char *);

#endif