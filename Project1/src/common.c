/*
** File:         common.c
** Author:       Jacob Taylor Cassady
** Description:  
*/

/* Compiler/OS Headers */
#include <stdio.h>
/* User Created Headers */
#include "headers/FileParser.h"

/* Main function */
int main(int argc, char *argv[]) {
	char *input_file_location_1, *input_file_location_2, *output_file_location;

	input_file_location_1 = strdup(*(argv + 1));
	input_file_location_2 = strdup(*(argv + 2));
	output_file_location = strdup(*(argv + 3));

	parse_and_merge_files(input_file_location_1, input_file_location_2, output_file_location);

	free(input_file_location_1);
	free(input_file_location_2);
	free(output_file_location);	
}