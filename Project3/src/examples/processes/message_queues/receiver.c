#include "headers/message_queue.h"

int main(void) {
  MessageQueueConnection *msq_connection = create_message_queue_connection("sender.c", 0);

  Node *test_node = receive_node(msq_connection);
  print_node(test_node);
  delete_node(test_node);

  end_msq_connection(msq_connection);
  destroy_message_queue_connection(msq_connection);

  return 0;
}
