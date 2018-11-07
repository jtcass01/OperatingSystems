#ifndef MULTITHREADER
#define MULTITHREADER

/* Compiler/OS Headers */
#include <pthread.h>
#include <assert.h>
#include <sched.h>
#include <semaphore.h>

/* Function Prototypes */
void create_pThread(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);

void join_pThread(pthread_t, void**);

#endif