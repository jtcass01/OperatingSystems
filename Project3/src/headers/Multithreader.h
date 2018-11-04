#ifndef MULTITHREADER
#define MULTITHREADER

/* Compiler/OS Headers */
#include <pthread.h>
#include <assert.h>
#include <sched.h>

/* User Created Headers */
#include "constants.h"
#include "DoublyLinkedList.h"
#include "Node.h"
#include "FileParser.h"

void *sender_thread(void *);

void *worker_thread(void *);

void create_pThread(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);

void join_pThread(pthread_t, void**);

void create_map_threads(char *);

#endif