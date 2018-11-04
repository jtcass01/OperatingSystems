
#include "../headers/Multithreader.h"

void create_map_threads(char *directory_path) {
	DoublyLinkedList *file_list = dll_create();

	retrieve_file_list(file_list, directory_path);

	dll_print(file_list);

	dll_destroy(file_list);
}