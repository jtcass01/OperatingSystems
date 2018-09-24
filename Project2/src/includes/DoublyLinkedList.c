/*
** File:         DoublyLinkedList.c
** Author:       Jacob Taylor Cassady
** Description:  
*/

/* User Created Headers */
#include "../headers/DoublyLinkedList.h"

DoublyLinkedList *dll_create(void){
	/*
	** function:    dll_create
	** author:      Jacob Taylor Cassady
	** description: Dynamically allocates memory for a DoublyLinkedList, initializes the list's
	**				attributes and returns a pointer to the struct.
	*/
	#if DEBUG
		printf("Allocating memory for a DoublyLinkedList...\n");
	#endif

	// Dynamically create the DoublyLinkedList structure
	DoublyLinkedList *doublyList = malloc(sizeof(DoublyLinkedList));

	if(doublyList == NULL) {
		printf("Unable to allocate memory for DoublyLinkedList.\n");
	} else {
		#if DEBUG
			printf("Successfully Allocated memory for a DoublyLinkedList.  Initializing attributes...\n");
		#endif
	}

	// Initiate the attributes.
	doublyList->head = NULL;
	doublyList->tail = NULL;
	doublyList->size = 0;

	#if DEBUG
		printf("DoublyLinkedList successfully allocated and intitialized.  Returning...\n");
	#endif

	// Return the DoublyLinkedList structure
	return doublyList;
}


void dll_destroy(DoublyLinkedList *doublyList) {
	/*
	** function:    dll_destroy
	** author:      Jacob Taylor Cassady
	** description: Dynamically deallocates memory stored within a DoublyLinkedList and each of it's processes.
	*/
	Process *currentProcess = doublyList->head;
	Process *nextProcess;

	while(currentProcess != NULL){
		nextProcess = currentProcess->nextProcess;
		delete_process(currentProcess);
		currentProcess = nextProcess;
	}

	free(doublyList);
}


void dll_insert_tail(DoublyLinkedList *doublyList, Process *newProcess) {
	/*
	** function:    dll_insert_tail
	** author:      Jacob Taylor Cassady
	** description: Inserts a process into the tail end of a DoublyLinkedList.
	*/
	if(doublyList->tail == NULL) {
		doublyList->head = newProcess;
		doublyList->tail = newProcess;
		newProcess->nextProcess = NULL;
		newProcess->previousProcess = NULL;
		doublyList->size = 1;
	} else {
		doublyList->tail->nextProcess = newProcess;
		newProcess->previousProcess = doublyList->tail;
		newProcess->nextProcess = NULL;
		doublyList->tail = newProcess;
		doublyList->size++;
	}
}

void dll_insert_head(DoublyLinkedList *doublyList, Process *newProcess) {
	/*
	** function:    dll_insert_head
	** author:      Jacob Taylor Cassady
	** description: Inserts a process into the head end of a DoublyLinkedList.
	*/
	if(doublyList->head == NULL) {
		doublyList->head = newProcess;
		doublyList->tail = newProcess;
		newProcess->nextProcess = NULL;
		newProcess->previousProcess = NULL;
		doublyList->size = 1;
	} else {
		doublyList->head->previousProcess = newProcess;
		newProcess->nextProcess = doublyList->head;
		newProcess->previousProcess = NULL;
		doublyList->head = newProcess;
		doublyList->size++;
	}
}

void dll_snip(DoublyLinkedList *doublyList, int new_size) {
	/*
	** function:    dll_snip
	** author:      Jacob Taylor Cassady
	** description: Curtails a DoublyLinkedList to a specific size.
	*/
	if ( doublyList->size > 0 ) {
		DoublyLinkedList *remainder = dll_create();
		Process *currentProcess = doublyList->head;
		int process_index = 0;

		while(currentProcess != NULL && process_index < new_size){ 
			currentProcess = currentProcess->nextProcess;
			process_index++;
		}

		if (currentProcess != NULL) {
			remainder->head = currentProcess;
			remainder->size = doublyList->size - new_size;

			currentProcess->previousProcess->nextProcess = NULL;
			doublyList->size = new_size;
		}


		dll_destroy(remainder);		
	}
}


