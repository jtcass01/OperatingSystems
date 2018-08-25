#include "../headers/Node.h"
#include "../headers/NodeTest.h"

/* Function definitions */
void nodeTest(void) {
	//Build a testNode.
	Node *testNode = create_node("Test Node");
	print_node(testNode);

	//Destroy a testNode.
	delete_node(testNode);
}