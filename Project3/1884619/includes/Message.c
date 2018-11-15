#include "../headers/Message.h"

Message *create_node_message(Node *node) {
  Message *message = malloc(sizeof(Message));

  if (message == NULL) {
		printf("Unable to allocate memory for Message.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for Message.  Initializing attributes...\n");
	#endif

  message->mtype = 1;
  strcpy(message->word, node->word);

  #if DEBUG
		printf("Message successfully allocated and intitialized.  Returning...\n");
	#endif

  return message;
}


void delete_message(Message *message) {
//  free(message->word);
  free(message);
}

MessageQueueConnection *create_message_queue_connection(char *target_file, int sender_flag) {
  MessageQueueConnection *mq_connection = malloc(sizeof(MessageQueueConnection));

	if (mq_connection == NULL) {
		printf("Unable to allocate memory for MessageQueueConnection.\n");

		return NULL;
	}

	#if DEBUG
		printf("Successfully Allocated memory for MessageQueueConnection.  Initializing attributes...\n");
	#endif

	// Intialize attributes.
  mq_connection->target_file = strdup(target_file);

  // Get key
  if ((mq_connection->key = ftok(mq_connection->target_file, 1)) == -1) {
    perror("ftok");
    exit(1);
  }

  //Connect to Queue
  if (sender_flag) { // sender creates the queue
    if ((mq_connection->msqid = msgget(mq_connection->key, 0644 | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
    }
  } else {
    if ((mq_connection->msqid = msgget(mq_connection->key, 0444)) == -1) {
      perror("msgget");
      exit(1);
    }
  }

	#if DEBUG
		printf("MessageQueaueConnection successfully allocated and intitialized.  Returning...\n");
	#endif

	return mq_connection;
}


void send_node(MessageQueueConnection *mq_connection, Node *node) {
  Message *node_message = create_node_message(node);

  if(msgsnd(mq_connection->msqid, node_message, MAXWORDSIZE, 0) == -1) {
    perror("Error in msgsnd");
    exit(1);
  } else {
    printf("Message sent with following attributes: mtype: %ld, word: %s\n", node_message->mtype, node_message->word);
  }

  delete_message(node_message);
}


Node *receive_node(MessageQueueConnection *mq_connection) {
  Message *received_message = malloc(sizeof(Message));

  if (msgrcv(mq_connection->msqid, received_message, MAXWORDSIZE, 0, 0) == -1) {
    perror("msgrcv");
    exit(1);
  } else {
    printf("Message recieved with following attributes: mtype: %ld, word: %s\n", received_message->mtype, received_message->word);
  }

  Node *received_node = create_node(received_message->word);

  delete_message(received_message);
  return received_node;
}


void end_msq_connection(MessageQueueConnection *mq_connection) {
  if(msgctl(mq_connection->msqid, IPC_RMID, NULL) == -1) {
    perror("msgctl");
    exit(1);
  }
}


void destroy_message_queue_connection(MessageQueueConnection *mq_connection) {
  free(mq_connection->target_file);
  free(mq_connection);
}
