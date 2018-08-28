#include <stdio.h>

#include "../headers/DoublyLinkedList.h"
#include "../headers/DoublyLinkedListTest.h"

/* Function definitions */
void dll_test(void) {
	dll_merge_test();
}

DoublyLinkedList *dll_create_test_list(void) {
	DoublyLinkedList *testList = dll_create();

	if(testList == NULL) {
		printf("Unable to allocate memory for a test list.");
	} else {
		dll_print(testList);		
	}

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

DoublyLinkedList *dll_create_test_list_2(void) {
	DoublyLinkedList *testList = dll_create();

	if(testList == NULL) {
		printf("Unable to allocate memory for a test list.");
	} else {
		dll_print(testList);		
	}

	printf("Creating a testList with nodes \"Hello World What's Up?\"...\n");
	Node* tmp = create_node("It");
	dll_insert_head(testList, tmp);
	tmp = create_node("is");
	dll_insert_tail(testList, tmp);
	tmp = create_node("Always");
	dll_insert_head(testList, tmp);
	tmp = create_node("Sunny");
	dll_insert_tail(testList, tmp);
	dll_print(testList);

	return testList;
}

DoublyLinkedList *dll_create_test_list_3(void) {
	DoublyLinkedList *testList = dll_create();

	if(testList == NULL) {
		printf("Unable to allocate memory for a test list.");
	} else {
		dll_print(testList);		
	}

	printf("Creating a testList with nodes \"Hello World What's Up?\"...\n");
	Node* tmp = create_node("Up?");
	dll_insert_tail(testList, tmp);
	tmp = create_node("What's");
	dll_insert_head(testList, tmp);
	tmp = create_node("Sunny");
	dll_insert_tail(testList, tmp);
	dll_print(testList);

	return testList;
}

void dll_insert_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	dll_destroy(testList);
}

void dll_delete_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	dll_insertion_sort(testList);

	printf("\n\nDeleting nodes...\n");
	dll_delete_node_by_word(testList, "World");
	dll_delete_node_by_word(testList, "Hello");
	dll_delete_node_by_word(testList, "What's");
	dll_delete_node_by_word(testList, "Up?");
	dll_print(testList);

	dll_destroy(testList);
}

void dll_swap_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	printf("\n\nSwapping the second and third nodes in the testList\n");
	//Swap the second and third nodes in the list.
	dll_swap_nodes(testList, testList->head->nextNode->nextNode, testList->head->nextNode);
	dll_print(testList);

	printf("Swapping the first and forth nodes in the testList\n");
	dll_swap_nodes(testList, testList->head, testList->head->nextNode->nextNode->nextNode);
	dll_print(testList);

	dll_destroy(testList);
}

void dll_find_node_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	printf("\n\nSearching for the string \"What's\"...");
	Node *search_result = dll_find_node_by_word(testList, "What's");
	print_node(search_result);

	printf("Searching for the string \"Hello\"...");
	search_result = dll_find_node_by_word(testList, "Hello");
	print_node(search_result);

	dll_destroy(testList);
}

void dll_sort_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();

	printf("\n\nSorting the list...\n");
	dll_insertion_sort(testList);
	dll_print(testList);

	DoublyLinkedList *testList2 = dll_create_test_list_2();
	printf("\n\nSorting the list...\n");
	dll_insertion_sort(testList2);
	dll_print(testList2);

	dll_destroy(testList);
	dll_destroy(testList2);
}

void dll_merge_test(void) {
	DoublyLinkedList *testList = dll_create_test_list();
	DoublyLinkedList *testList2 = dll_create_test_list_3();

	printf("\n\nMergin the lists...\n");
	DoublyLinkedList *mergedList = dll_merge_lists(testList, testList2);
	dll_print(mergedList);

	dll_destroy(mergedList);

}