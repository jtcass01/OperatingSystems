#include "headers/FileParser.h"
#include "headers/DoublyLinkedList.h"

int main(int argc, char *argv[]) {
	char *directoryPath;

	if (argc != 2) {
		printf("Invalid number of command line arguments.\n");

		return 1;
	}
	else {
		directoryPath = *(argv + 1);
	}

	DoublyLinkedList *file_list = dll_create();

	retrieve_file_list(file_list, directoryPath);

	dll_print(file_list);

	dll_destroy(file_list);

	return 0;
}
