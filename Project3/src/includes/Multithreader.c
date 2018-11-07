#include "../headers/Multithreader.h"

void create_pThread(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
	int rc = pthread_create(thread, attr, start_routine, arg);
	assert(rc == 0);
}

void join_pThread(pthread_t thread, void**value_ptr) {
	int rc = pthread_join(thread, value_ptr);
	assert(rc == 0);
}