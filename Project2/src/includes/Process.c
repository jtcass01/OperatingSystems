/*
** File:         Process.c
** Author:       Jacob Taylor Cassady
** Description: 
*/

#include "../headers/Process.h"

Process *create_process(int id, int arrival_time, int burst_time, int priority){
	Process *newProcess = malloc(sizeof(Process));

	newProcess->id = id;
	newProcess->arrival_time = arrival_time;
	newProcess->burst_time = burst_time;
	newProcess->run_time = burst_time;
	newProcess->priority = priority;

	newProcess->finish_time = 0;
	newProcess->wait_time = 0;
	newProcess->started = 0;

	newProcess->nextProcess = NULL;
	newProcess->previousProcess = NULL;

	return newProcess;
}


void delete_process(Process *process){
	free(process);
}


void finish_process(Process *process, int system_time){
   	process->finish_time = system_time;
   	process->wait_time = system_time - process->arrival_time - process->run_time;
}


void print_process(Process *process){
	if(process == NULL) {
		printf("This is a NULL process.  Cannot print.\n");
	} else {
		printf("Address: %p, id: %d, arrival_t: %d, burst_t: %d, priority: %d, finish_time: %d, wait_time: %d, previousProcess: %p, nextProcess: %p\n", process, process->id, process->arrival_time, process->burst_time, process->priority, process->finish_time, process->wait_time, process->previousProcess, process->nextProcess);
	}
}


void copy_process(Process *destination, Process *source) {
	destination->id = source->id;
	destination->arrival_time = source->arrival_time;
	destination->burst_time = source->burst_time;
	destination->run_time = source->run_time;
	destination->priority = source->priority;
	destination->finish_time = source->finish_time;
	destination->wait_time = source->wait_time;
	destination->started = source->started;
	destination->nextProcess = source->nextProcess;
	destination->previousProcess = source->previousProcess;
}


int compare_process_by_priority(Process *process1, Process *process2) {
	int result = 0;

	if (process1->priority < process2->priority) {
		result = -1;
	} else if (process1->priority == process2->priority) {
		result = 0;
	} else {
		result = 1;
	}

	#if DEBUG
		printf("\nComparing processes by word...\n");
		printf("Process1: ");
		print_process(process1);
		
		printf("Process2: ");
		print_process(process2);

		printf("Result: %d\n", result);
	#endif

	return result;
}

int compare_process_by_pid(Process *process1, Process *process2) {
	int result = 0;

	if (process1->id < process2->id) {
		result = -1;
	} else if (process1->id == process2->id) {
		result = 0;
	} else {
		result = 1;
	}

	#if DEBUG
		printf("\nComparing processes by id...\n");
		printf("Process1: ");
		print_process(process1);
		
		printf("Process2: ");
		print_process(process2);

		printf("Result: %d\n", result);
	#endif

	return result;
}


int compare_process_by_arrival_time(Process *process1, Process *process2) {
	int result = 0;

	if (process1->arrival_time < process2->arrival_time) {
		result = -1;
	} else if (process1->arrival_time == process2->arrival_time) {
		result = 0;
	} else {
		result = 1;
	}

	#if DEBUG
		printf("\nComparing processes by arrival_time...\n");
		printf("Process1: ");
		print_process(process1);
		
		printf("Process2: ");
		print_process(process2);

		printf("Result: %d\n", result);
	#endif

	return result;
}


int compare_process_by_finish_time(Process *process1, Process *process2) {
	int result = 0;

	if (process1->finish_time < process2->finish_time) {
		result = -1;
	} else if (process1->finish_time == process2->finish_time) {
		result = 0;
	} else {
		result = 1;
	}

	#if DEBUG
		printf("\nComparing processes by finish_time...\n");
		printf("Process1: ");
		print_process(process1);
		
		printf("Process2: ");
		print_process(process2);

		printf("Result: %d\n", result);
	#endif

	return result;
}


void log_process(FILE *log_file, Process *process) {
	#if DEBUG
		printf("Logging Process: ");
		print_process(process);
	#endif

	fprintf(log_file, "%d %d %d %d\n", process->id, process->arrival_time, process->finish_time, process->wait_time);
}