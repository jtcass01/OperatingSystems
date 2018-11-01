#include "headers/mapper.h"

void process_command_file(char *commandFile) {
	/*
	Function Description: The first step of the project is to
	Author: Jacob Taylor Cassady
	*/
	// Initialize DLL for holding each line of the command file
	DoublyLinkedList *directoryPaths = dll_create();

	// Parse the command file and store in DLL.  Print for DEBUG
	parse_file(directoryPaths, commandFile, MAXLINESIZE);
	dll_print(directoryPaths);

	create_map_processes(directoryPaths);

	dll_destroy(directoryPaths);
}

int main(int argc, char *argv[]) {
	char *commandFile;
	int bufferSize;

	if (argc != 3) {
		printf("Invalid number of command line arguments.\n");

		return 1;
	} else {
		commandFile = *(argv + 1);
		bufferSize = atoi(*(argv + 2));
	}

	printf("\tcommandFile: %s\n\tbufferSize: %d\n", commandFile, bufferSize);

	process_command_file(commandFile);

	return 0;
}
