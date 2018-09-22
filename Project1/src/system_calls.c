/*
** File:         system_calls.c
** Author:       Jacob Taylor Cassady
** Description:  
*/

/* Compiler/OS Headers */
#include <stdio.h>
/* User Created Headers */
#include "headers/FileParser.h"
#include "headers/DoublyLinkedList.h"

/* Main function */
int main(int argc, char *argv[]) {
	char *input_file_location, *output_file_location;
	DoublyLinkedList *system_call_list = dll_create();

	input_file_location = strdup(*(argv + 1));
	output_file_location = strdup(*(argv + 2));

	parse_file(system_call_list, input_file_location);

	dll_insertion_sort(system_call_list);

	dll_log(system_call_list, output_file_location);

	free(input_file_location);
	free(output_file_location);	
}