
#include "headers/reducer.h"

void receive_and_log_from_mapper(char *outputFile) {
	MessageQueueConnection *mq_connection = create_message_queue_connection("mapper.c", 0);

	// Will need to loop this if one is successful.
	Node *received_node = receive_node(mq_connection);

	while(strcmp(received_node->word, "%%%STOPTIME%%%") != 0) {
		printf("Node recieved:"); print_node(received_node); // Replace with log
		received_node = receive_node(mq_connection);
	}
	end_msq_connection(mq_connection);
	destroy_message_queue_connection(mq_connection);
}

int main(int argc, char *argv[]) {
	char *outputFile;

	if (argc != 2) {
		printf("Usage: ./reducer [outputFile]\n");

		return 1;
	} else {
		outputFile = *(argv + 1);
	}

	printf("\treducer started.  outputFile: %s\n", outputFile);
	receive_and_log_from_mapper(outputFile);

	return 0;
}
