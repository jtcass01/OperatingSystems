/*
** File:         test.c
** Author:       Jacob Taylor Cassady
** Description:  
** Last Updated: 8/22/18
*/

/* Compiler/OS Headers */
#include <stdio.h>
/* User Created Headers */
#include "headers/NodeTest.h"
#include "headers/DoublyLinkedListTest.h"
#include "headers/FileParserTest.h"

/* Function prototypes */
void printArray(int *, int);


/* Main function */
int main(int argc, char *argv[]) {
	dll_log_test("/home/durzo/Programming/OperatingSystems/Project1/out_test.txt");
}


/* Function definitions */
void printArray(int *array, int array_size){
	printf("\n== Printing Array of size: %d | memory address: %p ==", array_size, array);

	for(unsigned int array_index = 0; array_index < array_size; array_index++){
		printf("\n\tArray[%d] = %d", array_index, *(array + array_index));
	}
}