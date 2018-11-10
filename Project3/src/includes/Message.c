#include "../headers/Message.h"

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
  if ((mq_connection->key = ftok(mq_connection->target_file, 'B')) == -1) {
    perror("ftok");
    exit(1);
  }

  //Connect to Queue
  if (sender_flag) { // sender creates the queue
    if ((mq_connection->msqid = msgget(mq_connection->key, 0664 | IPC_CREAT)) == -1) {
      perror("msgget");
      exit(1);
    }
  } else {
    if ((mq_connection->msqid = msgget(mq_connection->key, 0664)) == -1) {
      perror("msgget");
      exit(1);
    }
  }

	#if DEBUG
		printf("MessageQueueConnection successfully allocated and intitialized.  Returning...\n");
	#endif

	return mq_connection;
}


void send_node(MessageQueueConnection *mq_connection, Node *node) {
  struct message_struct message;

  if(msgsnd(mq_connection->msqid, &message, sizeof(message.node), 0) == -1) {
    perror("Error in msgsnd");
    exit(1);
  }
}


Node *recieve_node(MessageQueueConnection *mq_connection) {
  struct message_struct message;

  if (msgrcv(mq_connection->msqid, &message, sizeof(message.node), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
  }

  return message.node;
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
