#include <stdio.h>

#include "headers/DoublyLinkedList.h"
#include "headers/Process.h"
#include "headers/FileParser.h"
#include "headers/SchedulingAlgorithms.h"

int main(int argc, char *argv[]) {
	char *input_file, *output_file, *sorting_algorithm;

	DoublyLinkedList *unarrived;
	DoublyLinkedList *arrived_unfinished = dll_create();
	DoublyLinkedList *finished = dll_create();

	int limit = 0;

	// Set up arguments from command line
	if(argc < 4 || argc > 5) {
		printf("Invalid number of arguments.\n");

		return 1;
	}

	input_file = *(argv + 1);
	output_file = *(argv + 2);
	sorting_algorithm = *(argv + 3);

	if( argc == 5 ) {
		limit = atoi(*(argv + 4));
	}

	#if DEBUG
		printf("=== Arguments: ===\n");
		printf("\tinput_file: %s\n", input_file);
		printf("\toutput_file: %s\n", output_file);
		printf("\tsorting_algorithm: %s\n", sorting_algorithm);
		printf("\tlimit: %d\n", limit);
	#endif

	// Parse the input file
	unarrived = parse_process_file(input_file, limit);

	// Apply Scheduling algorithm
	if(strcmp(sorting_algorithm, "FCFS") == 0) {
		#if DEBUG
			printf("First come first serve\n");
		#endif

		first_come_first_serve(unarrived, finished);
	} else if (strcmp(sorting_algorithm, "PP") == 0) {
		#if DEBUG
			printf("pre-emptive priority\n");
		#endif

		preemptive_priority(unarrived, arrived_unfinished, finished);
	} else {
		printf("Invalid sorting algorithm.\n");
	}

	dll_log(output_file, finished);

	dll_destroy(finished);
	dll_destroy(finished);
	dll_destroy(finished);

	return 0;
}