void dll_delete_process_by_id(DoublyLinkedList *doublyList, int pid_of_interest) {
	/*
	** function:    dll_delete_process_by_id
	** author:      Jacob Taylor Cassady
	** description: Searches for a Process within a DoublyLinkedList using a pid identifier and deletes it if found.
	*/
	Process *process_of_interest = dll_find_process_by_id(doublyList, pid_of_interest);

	if(process_of_interest != NULL) {
		if (process_of_interest->nextProcess != NULL && process_of_interest->previousProcess != NULL){
			process_of_interest->nextProcess->previousProcess = process_of_interest->previousProcess;
			process_of_interest->previousProcess->nextProcess = process_of_interest->nextProcess;
		} else {
			if(process_of_interest->nextProcess == NULL) {
				// CASE BOTH NEXT PROCESS AND PREVIOUS PROCESS ARE NULL
				if(process_of_interest->previousProcess == NULL) {
					doublyList->head = NULL;
					doublyList->tail = NULL;
				// CASE NEXT PROCESS IS NULL BUT PREVIOUS PROCESS IS NOT
				} else {
					doublyList->tail = process_of_interest->previousProcess;
					process_of_interest->previousProcess->nextProcess = NULL;
				}
			// CASE PREVIOUS PROCESS IS NULL BUT NEXT PROCESS IS NOT
			} else if(process_of_interest->previousProcess == NULL) {
				doublyList->head = process_of_interest->nextProcess;
				process_of_interest->nextProcess->previousProcess = NULL;
			}
		}

		delete_process(process_of_interest);
		doublyList->size--;
	}
}


Process *dll_find_process_by_id(DoublyLinkedList *doublyList, int pid_of_interest) {
	/*
	** function:    dll_find_process_by_id
	** author:      Jacob Taylor Cassady
	** description: Searches for a Process within a DoublyLinkedList using a word identifier.
	*/
	Process *currentProcess = doublyList->head;
	Process *pid_of_interest_holder = create_process(pid_of_interest, 0, 0, 0);
	Process *result = NULL;

	while(currentProcess != NULL) {
		if(compare_process_by_pid(currentProcess, pid_of_interest_holder) == 0){
			result = currentProcess;
			break;
		}
		currentProcess = currentProcess->nextProcess;
	}

	delete_process(pid_of_interest_holder);

	return result;
}


Process *dll_find_minimum_process(DoublyLinkedList *doublyList, char *parameter) {
	Process *minimumProcess = doublyList->head;
	Process *currentProcess = doublyList->head;

	if(strcmp(parameter, "priority") == 0) {
		while(currentProcess != NULL) {
			if(currentProcess->priority < minimumProcess->priority) {
				minimumProcess = currentProcess;
			} else if (currentProcess->priority == minimumProcess->priority ) {
				if (currentProcess->arrival_time < minimumProcess->arrival_time) {
					minimumProcess = currentProcess;
				}
			}

			currentProcess = currentProcess->nextProcess;
		}
	}


	return minimumProcess;
}


void dll_swap_processes(DoublyLinkedList *doublyList, Process *process1, Process *process2){
	/*
	** function:    dll_swap_processes
	** author:      Jacob Taylor Cassady
	** description: Swaps two processes.
	*/
	assert(process1 != process2);

	Process* tmp = create_process(0, 0, 0, 0);

	copy_process(tmp, process1);

	if (process2->previousProcess == process1) {
		// Move Process 1 to Process 2's place
		if(process2->nextProcess != NULL) {
			process2->nextProcess->previousProcess = process1;
		}

		process1->nextProcess = process2->nextProcess;
		process1->previousProcess = process2;

		// Move Process 2 to Process 1's place
		if(tmp->previousProcess != NULL) {
			tmp->previousProcess->nextProcess = process2;
		}

		process2->previousProcess = tmp->previousProcess;
		process2->nextProcess = process1;
	} else if (process2->nextProcess == process1) {
		// Move Process 1 to Process 2's place
		if(process2->previousProcess != NULL) {
			process2->previousProcess->nextProcess = process1;				
		}

		process1->nextProcess = process2;
		process1->previousProcess = process2->previousProcess;

		// Move Process 2 to Process 1's place
		if(tmp->nextProcess != NULL) {
			tmp->nextProcess->previousProcess = process2;
		}

		process2->nextProcess = tmp->nextProcess;
		process2->previousProcess = process1;
	} else {
		// Move Process 1 to Process 2's place
		if(process2->previousProcess != NULL) {
			process2->previousProcess->nextProcess = process1;				
		}
		if(process2->nextProcess != NULL) {
			process2->nextProcess->previousProcess = process1;
		}
		process1->nextProcess = process2->nextProcess;
		process1->previousProcess = process2->previousProcess;

		// Move Process 2 to Process 1's place
		process2->nextProcess = tmp->nextProcess;
		process2->previousProcess = tmp->previousProcess;
		if(tmp->nextProcess != NULL) {
			tmp->nextProcess->previousProcess = process2;
		}
		if(tmp->previousProcess != NULL) {
			tmp->previousProcess->nextProcess = process2;
		}
	}

	delete_process(tmp);

	if(process1->previousProcess == NULL){
		doublyList->head = process1;
	} else if (process2->previousProcess == NULL) {
		doublyList->head = process2;
	}

	if(process1->nextProcess == NULL){
		doublyList->tail = process1;
	} else if (process2->nextProcess == NULL) {
		doublyList->tail = process2;
	}
}


