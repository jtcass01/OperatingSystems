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
#include "../headers/constants.h"

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


void dll_delete_node_by_word(DoublyLinkedList *doublyList, char *word_of_interest) {
	Node *node_of_interest = dll_find_node_by_word(doublyList, word_of_interest);

	if (node_of_interest->nextNode != NULL && node_of_interest->previousNode != NULL){
		node_of_interest->nextNode->previousNode = node_of_interest->previousNode;
		node_of_interest->previousNode->nextNode = node_of_interest->nextNode;
	} else {
		if(node_of_interest->nextNode == NULL) {
			// CASE BOTH NEXT NODE AND PREVIOUS NODE ARE NULL
			if(node_of_interest->previousNode == NULL) {
				doublyList->head = NULL;
				doublyList->tail = NULL;
			// CASE NEXT NODE IS NULL BUT PREVIOUS NODE IS NOT
			} else {
				doublyList->tail = node_of_interest->previousNode;
				node_of_interest->previousNode->nextNode = NULL;
			}
		// CASE PREVIOUS NODE IS NULL BUT NEXT NODE IS NOT
		} else if(node_of_interest->previousNode == NULL) {
			doublyList->head = node_of_interest->nextNode;
			node_of_interest->nextNode->previousNode = NULL;
		}
	}

	delete_node(node_of_interest);
	doublyList->size--;
}


Node *dll_find_node_by_word(DoublyLinkedList *doublyList, char *word_of_interest) {
	assert(doublyList->head != NULL);

	Node *currentNode = doublyList->head;
	Node *word_of_interest_holder = create_node(word_of_interest);
	Node *result = NULL;

	while(currentNode->nextNode != NULL) {
		if(compare_node_by_word(currentNode, word_of_interest_holder) == 0){
			result = currentNode;
			break;
		}
		currentNode = currentNode->nextNode;
	}

	delete_node(word_of_interest_holder);

	return result;
}


void dll_swap_nodes(DoublyLinkedList *doublyList, Node *node1, Node *node2){
	assert(node1 != node2);

	Node* tmp = create_node("tmp");

	copy_node(tmp, node1);

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

	delete_node(tmp);

	if(node1->previousNode == NULL){
		doublyList->head = node1;
	} else if (node2->previousNode == NULL) {
		doublyList->head = node2;
	}

	if(node1->nextNode == NULL){
		doublyList->tail = node1;
	} else if (node2->nextNode == NULL) {
		doublyList->tail = node2;
	}
}


void dll_insertion_sort(DoublyLinkedList *doublyList) {
	if(doublyList->head == NULL) {
		printf("You attempted to sort an empty list.");
	} else {
		Node *minNode = doublyList->head;
		Node *currentNode = doublyList->head;
		Node *placeKeeper = doublyList->head;

		while(placeKeeper->nextNode != NULL){
			if (DEBUG) {
				printf("PlaceKeeper: ");
				print_node(placeKeeper);
			}

			while(currentNode->nextNode != NULL) {
				if (DEBUG) {
					printf("Current PlaceKeeper comparator: ");
					print_node(currentNode->nextNode);
				}
				if(compare_node_by_word(currentNode->nextNode, minNode) < 0) {
					minNode = currentNode->nextNode;
					if(DEBUG) {
						printf("New minNode found: ");
						print_node(minNode);
					}
				}
				currentNode = currentNode->nextNode;
			}

			if(DEBUG) {
				printf("\n\nMade it through the first while loop!\n\n");
			}

			if(compare_node_by_word(minNode, placeKeeper) < 0) {
				if(DEBUG) {
					printf("The placekeeper wasn't the min! Swapping nodes.\n");
					printf("\tPlaceKeeper: ");
					print_node(placeKeeper);

					printf("\tminNode: ");
					print_node(minNode);
				}

				dll_swap_nodes(doublyList, placeKeeper, minNode);

				placeKeeper = minNode->nextNode;

			} else {
				if(DEBUG) {
					printf("No new min was found. iterating the placeKeeper node up one.\n");
				}

				placeKeeper = placeKeeper->nextNode;
			}
			currentNode = placeKeeper;
			minNode = currentNode;
		}
	}
}

DoublyLinkedList *dll_merge_lists(DoublyLinkedList *doublyList1, DoublyLinkedList *doublyList2) {
	// Sort the lists
	dll_insertion_sort(doublyList1);
	dll_insertion_sort(doublyList2);

	DoublyLinkedList *smaller_list;
	DoublyLinkedList *longer_list;

	if(doublyList1->size < doublyList2->size) {
		smaller_list = doublyList1;
		longer_list = doublyList2;
	} else {
		smaller_list = doublyList2;
		longer_list = doublyList1;
	}

	Node *small_ptr = smaller_list->head;
	Node *long_ptr = longer_list->head;

	while(small_ptr->nextNode != NULL) {
		if(compare_node_by_word(small_ptr, long_ptr) == 0) {

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