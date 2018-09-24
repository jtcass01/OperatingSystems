#include "ProcessTest.h"

/* Function definitions */
// PASSED VALGRIND
void processTest(void) {
	//Build a testNode.
	Process *testProcess = create_process(10, 0, 10, 3);
	print_process(testProcess);

	//Destroy a testNode.
	delete_process(testProcess);
}

// PASSED VALGRIND
void processCopyTest(void) {
	printf("== Performing process copy test... ==\n");

	//Build a testProcess.
	Process *testProcess = create_process(10, 0, 10, 3);

	printf("testProcess before copy: ");
	print_process(testProcess);

	Process *copyProcess = create_process(15, 5, 15, 5);
	printf("Process to be copied: ");
	print_process(copyProcess);
	copy_process(testProcess, copyProcess);

	printf("Updated testProcess after copy: ");
	print_process(testProcess);

	//Destroy a testProcess.
	delete_process(testProcess);
	delete_process(copyProcess);
}