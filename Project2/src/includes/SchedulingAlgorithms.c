
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


void first_come_first_serve(DoublyLinkedList *process_list){
	#if DEBUG
		printf("Entering first_come_first_serve\n");
	#endif

	// Sort by arrival time
	dll_insertion_sort(process_list, "arrival_time");

	#if DEBUG
		printf("Done sorting....\n");
	#endif

	Process *current_process = process_list->head;
	int current_time = 0;

	while(current_process != NULL) {
		#if DEBUG
			printf("Scheduling process: ");
			print_process(current_process);
		#endif

		schedule_process(current_process, &current_time, current_process->burst_time);
		current_process = current_process->nextProcess;
	}

	dll_insertion_sort(process_list, "finish_time");
}


void preemptive_priority(DoublyLinkedList *process_list){
	#if DEBUG
		printf("\n\n=== Entering PP ===\n");
		dll_print(process_list);
	#endif

	// Sort by arrival time
	dll_insertion_sort(process_list, "arrival_time");

	#if DEBUG
		printf("\n\n=== ARRIVAL TIME SORT ===\n");
		dll_print(process_list);
	#endif

	int system_time = 0;
	DoublyLinkedList* available_processes;

	available_processes = get_available_processes(process_list, system_time);
	Process *highest_priority_process;

	while(available_processes->size != 0) {
		#if DEBUG
			printf("\n\n=== Available processes @ system_time: %d ===\n", system_time);
			dll_print(available_processes);
		#endif

		#if DEBUG
			printf("\n\n=== Sorted Available Processes ===\n");
			dll_print(available_processes);
		#endif


		highest_priority_process = dll_find_process_by_id(process_list, dll_find_minimum_process(available_processes, "priority")->id);

		#if DEBUG
			printf("\n\n=== Scheduling Process ===\n");
			print_process(highest_priority_process);
		#endif

		schedule_process(highest_priority_process, &system_time, PREEMPTIVE_TIME_DELTA);

		dll_destroy(available_processes);


		available_processes = get_available_processes(process_list, system_time);
	}

	dll_destroy(available_processes);

	dll_insertion_sort(process_list, "finish_time");
}


DoublyLinkedList *get_available_processes(DoublyLinkedList *process_list, int system_time){
	DoublyLinkedList *available_processes = dll_create();

	Process *current_process = process_list->head;

	#if DEBUG
		printf("\n === Process list: @ system_time: %d\n ===", system_time);
		dll_print(process_list);
	#endif

	while(current_process != NULL) {
		#if DEBUG
			printf("Current Process: ");
			print_process(current_process);
			printf("(arrival_time: %d <= system_time: %d ) == %d\n", current_process->arrival_time, system_time, (current_process->arrival_time<=system_time));
			printf("(finish_time: %d == 0 ) == %d\n", current_process->finish_time, (current_process->finish_time==0));
		#endif

		if((current_process->arrival_time<=system_time) && (current_process->finish_time==0)) {
			Process *available_process = create_process(0,0,0,0);
			copy_process(available_process, current_process);
			dll_insert_tail(available_processes, available_process);

			#if DEBUG
				printf("Process is available for execution; added to available_processes dll!\n");
			#endif
		}

		current_process = current_process->nextProcess;
	}

	#if DEBUG
		printf("\n === available_processes found ===\n");
		dll_print(available_processes);
	#endif

	return available_processes;
}