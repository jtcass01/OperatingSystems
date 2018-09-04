/* User Created Headers */
#include "FileParserTest.h"

/* Function Defintions */
void test_parse_merge_log_files(void) {
	parse_and_merge_files("/home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in1.txt", "/home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in2.txt", "/home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/out_test.txt");
}

void test_parse_file(void) {
	printf("\nPARSING FILE: /home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in1.txt\n");
	DoublyLinkedList *test_list = dll_create();
	parse_file(test_list, "/home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in1.txt");
	dll_destroy(test_list);

	printf("\nPARSING FILE: /home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in2.txt\n");
	DoublyLinkedList *test_list2 = dll_create();
	parse_file(test_list2, "/home/durzo/Programming/OperatingSystems/Project1/src/tests/test_files/test_1/in2.txt");
	dll_destroy(test_list2);
}