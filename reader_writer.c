// Implement the reader-writer problem’s solution using semaphore. Use one writer thread and multiple reader threads.
// Also, clearly define the reader() function and writer() function.
// Author: Jitin
// Roll No: CS20B1075
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

sem_t mutex, wrt;
int readcount = 0;
int global = 0; //shared data between reader and writer
int rep;
void *reader(void *arg)
{
	int temp = rep;
	while (temp--)
	{
		int f;
		f = ((int)arg);
		sem_wait(&mutex);
		readcount++;
		if (readcount == 1)
			sem_wait(&wrt);
		sem_post(&mutex);
		printf("Data read by the reader %d is %d \n", f, global);
		sleep(1);
		sem_wait(&mutex);
		readcount--;
		if (readcount == 0)
			sem_post(&wrt);
		sem_post(&mutex);
	}
}

void *writer(void *arg)
{
	int temp = rep;
	while (temp--)
	{
		int f;
		f = ((int)arg);
		sem_wait(&wrt);
		global++;
		printf("Data writen by the writer is %d \n", global);
		sleep(1);
		sem_post(&wrt);
	}
}

void main()
{
	int i, b;
	pthread_t rtid[5], wtid;
	sem_init(&mutex, 0, 1);
	sem_init(&wrt, 0, 1);
	int n;
	printf("Enter the number of readers: ");
	scanf("%d", &n);
	printf("Enter the number of times the reader and writer should repeat: ");
	scanf("%d", &rep);
	pthread_create(&wtid, NULL, writer, (void *)0);
	for (i = 0; i < n; i++)
	{
		pthread_create(&rtid[i], NULL, reader, (void *)i);
	}
	pthread_join(wtid, NULL);
	for (i = 0; i <= 2; i++)
	{
		pthread_join(rtid[i], NULL);
	}
	sem_destroy(&mutex);
	sem_destroy(&wrt);
}