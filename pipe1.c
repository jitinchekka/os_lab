#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
// Write a program in which parent process takes one string as input. It is sent to child using pipe 1 and child will reverse it. Child process will send the reversed string to pareent using pipe 2. Parent will print the reversed string.
void main()
{
	int fd1[2], fd2[2], status;
	pid_t pid1;
	char msg1[20], msg2[20], readmsg[20];
	status = pipe(fd1);
	if (status == -1)
	{
		printf("\n----- Unable to create Pipe1 -------\n");
		return;
	}
	status = pipe(fd2);
	if (status == -1)
	{
		printf("\n----- Unable to create Pipe2 -------\n");
		return;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], readmsg, sizeof(readmsg));
		printf("This is the child process.\nReceived messgage from parent is %s\n", readmsg);
		// Reverse the string
		int i, j;
		for (i = 0, j = strlen(readmsg) - 1; i < j; i++, j--)
		{
			char temp = readmsg[i];
			readmsg[i] = readmsg[j];
			readmsg[j] = temp;
		}
		printf("Reversed string is %s\n", readmsg);
		write(fd2[1], readmsg, sizeof(readmsg));
	}
	else
	{
		printf("This is the parent process\n");
		printf("Enter the string\n");
		scanf("%s", msg1);
		write(fd1[1], msg1, sizeof(msg1));
		read(fd2[0], msg2, sizeof(msg2));
		printf("Received message from child is %s\n", msg2);
	}
}