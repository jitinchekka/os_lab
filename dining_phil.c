// Implement dining philosopher problem using semaphores.
// Consider there are 5 philosophers and define each philosopher using a thread. You must consider three states: THINKING, HUNGRY, and EATING for each philosphers. Properly define the eating and thinking functions.
// Your code must ensure that at a time two philosophers can eat their meal.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define n 5
#define think 2
#define hun 1
#define eat 0
#define l (no_phi + 4) % n
#define r (no_phi + 1) % n

int act[n];
int phi[n] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[n];

void check(int no_phi)
{
	if (act[no_phi] == hun && act[l] != eat && act[r] != eat)
	{
		act[no_phi] = eat;

		sleep(2);

		printf("philosopher %d took fork from %d and %d\n", no_phi + 1, l + 1, no_phi + 1);

		printf("philosopher %d is eating\n", no_phi + 1);
		sem_post(&S[no_phi]);
	}
}

void take_fork(int no_phi)
{

	sem_wait(&mutex);
	act[no_phi] = hun;

	printf("philosopher %d is hungry\n", no_phi + 1);
	check(no_phi);

	sem_post(&mutex);
	sem_wait(&S[no_phi]);

	sleep(1);
}

void fork_down(int no_phi)
{

	sem_wait(&mutex);
	act[no_phi] = think;

	printf("philosopher %d putting fork %d and %d down\n", no_phi + 1, l + 1, no_phi + 1);
	printf("philosopher %d is thinking\n", no_phi + 1);

	check(l);
	check(r);

	sem_post(&mutex);
}

void *philosopher(void *num)
{

	while (1)
	{
		int *i = num;

		sleep(1);

		take_fork(*i);

		sleep(0);

		fork_down(*i);

		break;
	}
}

int main()
{
	int i;
	pthread_t thread_id[n];
	sem_init(&mutex, 0, 1);

	for (i = 0; i < n; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < n; i++)
	{

		pthread_create(&thread_id[i], NULL, philosopher, &phi[i]);

		printf("philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < n; i++)
	{
		pthread_join(thread_id[i], NULL);
		pthread_mutex_destroy(&mutex);
		sem_destroy(&S[n]);
	}
}