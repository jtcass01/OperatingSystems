#include "headers/mapper.h"

void process_command_file(char *commandFile) {
	/*
	Function Description: The first step of the project is to
	Author: Jacob Taylor Cassady
	*/

	DoublyLinkedList *command_list = dll_create();

	parse_file(command_list, commandFile, MAXLINESIZE);

	dll_print(command_list);

	dll_destroy(command_list);
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
