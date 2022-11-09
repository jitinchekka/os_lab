#include <stdio.h>
#include <stdlib.h>
// Shortest Job First non preemtive scheduling algorithm
struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
};
// sort using bubble sort according to arrival time if arrival time is same, sort according to burst time
void sort_sjf(struct process *p, int n)
{
	int i, j;
	struct process temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
			// if arrival time is same, sort according to burst time
			else if (p[j].at == p[j + 1].at)
			{
				if (p[j].bt > p[j + 1].bt)
				{
					temp = p[j];
					p[j] = p[j + 1];
					p[j + 1] = temp;
				}
			}
		}
	}
}
void display_sjf(struct process *p, int n)
{
	int i;
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	int avg_waiting_time = 0, avg_turnaround_time = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
		avg_waiting_time += p[i].wt;
		avg_turnaround_time += p[i].tat;
	}
	printf("Average turnaround time: %f\n", (float)avg_turnaround_time / n);
	printf("\nAverage waiting time: %f\n", (float)avg_waiting_time / n);
}
int main()
{
	int n, i;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	struct process *p = (struct process *)malloc(n * sizeof(struct process));
	for (i = 0; i < n; i++)
	{
		printf("Enter the details of process %d:\n", i + 1);
		printf("Enter the arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter the burst time: ");
		scanf("%d", &p[i].bt);
		p[i].pid = i + 1;
	}
	sort_sjf(p, n);
	int t = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (p[i].at <= t)
		{
			// pick the process with minimum burst time from the processes with arrival time less than or equal to current time
			int min = p[i].bt;
			int index = i;
			for (k = i; k < n; k++)
			{
				if (p[k].at <= t && p[k].bt < min)
				{
					min = p[k].bt;
					index = k;
				}
			}
			// swap the process with minimum burst time with the current process
			struct process temp = p[i];
			p[i] = p[index];
			p[index] = temp;
			// printf("Minimum burst time process %d is picked\n", p[i].pid);
			p[i].ct = t + p[i].bt;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			t += p[i].bt;
		}
		else
		{
			t = p[i].at;
			i--;
		}
	}
	display_sjf(p, n);
	return 0;
}