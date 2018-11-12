#include "headers/message_queue.h"

#define MESSAGESIZE 128

int main(void) {
  MessageQueueConnection *msq_connection = create_message_queue_connection("sender.c", 1);

  Node *test_node = create_node("Hello world : )\n");

  send_node(msq_connection, test_node);

  destroy_message_queue_connection(msq_connection);
  delete_node(test_node);

  return 0;
}
