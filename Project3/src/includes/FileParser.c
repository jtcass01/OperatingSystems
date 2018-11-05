/*
** File:         FileParser.c
** Author:       Jacob Taylor Cassady
** Description:
*/

/* User Created Headers */
#include "../headers/FileParser.h"

void retrieve_file_list(DoublyLinkedList *file_list, char *directory_path) {
	DIR *directory_o;
	char *full_path[MAXLINESIZE];

	// Open the directory path
	directory_o = opendir(directory_path);

	if (directory_o == NULL) {
		printf("Unable to open directory : %s\n", directory_path);

		return;

	} else { // Successful opening of directory.

		struct dirent *directory;

		// Iterate over the contents of the directory
		while ((directory = readdir(directory_o)) != NULL) {
			// Ensure the directory item is a file.
			if (directory->d_type == DT_REG) {
				strcpy(full_path, directory_path);
				strncat(full_path, directory->d_name, MAXLINESIZE)
				// Create a node to represent the file and add it to the file_list
				printf("%s\n", full_path);
				Node *file_node = create_node(full_path);
				free(full_path);
				dll_insert_tail(file_list, file_node);
			}
		}

		closedir(directory_o);
	}
}

void parse_file(DoublyLinkedList *file_data, char *file_path, int max_word_size_expected) {
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
			add_words_from_line_to_list(file_data, data_line, max_word_size_expected);
		}
	}

	#if DEBUG
		dll_print(file_data);
	#endif

	free(data_line);

	fclose(data_stream);
}

void add_words_from_line_to_list(DoublyLinkedList *doublyList, char *data_line, int max_word_size_expected) {
	int word_found = 0, char_count = 0, word_start_index = 0;
	char word_buffer[max_word_size_expected];

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
