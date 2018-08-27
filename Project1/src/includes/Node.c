/*
** File:         Node.c
** Author:       Jacob Taylor Cassady
** Description: 
** Last Updated: 8/22/18
*/

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* User Created Headers */
#include "../headers/Node.h"
#include "../headers/constants.h"

Node *create_node(char *string){
	Node *newNode = malloc(sizeof(Node));

	newNode->word = strdup(string);
	newNode->count = 1;
	newNode->nextNode = NULL;
	newNode->previousNode = NULL;

	return newNode;
}

void print_node(Node *node){
	if(node == NULL) {
		printf("This is a NULL node.  Cannot print.\n");
	} else {
		printf("Address: %p, Word: %s, Word Count: %d, previousNode: %p, nextNode: %p\n", node, node->word, node->count, node->previousNode, node->nextNode);
	}
}

void copy_node(Node *destination, Node *source) {
	strcpy(destination->word, source->word);
	destination->count = source->count;
	destination->nextNode = source->nextNode;
	destination->previousNode = source->previousNode;
}

int compare_node_by_word(Node *node1, Node *node2) {
	if (DEBUG) {
		printf("\nComparing nodes by word...\n");
		printf("Node1: ");
		print_node(node1);
		
		printf("Node2: ");
		print_node(node2);

		printf("Result: %d\n", strcmp(node1->word, node2->word));
	}

	return strcmp(node1->word, node2->word);
}

void delete_node(Node *node){
	free(node->word);
	free(node);
}