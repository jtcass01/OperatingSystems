#include <stdio.h>

#include "../headers/DoublyLinkedList.h"
#include "../headers/DoublyLinkedListTest.h"

/* Function definitions */
void dll_test(void) {
	dll_swap_test();
}

DoublyLinkedList *dll_create_test_list(void) {
	DoublyLinkedList *testList = dll_create();
	dll_print(testList);

	printf("Creating a testList with nodes \"Hello World What's Up?\"...\n");
	Node* tmp = create_node("World");
	dll_insert_head(testList, tmp);
	tmp = create_node("What's");
	dll_insert_tail(testList, tmp);
	tmp = create_node("Hello");
	dll_insert_head(testList, tmp);
	tmp = create_node("Up?");
	dll_insert_tail(testList, tmp);
	dll_print(testList);

	return testList;
}

void dll_insert_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	dll_destroy(testList);
}

void dll_swap_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	printf("Swapping the second and third nodes in the testList\n");
	//Swap the second and third nodes in the list.
	dll_swap_nodes(testList, testList->head->nextNode->nextNode, testList->head->nextNode);
	dll_print(testList);

	printf("Swapping the first and forth nodes in the testList\n");
	dll_swap_nodes(testList, testList->head, testList->head->nextNode->nextNode->nextNode);
	dll_print(testList);

	dll_destroy(testList);
}

void dll_sort_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	printf("Sorting the list...\n");
	dll_insertion_sort(testList);
	dll_print(testList);

	dll_destroy(testList);
}