void dll_insertion_sort(DoublyLinkedList *doublyList, char *parameter) {
	/*
	** function:    dll_insertion_sort
	** author:      Jacob Taylor Cassady
	** description: Sorts a DoublyLinkedList using the insertion sort algorithm.
	*/

	// PRIORITY SORT
	if (strcmp(parameter, "priority") == 0) {
		if(doublyList->head == NULL) {
			printf("You attempted to sort an empty list.");
		} else {
			Process *minProcess = doublyList->head;			// Keeps track of minimum process
			Process *currentProcess = doublyList->head;		// Keeps track of iterator
			Process *placeKeeper = doublyList->head; 		// Keeps track of sorted and unsorted line

			while(placeKeeper->nextProcess != NULL){
				#if DEBUG
					printf("PlaceKeeper: ");
					print_process(placeKeeper);
				#endif

				while(currentProcess->nextProcess != NULL) {
					#if DEBUG
						printf("Current PlaceKeeper comparator: ");
						print_process(currentProcess->nextProcess);
					#endif

					if(compare_process_by_priority(currentProcess->nextProcess, minProcess) < 0) {
						minProcess = currentProcess->nextProcess;

						#if DEBUG
							printf("New minProcess found: ");
							print_process(minProcess);
						#endif
					} else if (compare_process_by_priority(currentProcess->nextProcess, minProcess) == 0) {
						if(compare_process_by_arrival_time(currentProcess->nextProcess, minProcess) < 0) {
							minProcess = currentProcess->nextProcess;
						}

						#if DEBUG
							printf("New minProcess found: ");
							print_process(minProcess);
						#endif
					}
					currentProcess = currentProcess->nextProcess;
				}

				#if DEBUG
					printf("\n\nMade it through the first while loop!\n\n");
				#endif

				if(compare_process_by_priority(minProcess, placeKeeper) < 0) {
					#if DEBUG
						printf("The placekeeper wasn't the min! Swapping processes.\n");
						printf("\tPlaceKeeper: ");
						print_process(placeKeeper);

						printf("\tminProcess: ");
						print_process(minProcess);
					#endif

					dll_swap_processes(doublyList, placeKeeper, minProcess);

					placeKeeper = minProcess->nextProcess;

				} else {
					#if DEBUG
						printf("No new min was found. iterating the placeKeeper process up one.\n");
					#endif

					placeKeeper = placeKeeper->nextProcess;
				}
				currentProcess = placeKeeper;
				minProcess = currentProcess;
			}
		}
	}

	//arrival_time Sort	
	if (strcmp(parameter, "arrival_time") == 0) {
		if(doublyList->head == NULL) {
			printf("You attempted to sort an empty list.");
		} else {
			Process *minProcess = doublyList->head;
			Process *currentProcess = doublyList->head;
			Process *placeKeeper = doublyList->head;

			while(placeKeeper->nextProcess != NULL){
				#if DEBUG
					printf("PlaceKeeper: ");
					print_process(placeKeeper);
				#endif

				while(currentProcess->nextProcess != NULL) {
					#if DEBUG
						printf("Current PlaceKeeper comparator: ");
						print_process(currentProcess->nextProcess);
					#endif
					if(compare_process_by_arrival_time(currentProcess->nextProcess, minProcess) < 0) {
						minProcess = currentProcess->nextProcess;
						#if DEBUG
							printf("New minProcess found: ");
							print_process(minProcess);
						#endif
					}
					currentProcess = currentProcess->nextProcess;
				}

				#if DEBUG
					printf("\n\nMade it through the first while loop!\n\n");
				#endif

				if(compare_process_by_arrival_time(minProcess, placeKeeper) < 0) {
					#if DEBUG
						printf("The placekeeper wasn't the min! Swapping processes.\n");
						printf("\tPlaceKeeper: ");
						print_process(placeKeeper);

						printf("\tminProcess: ");
						print_process(minProcess);
					#endif

					dll_swap_processes(doublyList, placeKeeper, minProcess);

					placeKeeper = minProcess->nextProcess;

				} else {
					#if DEBUG
						printf("No new min was found. iterating the placeKeeper process up one.\n");
					#endif

					placeKeeper = placeKeeper->nextProcess;
				}
				currentProcess = placeKeeper;
				minProcess = currentProcess;
			}
		}
	}


	//finish_time sort
	if (strcmp(parameter, "finish_time") == 0) {
		if(doublyList->head == NULL) {
			printf("You attempted to sort an empty list.");
		} else {
			Process *minProcess = doublyList->head;
			Process *currentProcess = doublyList->head;
			Process *placeKeeper = doublyList->head;

			while(placeKeeper->nextProcess != NULL){
				#if DEBUG
					printf("PlaceKeeper: ");
					print_process(placeKeeper);
				#endif

				while(currentProcess->nextProcess != NULL) {
					#if DEBUG
						printf("Current PlaceKeeper comparator: ");
						print_process(currentProcess->nextProcess);
					#endif
					if(compare_process_by_finish_time(currentProcess->nextProcess, minProcess) < 0) {
						minProcess = currentProcess->nextProcess;
						#if DEBUG
							printf("New minProcess found: ");
							print_process(minProcess);
						#endif
					}
					currentProcess = currentProcess->nextProcess;
				}

				#if DEBUG
					printf("\n\nMade it through the first while loop!\n\n");
				#endif

				if(compare_process_by_finish_time(minProcess, placeKeeper) < 0) {
					#if DEBUG
						printf("The placekeeper wasn't the min! Swapping processes.\n");
						printf("\tPlaceKeeper: ");
						print_process(placeKeeper);

						printf("\tminProcess: ");
						print_process(minProcess);
					#endif

					dll_swap_processes(doublyList, placeKeeper, minProcess);

					placeKeeper = minProcess->nextProcess;

				} else {
					#if DEBUG
						printf("No new min was found. iterating the placeKeeper process up one.\n");
					#endif

					placeKeeper = placeKeeper->nextProcess;
				}
				currentProcess = placeKeeper;
				minProcess = currentProcess;
			}
		}
	}

}


void dll_print(DoublyLinkedList *doublyList) {
	/*
	** function:    dll_print
	** author:      Jacob Taylor Cassady
	** description: Prints information on a DoublyLinkedList and the processes within.
	*/
	printf("=== Printing Doubly Linked List of size: %d | memory address: %p ===\n", doublyList->size, doublyList->head);
 
 	if ( doublyList->head == NULL ) {
 		printf("This list is empty. It's head is NULL.\n");
 	} else {
	 	Process *currentProcess = doublyList->head;

		while(currentProcess != NULL){
			print_process(currentProcess);
			currentProcess = currentProcess->nextProcess;
		}
 	}
}

void dll_log(char *log_destination, DoublyLinkedList *doublyList) {
	/*
	** function:    dll_log
	** author:      Jacob Taylor Cassady
	** description: Logs process information from a DoublyLinkedList into a log specified by log_destiantion path.
	*/
 	Process *currentProcess = doublyList->head;

	FILE *log = fopen(log_destination, "w+");

	while(currentProcess != NULL){
		log_process(log, currentProcess);

		currentProcess = currentProcess->nextProcess;
	}

	fclose(log);
}