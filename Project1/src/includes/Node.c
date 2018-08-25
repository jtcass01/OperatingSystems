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

Node *create_node(char *string){
	Node *newNode = malloc(sizeof(Node));

	newNode->word = strdup(string);
	newNode->count = 1;
	newNode->nextNode = NULL;
	newNode->previousNode = NULL;

	return newNode;
}

void print_node(Node *node){
	printf("Address: %p, Word: %s, Word Count: %d, previousNode: %p, nextNode: %p\n", node, node->word, node->count, node->previousNode, node->nextNode);
}

void copy_node(Node *destination, Node *source) {
	strcpy(destination->word, source->word);
	destination->count = source->count;
	destination->nextNode = source->nextNode;
	destination->previousNode = source->previousNode;
}

void swap_nodes(Node *node1, Node *node2){
	Node* tmp = create_node("tmp");

	copy_node(tmp, node1);

	printf("\n\ntmp: ");
	print_node(tmp);
	printf("node1: ");
	print_node(node1);
	printf("node2: ");
	print_node(node2);

	if (node2->previousNode == node1) {
		// Move Node 1 to Node 2's place
		if(node2->nextNode != NULL) {
			node2->nextNode->previousNode = node1;
		}

		node1->nextNode = node2->nextNode;
		node1->previousNode = node2;

		// Move Node 2 to Node 1's place
		if(tmp->previousNode != NULL) {
			tmp->previousNode->nextNode = node2;
		}

		node2->previousNode = tmp->previousNode;
		node2->nextNode = node1;
	} else if (node2->nextNode == node1) {
		// Move Node 1 to Node 2's place
		if(node2->previousNode != NULL) {
			node2->previousNode->nextNode = node1;				
		}

		node1->nextNode = node2;
		node1->previousNode = node2->previousNode;

		// Move Node 2 to Node 1's place
		if(tmp->nextNode != NULL) {
			tmp->nextNode->previousNode = node2;
		}

		node2->nextNode = tmp->nextNode;
		node2->previousNode = node1;
	} else {
		// Move Node 1 to Node 2's place
		if(node2->previousNode != NULL) {
			node2->previousNode->nextNode = node1;				
		}
		if(node2->nextNode != NULL) {
			node2->nextNode->previousNode = node1;
		}
		node1->nextNode = node2->nextNode;
		node1->previousNode = node2->previousNode;

		// Move Node 2 to Node 1's place
		node2->nextNode = tmp->nextNode;
		node2->previousNode = tmp->previousNode;
		if(tmp->nextNode != NULL) {
			tmp->nextNode->previousNode = node2;
		}
		if(tmp->previousNode != NULL) {
			tmp->previousNode->nextNode = node2;
		}
	}



	printf("\n\ntmp: ");
	print_node(tmp);
	printf("node1: ");
	print_node(node1);
	printf("node2: ");
	print_node(node2);

	delete_node(tmp);

/*
	node1->nextNode = node2->nextNode;
	if(node2->nextNode != NULL) {
		node2->nextNode->previousNode = node1;
	}
	node1->previousNode = node2->previousNode;
	if(node2->previousNode != NULL) {
		node2->previousNode->nextNode = node1;
	}

	node2->nextNode = tmp->nextNode;
	if(tmp->nextNode != NULL) {
		tmp->nextNode->previousNode = node2;
	}
	node2->previousNode = tmp->previousNode;
	if(tmp->previousNode != NULL) {
		tmp->previousNode->nextNode = node2;
	}*/
}

void delete_node(Node *node){
	free(node->word);
	free(node);
}