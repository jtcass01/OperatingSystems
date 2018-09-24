
#include "SchedulingAlgorithmsTest.h"

void FCFS_test(int limit) {
	DoublyLinkedList *process_list = parse_process_file("/home/durzo/Programming/OperatingSystems/Project2/Test_Files/sample_input0.txt", limit);

	first_come_first_serve(process_list);

	dll_log("/home/durzo/Programming/OperatingSystems/Project2/Test_Files/sample_output0.txt", process_list);

	dll_destroy(process_list);
}