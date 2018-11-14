
#include "headers/reducer.h"

void receive_and_log_from_mapper(char *outputFile) {
	MessageQueueConnection *mq_connection = create_message_queue_connection("mapper.c", 0);

	// Will need to loop this if one is successful.
	DoublyLinkedList *nodes_received = dll_create();
	Node *received_node = receive_node(mq_connection);

	while(strcmp(received_node->word, "%%%STOPTIME%%%") != 0) {
		dll_insert_tail(nodes_received, received_node);
		printf("Node recieved:"); print_node(received_node); // Replace with log
		received_node = receive_node(mq_connection);
	}
	dll_print(nodes_received);
	dll_log(nodes_received, outputFile);

	dll_destroy(nodes_received);
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
