
#include "../headers/FileParser.h"

DoublyLinkedList *parse_file(char *file_path) {
	char *data_line = NULL, *word = NULL;
	FILE *data_stream = fopen(file_path, "r");
	rewind(data_stream);

	size_t len = 0;

	while(getline(&data_line, &len, data_stream) != -1) {
		if(line_has_word(data_line)) {
			printf("Data_line: %s\n", data_line);
//			word = strtok(data_line, " ");
			printf("Word: %s\n", word);
		}
	}

	free(word);


	fclose(data_stream);
}

int line_has_word(char *line){
	for(int line_index = 0; *(line + line_index) != '\0'; line_index++){
		if((int) *(line + line_index) > 32 ){
			printf("char: %c, value:%d\n", *(line + line_index), (int) *(line + line_index));
			return 1;
		}
	}
	return 0;
}
