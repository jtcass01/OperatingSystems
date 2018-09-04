/*
** File:         FileParser.c
** Author:       Jacob Taylor Cassady
** Description:  
*/

/* User Created Headers */
#include "../headers/FileParser.h"

void parse_and_merge_files(char *input_file1_path, char *input_file2_path, char *output_file_path) {
	// Dynamically allocate memory for a DoublyLinkedList struct for file 1.
	#if DEBUG
		printf("\nBuilding a dll list out of file: %s\n", input_file1_path);
	#endif
	DoublyLinkedList *file1_list = dll_create();
	
	// Parse a file 1 to build a dll representation of the inner words.
	#if DEBUG
		printf("dll struct dynamically allocated.  Parsing file...\n");
		printf("dll struct dynamically allocated.  Parsing file...\n");
	#endif
	parse_file(file1_list, input_file1_path);

	// Dynamically allocate memory for a DoublyLinkedList struct for file 1.
	#if DEBUG
		printf("dll %s successfully created.\n", input_file1_path);
		printf("\nBuilding a dll list out of file: %s\n", input_file2_path);
	#endif
	DoublyLinkedList *file2_list = dll_create();

	// Parse a file 2 to build a dll representation of the inner words.
	#if DEBUG
		printf("dll struct dynamically allocated.  Parsing file...\n");
	#endif
	parse_file(file2_list, input_file2_path);

	// Merge parsed files.
	#if DEBUG
		printf("dll %s successfully created.\n", input_file2_path);
		printf("\nMerging previously mentioned files...\n");
	#endif
	DoublyLinkedList *merged_list = dll_create();
	dll_merge_lists(merged_list, file1_list, file2_list);

	#if DEBUG
		printf("Logging merged dll at relative directory: %s...\n", output_file_path);
	#endif
	dll_log(merged_list, output_file_path);

	#if DEBUG
		printf("merged dll successfully logged.  Freeing allocated memory..\n");
	#endif
	dll_destroy(file1_list);
	dll_destroy(file2_list);
	dll_destroy(merged_list);

	#if DEBUG
		printf("Allocated memory succesfully freed.\n");
	#endif
}

void parse_file(DoublyLinkedList *file_list, char *file_path) {
	char *data_line = NULL;
	size_t len = 0;

	// Open file and point to the beginning.
	#if DEBUG
		printf("Opening file %s and rewinding to the beginning...\n", file_path);
	#endif
	FILE *data_stream = fopen(file_path, "r");
	rewind(data_stream);

	// Get words from each line of the document.
	#if DEBUG
		printf("File successfully opened and rewound.\n");
		printf("Retrieving words line by line from document.\n");
	#endif
	while(getline(&data_line, &len, data_stream) != -1) {
		
		if(line_has_word(data_line)) {
			add_words_from_line_to_list(file_list, data_line);
		}

	}

	#if DEBUG
		dll_print(file_list);
	#endif

	fclose(data_stream);
}

void add_words_from_line_to_list(DoublyLinkedList *doublyList, char *data_line) {
	int word_found = 0, char_count = 0, word_start_index = 0;
	int line_size = get_line_size(data_line);
	char word_buffer[line_size];
				
	#if DEBUG
		print_data_line_info(data_line);
	#endif

	for(int letter_index = 0; *(data_line + letter_index) != '\0'; letter_index++){

		if((int) *(data_line + letter_index) > 32) {
			if (!word_found) {
				word_start_index = letter_index;
				word_found = 1;
			}
			char_count++;

		} else {
			if (word_found) {
				get_word(word_buffer, data_line, word_start_index, char_count);
				Node *word_node = create_node_from_buffer(word_buffer, char_count);
				Node *matching_node = dll_find_node_by_word(doublyList, word_node->word);

				if(matching_node == NULL) {
					dll_insert_tail(doublyList, word_node);
				} else {
					matching_node->count++;
					delete_node(word_node);
				}
			}

			word_found = 0;
			char_count = 0;
		}
	}

	if (word_found) {
		get_word(word_buffer, data_line, word_start_index, char_count);
		Node *word_node = create_node_from_buffer(word_buffer, char_count);
		Node *matching_node = dll_find_node_by_word(doublyList, word_node->word);

		if(matching_node == NULL) {
			dll_insert_tail(doublyList, word_node);
		} else {
			matching_node->count++;
			delete_node(word_node);
		}
	}
}

void get_word(char *word, char *data_line, long word_start_index, long char_count) {
	for(long word_index = 0; word_index < char_count; word_index++) {
		word[word_index] = *(data_line + word_index + word_start_index);
		#if DEBUG
			printf("Char: %c\n", *(data_line + word_index));
			printf("word: %s\n", word);
		#endif
	}
}

long get_line_size(char *line) {
	long line_size = 0;

	for(line_size = 0; *(line + line_size) != '\0'; line_size++);

	return line_size;
}

int line_has_word(char *line){
	for(int line_index = 0; *(line + line_index) != '\0'; line_index++){
		if((int) *(line + line_index) > 32 ){
			return 1;
		}
	}
	return 0;
}

void print_data_line_info(char *data_line) {
	printf("Data_line: %s\n", data_line);

	for(unsigned int line_index = 0; *(data_line + line_index) != '\0'; line_index++) {
		printf("char: %c, value:%d\n", *(data_line + line_index), (int) *(data_line + line_index));
	}
}
