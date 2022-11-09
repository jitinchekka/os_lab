// Round robin scheduling algorithm for n processes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int response_time;
	int rt; // remaining time
	int flag;
};
int inQueue[MAX] = {0};
int context_switch_overhead = 0;
struct process p[MAX];
// Implement queue using linked list
struct node
{
	int process_index;
	struct node *next;
};
struct node *front = NULL, *rear = NULL;
void enqueue(int process_index)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->process_index = process_index;
	temp->next = NULL;
	if (front == NULL)
	{
		front = temp;
		rear = temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}
int dequeue()
{
	int process_index;
	if (front == NULL)
	{
		printf("Queue is empty\n");
		exit(0);
	}
	else
	{
		process_index = front->process_index;
		struct node *temp = front;
		front = front->next;
		free(temp);
	}
	return process_index;
}
void display_queue()
{
	struct node *temp = front;
	while (temp != NULL)
	{
		printf("%d ", p[temp->process_index].pid);
		temp = temp->next;
	}
	printf("\n");
}
void display()
{
	struct node *temp = front;
	while (temp != NULL)
	{
		printf("%d ", temp->process_index);
		temp = temp->next;
	}
	printf("\n");
}

void sort(int n)
{
	int i, j;
	struct process temp;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}
void display_process(int n)
{
	int i;
	printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].response_time);
	}
}

void round_robin(int n, int time_quantum, int context_switch_overhead)
{
	int i = 0, j = 0, count = 0, time = 0, total_time = 0, total_wait = 0, total_turnaround = 0, total_response = 0;
	for (i = 0; i < n; i++)
	{
		p[i].rt = p[i].bt;
		p[i].flag = 0;
	}
	for (i = 0; i < n; i++)
	{
		if (p[i].at <= time)
		{
			enqueue(i);
		}
	}
	// Print the process details before scheduling
	// printf("\nBefore scheduling\n");
	// display_queue();
	// printf("\n");
	// Start scheduling
	while (front != NULL)
	{
		int index = dequeue();
		inQueue[index] = 0;
		// Calculate response time
		if (p[index].response_time == -1)
			p[index].response_time = time; // the time when it first got executed
		if (p[index].rt > time_quantum)
		{
			time += time_quantum;
			p[index].rt -= time_quantum;
			// printf("rt = %d\n", p[index].rt);
		}
		else
		{
			time += p[index].rt;
			p[index].rt = 0;
			inQueue[index] = 1;
			p[index].ct = time;
			p[index].tat = p[index].ct - p[index].at;
			p[index].wt = p[index].tat - p[index].bt;
			p[index].flag = 1;
			// total_time += p[index].tat;
			// total_wait += p[index].wt;
			// total_turnaround += p[index].tat;
			// count++;
		}

		for (j = 0; j < n; j++)
		{
			// if not in queue and not executed and arrival time is less than or equal to current time
			if (p[j].flag == 0 && p[j].at <= time && j != index && inQueue[j] == 0)
			{
				enqueue(j);
				inQueue[j] = 1;
			}
		}
		if (p[index].rt > 0)
		{
			enqueue(index);
			inQueue[index] = 1;
		}
		printf("pid =%d Index =%d rt=%d time=%d\n", p[index].pid, index, p[index].rt, time);
	}

	// Calculate response time
	for (int i = 0; i < n; i++)
	{
		p[i].response_time = p[i].response_time - p[i].at;
	}

	for (i = 0; i < n; i++)
	{
		if (p[i].flag == 1)
		{
			count++;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (p[i].flag == 1)
		{
			total_time += p[i].bt;
			total_wait += p[i].wt;
			total_turnaround += p[i].tat;
			total_response += p[i].response_time;
		}
	}
	printf("\n\nAverage waiting time: %f\n", (float)total_wait / count);
	printf("Average turnaround time: %f\n", (float)total_turnaround / count);
	printf("Average response time: %f\n", (float)total_response / count);
}

void main()
{
	int i;
	int time_quantum;
	int n;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the details of the processes\n");
	for (i = 0; i < n; i++)
	{
		printf("Enter the pid, arrival time and burst time of process %d\n", i + 1);
		scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
		p[i].ct = 0;
		p[i].tat = 0;
		p[i].wt = 0;
		p[i].response_time = -1;
		p[i].rt = 0;
		p[i].flag = 0;
	}
	printf("Enter the time quantum\n");
	scanf("%d", &time_quantum);
	printf("Enter the context switch overhead\n");
	scanf("%d", &context_switch_overhead);
	sort(n);
	round_robin(n, time_quantum, context_switch_overhead);
	display_process(n);
}