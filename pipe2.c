#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/times.h>

int main()
{
	int status;
	int fd1[2];
	int fd2[2];
	pid_t pid1, pid2;
	char msg1[20];
	char msg2[20];
	char readmsg[20];

	status = pipe(fd1);
	if (status == -1)
	{
		printf("\n----- Unable to create Pipe1 -------\n");
		return 1;
	}

	pid1 = fork();
	if (pid1 == 0)
	{
		status = pipe(fd2);
		if (status == -1)
		{
			printf("\n----- Unable to create Pipe2 -------\n");
			return 1;
		}
		int n1, n2;
		read(fd1[0], readmsg, sizeof(readmsg));
		n1 = strlen(readmsg);
		pid2 = fork();
		if (pid2 != 0)
		{
			// wait(NULL);
			read(fd2[0], readmsg, sizeof(readmsg));
			n2 = strlen(readmsg);
			printf("\nHello I am Child Process and my Parent Process Id is: %d ", getppid());
			printf("\nThe difference between lengths is : %d ", n1 - n2);
		}
		else
		{
			//   sleep(5);
			printf("\nHello I am Grand Child Process and my Parent Process Id is: %d ", getppid());
			printf("\nEnter the Grand Child Process String: ");
			scanf("%s", msg1);
			write(fd2[1], msg1, sizeof(msg1));
		}
	}
	else
	{
		printf("\nHello I am Parent Process and my Parent Process Id is: %d ", getppid());
		printf("\nEnter the Parent Process String: ");
		scanf("%s", msg1);
		write(fd1[1], msg1, sizeof(msg1));
		wait(NULL);
	}
	return 0;
}