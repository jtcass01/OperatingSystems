/*
** File:         DoublyLinkedList.c
** Author:       Jacob Taylor Cassady
** Description:
*/


/* User Created Headers */
#include "../headers/DoublyLinkedList.h"


/* Function Defintions */
DoublyLinkedList *dll_create(void){
	/*
	** function:    dll_create
	** author:      Jacob Taylor Cassady
	** description: Dynamically allocates memory for a DoublyLinkedList, initializes the list's
	**				attributes and returns a pointer to the struct.
	*/
	#if DEBUG
		printf("Allocating memory for a DoublyLinkedList...\n");
	#endif

	// Dynamically create the DoublyLinkedList structure
	DoublyLinkedList *doublyList = malloc(sizeof(DoublyLinkedList));

	if(doublyList == NULL) {
		printf("Unable to allocate memory for DoublyLinkedList.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for a DoublyLinkedList.  Initializing attributes...\n");
	#endif

	// Intialize attributes.
	doublyList->head = NULL;
	doublyList->tail = NULL;
	doublyList->size = 0;

	#if DEBUG
		printf("DoublyLinkedList successfully allocated and intitialized.  Returning...\n");
	#endif

	// Return the DoublyLinkedList structure
	return doublyList;
}


void dll_destroy(DoublyLinkedList *doublyList) {
	/*
	** function:    dll_destroy
	** author:      Jacob Taylor Cassady
	** description: Dynamically deallocates memory stored within a DoublyLinkedList and each of it's nodes.
	*/
	Node *currentNode = doublyList->head;
	Node *nextNode;

	while(currentNode != NULL){
		nextNode = currentNode->nextNode;
		delete_node(currentNode);
		currentNode = nextNode;
	}

	free(doublyList);
}


void dll_insert_tail(DoublyLinkedList *doublyList, Node *newNode) {
	/*
	** function:    dll_insert_tail
	** author:      Jacob Taylor Cassady
	** description: Inserts a node into the tail end of a DoublyLinkedList.
	*/
	Node *previous_entry = dll_find_node_by_word(doublyList, word_of_interest);

	if (previous_entry == NULL) {
		// If there is no previous entry, add it to the list.

		if (doublyList->tail == NULL) {
			doublyList->head = newNode;
			doublyList->tail = newNode;
			doublyList->size = 1;
		} else {
			doublyList->tail->nextNode = newNode;
			newNode->previousNode = doublyList->tail;
			newNode->nextNode = NULL;
			doublyList->tail = newNode;
			doublyList->size++;
		}
	} else {
		// else if there is a previous entry, increment the count.
		previous_entry->count++;
	}

}

void dll_insert_head(DoublyLinkedList *doublyList, Node *newNode) {
	/*
	** function:    dll_insert_head
	** author:      Jacob Taylor Cassady
	** description: Inserts a node into the head end of a DoublyLinkedList.
	*/
	Node *previous_entry = dll_find_node_by_word(doublyList, word_of_interest);

	if (previous_entry == NULL) {
		// If there is no previous entry, add it to the list.
		if(doublyList->head == NULL) {
			doublyList->head = newNode;
			doublyList->tail = newNode;
			doublyList->size = 1;
		} else {
			doublyList->head->previousNode = newNode;
			newNode->nextNode = doublyList->head;
			newNode->previousNode = NULL;
			doublyList->head = newNode;
			doublyList->size++;
		}
	} else {
		// else if there is a previous entry, increment the count.
		previous_entry->count++;
	}
}


void dll_delete_node_by_word(DoublyLinkedList *doublyList, char *word_of_interest) {
	/*
	** function:    dll_delete_node_by_word
	** author:      Jacob Taylor Cassady
	** description: Searches for a Node within a DoublyLinkedList using a word identifier and deletes it if found.
	*/
	Node *node_of_interest = dll_find_node_by_word(doublyList, word_of_interest);

	if(node_of_interest != NULL) {
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
}


Node *dll_find_node_by_index(DoublyLinkedList *doublyList, int index) {
	/*
	** function:    dll_find_node_by_word
	** author:      Jacob Taylor Cassady
	** description: Searches for a Node within a DoublyLinkedList by index.
	*/
	if (index >= doublyList->size || index < 0) {
		return NULL;
	} else {
		Node *currentNode = doublyList->head;
		
		for (int node_index = 0; node_index < index; node_index++) {
			currentNode = currentNode->nextNode;
		}

		return currentNode;
	}
}


Node *dll_find_node_by_word(DoublyLinkedList *doublyList, char *word_of_interest) {
	/*
	** function:    dll_find_node_by_word
	** author:      Jacob Taylor Cassady
	** description: Searches for a Node within a DoublyLinkedList using a word identifier.
	*/
	Node *currentNode = doublyList->head;
	Node *word_of_interest_holder = create_node(word_of_interest);
	Node *result = NULL;

	while(currentNode != NULL) {
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
	/*
	** function:    dll_swap_nodes
	** author:      Jacob Taylor Cassady
	** description: Swaps two nodes.
	*/
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
	/*
	** function:    dll_insertion_sort
	** author:      Jacob Taylor Cassady
	** description: Sorts a DoublyLinkedList using the insertion sort algorithm.
	*/
	if(doublyList->head == NULL) {
		printf("You attempted to sort an empty list.");
	} else {
		Node *minNode = doublyList->head;
		Node *currentNode = doublyList->head;
		Node *placeKeeper = doublyList->head;

		while(placeKeeper->nextNode != NULL){
			#if DEBUG
				printf("PlaceKeeper: ");
				print_node(placeKeeper);
			#endif

			while(currentNode->nextNode != NULL) {
				#if DEBUG
					printf("Current PlaceKeeper comparator: ");
					print_node(currentNode->nextNode);
				#endif
				if(compare_node_by_word(currentNode->nextNode, minNode) < 0) {
					minNode = currentNode->nextNode;
					#if DEBUG
						printf("New minNode found: ");
						print_node(minNode);
					#endif
				}
				currentNode = currentNode->nextNode;
			}

			#if DEBUG
				printf("\n\nMade it through the first while loop!\n\n");
			#endif

			if(compare_node_by_word(minNode, placeKeeper) < 0) {
				#if DEBUG
					printf("The placekeeper wasn't the min! Swapping nodes.\n");
					printf("\tPlaceKeeper: ");
					print_node(placeKeeper);

					printf("\tminNode: ");
					print_node(minNode);
				#endif

				dll_swap_nodes(doublyList, placeKeeper, minNode);

				placeKeeper = minNode->nextNode;

			} else {
				#if DEBUG
					printf("No new min was found. iterating the placeKeeper node up one.\n");
				#endif

				placeKeeper = placeKeeper->nextNode;
			}
			currentNode = placeKeeper;
			minNode = currentNode;
		}
	}
}

DoublyLinkedList *dll_merge_lists(DoublyLinkedList *merged_list, DoublyLinkedList *doublyList1, DoublyLinkedList *doublyList2) {
	/*
	** function:    dll_merge_lists
	** author:      Jacob Taylor Cassady
	** description: Sorts two lists using insertion sort and merges them after into a new DoublyLinkedList.
	*/
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

	#if DEBUG
		printf("Smaller List: ");
		dll_print(smaller_list);
		printf("Longer List: ");
		dll_print(longer_list);
		printf("Merged List: ");
		dll_print(merged_list);
	#endif

	Node *small_ptr = smaller_list->head;
	Node *long_ptr = longer_list->head;

	while(small_ptr != NULL && long_ptr != NULL) {
		// CASE Nodes in each list are equal.
		if(compare_node_by_word(small_ptr, long_ptr) == 0) {
			Node *matching_node = create_node("tmp");
			copy_node(matching_node, small_ptr);
			matching_node->count += long_ptr->count;

			#if DEBUG
				printf("\n\n!!! MATCHING NODE FOUND!!! ");
				print_node(matching_node);
			#endif
			dll_insert_tail(merged_list, matching_node);

			#if DEBUG
				printf("Updated Merged List: ");
				dll_print(merged_list);
			#endif

			small_ptr = small_ptr->nextNode;
			long_ptr = long_ptr->nextNode;
		// CASE Node in smaller list is less than node in longer list.
		} else if (compare_node_by_word(small_ptr, long_ptr) < 0) {
			small_ptr = small_ptr->nextNode;
		// CASE Node in smaller list is greather than node in longer list.
		} else {
			long_ptr = long_ptr->nextNode;
		}

	}

	return merged_list;
}

void dll_print(DoublyLinkedList *doublyList) {
	/*
	** function:    dll_print
	** author:      Jacob Taylor Cassady
	** description: Prints information on a DoublyLinkedList and the nodes within.
	*/
	printf("=== Printing Doubly Linked List of size: %d | memory address: %p ===\n", doublyList->size, doublyList->head);

 	if ( doublyList->head == NULL ) {
 		printf("This list is empty. It's head is NULL.\n");
 	} else {
	 	Node *currentNode = doublyList->head;

		while(currentNode != NULL){
			print_node(currentNode);
			currentNode = currentNode->nextNode;
		}
 	}
}

void dll_log(DoublyLinkedList *doublyList, char *log_destination) {
	/*
	** function:    dll_log
	** author:      Jacob Taylor Cassady
	** description: Logs node word and count information from a DoublyLinkedList into a log specified by log_destiantion path.
	*/
 	Node *currentNode = doublyList->head;
	Node *nextNode;

	FILE *log = fopen(log_destination, "w+");

	while(currentNode != NULL){
		nextNode = currentNode->nextNode;

		log_node(currentNode, log);
		fprintf(log, "\n");

		currentNode = nextNode;
	}

	fclose(log);
}
