// OS lab-2
// Author: Jitin CS20B1075
#include <stdio.h>
#include <stdlib.h>
struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
};
// sort using bubble sort by arrival time
void sort(struct process *p, int n)
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
		}
	}
}
float *display(struct process *p, int n)
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
	printf("Average waiting time: %f\n", (float)avg_waiting_time / n);
	float *arr = (float *)malloc(2 * sizeof(float));
	arr[0] = avg_turnaround_time;
	arr[1] = avg_waiting_time;
	return arr;
}

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
float *display_sjf(struct process *p, int n)
{
	printf("\nUsing Shortest Job First Algorithm\n");
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
	printf("Average waiting time: %f\n\n", (float)avg_waiting_time / n);
	float *avg = (float *)malloc(2 * sizeof(float));
	avg[0] = avg_turnaround_time;
	avg[1] = avg_waiting_time;
	return avg;
}

// FCFS
float *fcfs(struct process *p, int n)
{
	sort(p, n);
	int t = 0, j = 0, k = 0;
	int i;
	for (i = 0; i < n; i++)
	{
		if (p[i].at <= t)
		{
			p[i].ct = t + p[i].bt;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			t = p[i].ct;
			j++;
		}
		else
		{
			p[i].ct = p[i].at + p[i].bt;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			t = p[i].ct;
			k++;
		}
	}
	printf("\nThe scheduling algorithm is First Come First Serve\n");
	return display(p, n);
}

float *sjf(struct process *p, int n)
{
	sort_sjf(p, n);
	int t = 0, k = 0;
	int i;
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
	return display_sjf(p, n);
}
int main()
{
	int i, n;
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
	float *avg_fcfs = fcfs(p, n);
	float *avg_sjf = sjf(p, n);
	// Printing optimal TAT
	if (avg_fcfs[0] < avg_sjf[0])
	{
		printf("FCFS is optimal in terms of TAT\n");
	}
	else
	{
		printf("SJF is optimal in terms of TAT\n");
	}

	// Print optimal in terms of WT
	if (avg_fcfs[1] < avg_sjf[1])
	{
		printf("FCFS is optimal in terms of WT\n");
	}
	else
	{
		printf("SJF is optimal in terms of WT\n");
	}

	printf("Time complexity of FCFS is O(n^2)\n");
	printf("Time complexity of SJF is O(n^2)");
}
