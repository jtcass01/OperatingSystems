#include "headers/mapper.h"

void process_command_file(char *commandFile, int bufferSize) {
	/*
	Function Description: The first step of the project is to
	Author: Jacob Taylor Cassady
	*/
	// Initialize DLL for holding each line of the command file
	DoublyLinkedList *directoryPaths = dll_create();

	// Parse the command file and store in DLL.  Print for DEBUG
	parse_file(directoryPaths, commandFile, MAXLINESIZE);

	// Create a process for each directory listed in the commandFile
	create_map_processes(directoryPaths, bufferSize);

	dll_destroy(directoryPaths);
}

int main(int argc, char *argv[]) {
	char *commandFile;
	int bufferSize;

	DoublyLinkedList *test_list = dll_create();
	Node *test_node = create_node("Test 1");
	Node *test_node2 = create_node("Test 2");
	Node *test_node4 = create_node("Test 3");

	dll_insert_tail(test_list, test_node);
	dll_insert_tail(test_list, test_node2);
	dll_insert_tail(test_list, test_node4);

	dll_print(test_list);

	Node *test_node3 = dll_pop_head(test_list);

	dll_print(test_list);

	delete_node(test_node3);

	dll_destroy(test_list);

	if (argc != 3) {
		printf("Invalid number of command line arguments.\n");

		return 1;
	} else {
		commandFile = *(argv + 1);
		bufferSize = atoi(*(argv + 2));
	}

	printf("\tcommandFile: %s\n\tbufferSize: %d\n", commandFile, bufferSize);

	process_command_file(commandFile, bufferSize);

	return 0;
}
