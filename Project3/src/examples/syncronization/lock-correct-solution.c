#define _GNU_SOURCE

#include <stdio.h>
#include "mythreads.h"
#include <stdlib.h>
#include <pthread.h>

int max;
volatile int balance = 0;

//
// xchg(int *addr, int newval)
// return what is pointed to by addr
// at the same time, store newval into addr
// 
static inline uint xchg(volatile unsigned int *addr, unsigned int newval) {
	uint result;
	asm volatile("lock; xchgl %0, %1" : "+m" (*addr), "=a" (result) : "1" (newval) : "cc");
	return result;
}

volatile unsigned int mutex = 0;

void SpinLock(volatile unsigned int *lock) {
	while (xchg(lock, 1) == 1)
		; // spin
}

void SpinUnlock(volatile unsigned int *lock) {
	xchg(lock, 0);
}

void * mythread(void *arg) {
	char *letter = arg;
	//cpubind();
	printf("%s: begin\n", letter);
	int i;


	for (i = 0; i < max; i++) {
		SpinLock(&mutex);
		balance = balance + 1;
		SpinUnlock(&mutex);
	}

	printf("%s: done\n", letter);
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: main-first <loopcount>\n");
		exit(1);
	}
	max = atoi(argv[1]);

	pthread_t p1, p2;
	printf("main: begin [balance = %d]\n", balance);

	Pthread_create(&p1, NULL, mythread, "A");
	Pthread_create(&p2, NULL, mythread, "B");
	// join waits for the threads to finish

	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);

	printf("main: done\n\t[balance: %d]\n\t[should:  %d]\n",
		balance, max * 2);
	return 0;
}