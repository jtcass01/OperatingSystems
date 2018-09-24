/*
** File:         FileParser.c
** Author:       Jacob Taylor Cassady
** Description:  
*/

/* User Created Headers */
#include "../headers/FileParser.h"

DoublyLinkedList *parse_process_file(char *file_location, int limit){
	DoublyLinkedList *process_list = dll_create();
	int pid = 0, arrival_time = 0, burst_time = 0, priority = 0;
	FILE *process_file;

	process_file = fopen(file_location, "r");
	rewind(process_file);

	while(fscanf(process_file, "%d %d %d %d", &pid, &arrival_time, &burst_time, &priority) != EOF) {
		Process *currentProcess = create_process(pid, arrival_time, burst_time, priority);
		dll_insert_tail(process_list, currentProcess);
	}

	dll_insertion_sort(process_list, "arrival_time");

	if (limit != 0) {
		dll_snip(process_list, limit);
	}

	fclose(process_file);

	return process_list;
}