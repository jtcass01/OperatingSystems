/*
** File:         Node.c
** Author:       Jacob Taylor Cassady
** Description:
** Last Updated: 8/22/18
*/

#include "../headers/Node.h"

Node *create_node(char *string){
	Node *newNode = malloc(sizeof(Node));

	newNode->word = strdup(string);
	newNode->count = 1;
	newNode->nextNode = NULL;
	newNode->previousNode = NULL;

	return newNode;
}


Node *create_node_from_buffer(char *buffer, int char_count) {
	Node *newNode = malloc(sizeof(Node));

	newNode->word = strndup(buffer, char_count);
	newNode->count = 1;
	newNode->nextNode = NULL;
	newNode->previousNode = NULL;

	return newNode;
}

void delete_node(Node *node){
	free(node->word);
	free(node);
}


void print_node(Node *node){
	if(node == NULL) {
		printf("This is a NULL node.  Cannot print.\n");
	} else {
		printf("Address: %p, Word: %s, Word Count: %d, previousNode: %p, nextNode: %p\n", node, node->word, node->count, node->previousNode, node->nextNode);
	}
}


void copy_node(Node *destination, Node *source) {
	free(destination->word);
	destination->word = strdup(source->word);
	destination->count = source->count;
	destination->nextNode = source->nextNode;
	destination->previousNode = source->previousNode;
}


int compare_node_by_word(Node *node1, Node *node2) {
	#if DEBUG
		printf("\nComparing nodes by word...\n");
		printf("Node1: ");
		print_node(node1);

		printf("Node2: ");
		print_node(node2);

		printf("Result: %d\n", strcmp(node1->word, node2->word));
	#endif

	return strcmp(node1->word, node2->word);
}


void log_node(Node *node, FILE *log_file) {
	fprintf(log_file, "%s,%d", node->word, node->count);
}
