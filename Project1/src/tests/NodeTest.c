#include "NodeTest.h"

/* Function definitions */
// PASSED VALGRIND
void nodeTest(void) {
	//Build a testNode.
	Node *testNode = create_node("Test Node");
	print_node(testNode);

	//Destroy a testNode.
	delete_node(testNode);
}

// PASSED VALGRIND
void nodeCopyTest(void) {
	//Build a testNode.
	Node *testNode = create_node("Test Node");
	print_node(testNode);

	Node *copyNode = create_node("Copy Node");
	copy_node(copyNode, testNode);

	//Destroy a testNode.
	delete_node(testNode);
	delete_node(copyNode);
}