// Implement the producer – consumer problem’s solution using semaphore. 
// Use one producer thread and one consumer thread. Also, clearly define the produce_item() function and consume_item() function. 
// The producer thread will produce an item and put it into the buffer.
// The consumer thread will consume an item from the buffer.
// The buffer is a shared resource between the producer and the consumer.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[10];
int start=0, end=0;
sem_t empty, full;
pthread_mutex_t mutex;
void *producer(void *param)
{
	int item;
	int i=0;
	while(i<10)
	{
		item = rand()%100;
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[end] = item;
		end = (end+1)%10;
		printf("Produced item: %d \n", item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		i++;
	}
}
void *consumer(void *param)
{
	int item;
	int i=0;
	while(i<10)
	{
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		item = buffer[start];
		start = (start+1)%10;
		printf("Consumed item: %d \n", item);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		i++;
	}
}

void main()
{
	pthread_t t1, t2;
	sem_init(&empty, 0, 10);
	sem_init(&full, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &producer, NULL);
	pthread_create(&t2, NULL, &consumer, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
}