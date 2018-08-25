/*
** File:         test.c
** Author:       Jacob Taylor Cassady
** Description:  
** Last Updated: 8/22/18
*/

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* User Created Headers */
#include "../headers/DoublyLinkedList.h"
#include "../headers/Node.h"

#define DEBUG 0

DoublyLinkedList *dll_create(void){
	// Dynamically create the DoublyLinkedList structure
	DoublyLinkedList *doublyList = malloc(sizeof(DoublyLinkedList));

	// Initiate the attributes.
	doublyList->head = NULL;
	doublyList->tail = NULL;
	doublyList->size = 0;

	// Return the DoublyLinkedList structure
	return doublyList;
}

void dll_insert_tail(DoublyLinkedList *doublyList, Node *newNode) {
	if(doublyList->tail == NULL) {
		doublyList->head = newNode;
		doublyList->tail = newNode;
		doublyList->size = 1;
	} else {
		doublyList->tail->nextNode = newNode;
		newNode->previousNode = doublyList->tail;
		doublyList->tail = newNode;
		doublyList->size++;
	}
}

void dll_insert_head(DoublyLinkedList *doublyList, Node *newNode) {
	if(doublyList->head == NULL) {
		doublyList->head = newNode;
		doublyList->tail = newNode;
		doublyList->size = 1;
	} else {
		doublyList->head->previousNode = newNode;
		newNode->nextNode = doublyList->head;
		doublyList->head = newNode;
		doublyList->size++;
	}
}

void dll_swap_nodes(DoublyLinkedList *testList, Node *node1, Node *node2){
	assert(node1 != node2);

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

	if(node1->previousNode == NULL){
		testList->head = node1;
	} else if (node2->previousNode == NULL) {
		testList->head = node2;
	}

	if(node1->nextNode == NULL){
		testList->tail = node1;
	} else if (node2->nextNode == NULL) {
		testList->tail = node2;
	}
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


void dll_insertion_sort(DoublyLinkedList *doublyList) {
	if(doublyList->head == NULL) {
		printf("You attempted to sort an empty list.");
	} else {
		Node *minNode = doublyList->head;
		Node *currentNode = doublyList->head;
		Node *placeKeeper = doublyList->head;

		while(placeKeeper->nextNode != NULL){
			printf("PlaceKeeper: ");
			print_node(placeKeeper);

			while(currentNode->nextNode != NULL) {
				printf("Current PlaceKeeper comparator: ");
				print_node(currentNode->nextNode);
				if(strcmp(currentNode->nextNode->word, minNode->word) < 0) {
					minNode = currentNode->nextNode;
					printf("New minNode found: ");
					print_node(minNode);
				}

				currentNode = currentNode->nextNode;
			}

			if(strcmp(currentNode->nextNode->word, minNode->word) != 0) {
				swap_nodes(placeKeeper, minNode);

				placeKeeper = minNode->nextNode;
			} else {
				placeKeeper = placeKeeper->nextNode;
			}
		}
	}
}

void dll_print(DoublyLinkedList *doublyList) {
	printf("=== Printing Doubly Linked List of size: %d | memory address: %p ===\n", doublyList->size, doublyList->head);
 
 	if ( doublyList->head == NULL ) {
 		printf("This list is empty. It's head is NULL.\n");
 	} else {
	 	Node *currentNode = doublyList->head;
		Node *nextNode;

		while(currentNode != NULL){
			nextNode = currentNode->nextNode;
			print_node(currentNode);
			currentNode = nextNode;
		}
 	}
}

void dll_destroy(DoublyLinkedList *doublyList) {
	Node *currentNode = doublyList->head;
	Node *nextNode;

	while(currentNode != NULL){
		nextNode = currentNode->nextNode;
		delete_node(currentNode);
		currentNode = nextNode;
	}

	free(doublyList);
}