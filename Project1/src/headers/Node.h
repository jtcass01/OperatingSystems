#ifndef NODE
#define NODE

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* User Created Headers */
#include "Node.h"
#include "constants.h"

typedef struct NodeT {
	char *word;
	int count;
	struct NodeT *nextNode;
	struct NodeT *previousNode;
} Node;

Node* create_node(char *);

void delete_node(Node *);

void print_node(Node *);

void copy_node(Node *, Node *);

int compare_node_by_word(Node *, Node *);

void log_node(Node *, FILE *);

#endif