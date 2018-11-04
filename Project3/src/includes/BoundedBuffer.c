/*
** File:         BoundedBuffer.c
** Author:       Jacob Taylor Cassady
** Description:
*/

#include "../headers/BoundedBuffer.h"

BoundedBuffer *bb_create(max_size) {
	/*
	** function:    bb_create
	** author:      Jacob Taylor Cassady
	** description: Dynamically allocates memory for a BoundedBuffer, initializes the buffer's attributes and returns a pointer to the struct.
	*/
	#if DEBUG
		printf("Allocating memory for a BoundedBuffer...\n");
	#endif

	// Dynamically create the DoublyLinkedList structure
	BoundedBuffer *buffer = malloc(sizeof(DoublyLinkedList));

	if (doublyList == NULL) {
		printf("Unable to allocate memory for BoundedBuffer.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for a BoundedBuffer.  Initializing attributes...\n");
	#endif

	// Intialize attributes.
	buffer->head = NULL;
	buffer->tail = NULL;
	buffer->size = 0;
	buffer->max_size = max_size;

	#if DEBUG
		printf("BoundedBuffer successfully allocated and intitialized.  Returning...\n");
	#endif

	// Return the BoundedBuffer structure
	return buffer;
}

void bb_destroy(BoundedBuffer *buffer) {
	/*
	** function:    dll_destroy
	** author:      Jacob Taylor Cassady
	** description: Dynamically deallocates memory stored within a BoundedBuffer and each of it's nodes.
	*/
	Node *currentNode = buffer->head;
	Node *nextNode;

	while (currentNode != NULL) {
		nextNode = currentNode->nextNode;
		delete_node(currentNode);
		currentNode = nextNode;
	}

	free(buffer);
}

void bb_insert_tail(BoundedBuffer *buffer, Node *newNode) {
	/*
	** function:    dll_insert_tail
	** author:      Jacob Taylor Cassady
	** description: Inserts a node into the tail end of a BoundedBuffer.
	*/
	if (buffer->tail == NULL) {
		buffer->head = newNode;
		buffer->tail = newNode;
		buffer->size = 1;
	}
	else {
		buffer->tail->nextNode = newNode;
		newNode->previousNode = buffer->tail;
		newNode->nextNode = NULL;
		buffer->tail = newNode;
		buffer->size++;
	}
}
/* Function Definitions */