#ifndef MESSAGE
#define MESSAGE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "constants.h"
#include "DoublyLinkedList.h"
#include "Node.h"

struct message_struct {
  long mtype;
  Node *node;
};

typedef struct {
    key_t key;
    int msqid;
    char *target_file;
} MessageQueueConnection;

MessageQueueConnection *create_message_queue_connection(char *, int);
void send_node(MessageQueueConnection *, Node *);
Node *recieve_node(MessageQueueConnection *);
void end_msq_connection(MessageQueueConnection *);
void destroy_message_queue_connection(MessageQueueConnection *);

#endif
