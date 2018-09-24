#include <stdio.h>

#include "tests/SchedulingAlgorithmsTest.h"

int main(int argc, char *argv[]) {
	char *input_file, *output_file, *sorting_algorithm;
	DoublyLinkedList *process_list;
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
	process_list = parse_process_file(input_file, limit);

	// Apply Scheduling algorithm
	if(strcmp(sorting_algorithm, "FCFS") == 0) {
		#if DEBUG
			printf("First come first serve\n");
		#endif

		first_come_first_serve(process_list);
	} else if (strcmp(sorting_algorithm, "PP") == 0) {
		#if DEBUG
			printf("pre-emptive priority\n");
		#endif

		preemptive_priority(process_list);
	} else {
		printf("Invalid sorting algorithm.\n");
	}

	dll_log(output_file, process_list);

	dll_destroy(process_list);

	return 0;
}
