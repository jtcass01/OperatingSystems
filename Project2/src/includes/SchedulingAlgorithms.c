
#include "../headers/SchedulingAlgorithms.h"

void schedule_process(Process *process, int *system_time, int run_time) {
	#if DEBUG
		printf("Process prior to scheduling: ");
		print_process(process);
		printf("System_time: %d\n", *system_time);
		printf("run_time: %d\n", run_time);
	#endif

	if(process->started == 0){
		process->started = 1;

		#if DEBUG
			printf("Updating start time for process: ");
			print_process(process);
		#endif
	}

	// Update burst time
	// Reduce burst time, increase run_time
    process->burst_time -= run_time;
   	*system_time += run_time;

    // Check to see if process is finished
    if(process->burst_time == 0) {
    	finish_process(process, *system_time);
    }

	#if DEBUG
		printf("\nProcess after to scheduling: ");
		print_process(process);
	#endif
}


void first_come_first_serve(DoublyLinkedList *process_list, DoublyLinkedList *finished){
	#if DEBUG
		printf("Entering first_come_first_serve\n");
		dll_print(process_list);
	#endif

	// Sort by arrival time
	dll_insertion_sort(process_list, "arrival_time");

	#if DEBUG
		printf("Done sorting....\n");
	#endif

	Process *current_process = process_list->head;
	Process *nextProcess;
	int current_time = 0;

	while(current_process != NULL) {
		#if DEBUG
			printf("Scheduling process: ");
			print_process(current_process);
		#endif

		schedule_process(current_process, &current_time, current_process->burst_time);

		nextProcess = current_process->nextProcess;
		if(current_process->finish_time > 0) {
			dll_move_process(finished, process_list, current_process);

			#if DEBUG
				printf("Process is finished.");
				print_process(current_process);
			#endif
		}

		current_process = nextProcess;
	}

	dll_insertion_sort(finished, "finish_time");
}


void preemptive_priority(DoublyLinkedList *unarrived, DoublyLinkedList *arrived_unfinished, DoublyLinkedList *finished){

	#if DEBUG
		printf("\n\n=== Entering PP ===\n");
		dll_print(unarrived);
	#endif

	// Sort the unarrived by arrival time
	dll_insertion_sort(unarrived, "arrival_time");

	#if DEBUG
		printf("\n\n=== ARRIVAL TIME SORT ===\n");
		dll_print(unarrived);
	#endif

	int system_time = 0;

	update_process_lists(unarrived, arrived_unfinished, finished, system_time);
	Process *highest_priority_process;

	while(arrived_unfinished->size != 0 || unarrived->size != 0) {
		#if DEBUG
			printf("\n\n=== Available processes @ system_time: %d ===\n", system_time);
			dll_print(arrived_unfinished);
		#endif

		highest_priority_process = dll_find_minimum_process(arrived_unfinished, "priority");

		#if DEBUG
			printf("\n\n=== Scheduling Process... ===\n");
			print_process(highest_priority_process);

			printf("\n\n=== Finished Processes ===\n");
			dll_print(finished);
		#endif

		schedule_process(highest_priority_process, &system_time, PREEMPTIVE_TIME_DELTA);

		update_process_lists(unarrived, arrived_unfinished, finished, system_time);
	}

	dll_insertion_sort(finished, "finish_time");
}


void update_process_lists(DoublyLinkedList *unarrived, DoublyLinkedList *arrived_unfinished, DoublyLinkedList *finished, int system_time) {
	// Update the arrived_unfinished list.
	if (unarrived->size > 0) {
		Process *current_process = unarrived->head;

		while (current_process != NULL) {
			if (current_process->arrival_time <= system_time) {
				dll_move_process(arrived_unfinished, unarrived, current_process);
			}
			current_process = current_process->nextProcess;
		}
	}


	// Update the finished list.
	if (arrived_unfinished->size > 0) {
		Process *current_process = arrived_unfinished->head;

		while (current_process != NULL) {
			if (current_process->finish_time != 0) {
				dll_move_process(finished, arrived_unfinished, current_process);
			}
			current_process = current_process->nextProcess;
		}
	}

}