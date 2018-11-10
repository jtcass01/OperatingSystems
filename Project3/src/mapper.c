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

	if (argc != 3) {
		printf("Usage: ./mapper [commandFile] [bufferSize]\n");

		return 1;
	} else {
		commandFile = *(argv + 1);
		bufferSize = atoi(*(argv + 2));
	}

	printf("\tcommandFile: %s\n\tbufferSize: %d\n", commandFile, bufferSize);

	process_command_file(commandFile, bufferSize);

	return 0;
}
