
#include "headers/mapper.h"

void process_command_file(char *commandFile) {
	DoublyLinkedList *command_list = dll_create();

	parse_file(commandFile, command_list);

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

	printf("\n\tcommandFile: %s\n\tbufferSize: %d", commandFile, bufferSize);

	process_command_file(commandFile);

	return 0;
}