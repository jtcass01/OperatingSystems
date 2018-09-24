#ifndef PROCESS
#define PROCESS

/* Compiler/OS Headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* User Created Headers */
#include "constants.h"

typedef struct ProcessNode {
	// Filled During creation
	unsigned int id;
	unsigned int arrival_time;
	unsigned int burst_time;
	unsigned int run_time;
	unsigned int priority;

	// Filled after execution
	unsigned int finish_time;
	unsigned int started;
	unsigned int wait_time;

	struct ProcessNode *nextProcess;
	struct ProcessNode *previousProcess;
} Process;

Process* create_process(int, int, int, int);

void delete_process(Process *);

void finish_process(Process *, int );

void print_process(Process *);

void copy_process(Process *, Process *);

int compare_process_by_priority(Process *, Process *);

int compare_process_by_pid(Process *, Process *);

int compare_process_by_arrival_time(Process *, Process *);

int compare_process_by_finish_time(Process *, Process *);

void log_process(FILE *, Process *);

#endif