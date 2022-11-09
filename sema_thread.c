// Given 2 threads, schedule the order of execution in such a way that Thread A has to wait for Thread B and vice versa. In other words, given the code below you must guarantee that Statement A1 happens before Statement B2 and Statement B1 happens before Statement A2.
// Thread1 - A1,A2
// Thread2 - B1, B2
// A1, B2 && B1, A2
// A1,B1,A2,B2
// B1,A1,B2,A2
// A1,B1,B2,A2 -- correct
// B1,A1,A2,B2 -- correct
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<stdbool.h>
sem_t s1, s2;

void thread_fn1(void *arg)
{
	sem_wait(&s1);
	// printf("Thread 1: Process ID: %d, Thread ID: %lu, S1: %d \n", getpid(), pthread_self(), s1);
	printf("A1\n");
	sem_post(&s2);
	sem_wait(&s1);
	printf("A2\n");
	// sem_post(&s2);
	return NULL;
}

void thread_fn2(void *arg)
{
	sem_wait(&s2);
	// printf("Thread 2: Process ID: %d, Thread ID: %lu, S2: %d \n", getpid(), pthread_self(), s2);
	printf("B1\n");
	sem_post(&s1);
	sem_wait(&s2);
	printf("B2\n");
	// sem_post(&s1);
	return NULL;
}

void main()
{
	pthread_t t1, t2;
	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 1);
	int first;
	printf("Which thread should run first? 1 or 2? ");
	scanf("%d", &first);
	if (first == 1)
	{
		pthread_create(&t1, NULL, &thread_fn1, NULL);
		pthread_create(&t2, NULL, &thread_fn2, NULL);
	}
	else
	{
		pthread_create(&t2, NULL, &thread_fn2, NULL);
		pthread_create(&t1, NULL, &thread_fn1, NULL);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	sem_destroy(&s1);
	sem_destroy(&s2);
}