//  Write a two C program(Process1.c and Process2.c) using the shared memory concept.

// Process1:- generates a string and sends it to the shared memory region.

// Process2:- read this string and append another string and write in shared memory.

// Process1:- Read the shared Memory written by Process2
// Sever
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	char *str;
	key_t key = 1075;
	int shmid = shmget((key_t)key, 1024, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		printf("Not able to create a shared memory\n");
		exit(0);
	}
	printf("ID of shared memory is %d\n", shmid);
	str = shmat(shmid, NULL, 0);
	printf("SM is attached to %p in sender\n", str);
	if (str == (char *)-1)
	{
		printf("Not able to attach a shared memory to address space \n ");
		exit(1);
	}
	int n;
	printf("Enter n\n");
	scanf("%d", &n);
	getchar();
	str[1] = (char)n;
	for (int i = 0; i < n; i++)
	{
		*str = '*';
		printf("Server side\nEnter a string\n");
		// char mystr[100]
		// getchar();
		scanf("%s", str + 2);
		printf("String in server side is %s\n", str + 2);
		while (*str != '#')
			sleep(1);
		printf("String sent by client is %s\n", str + 2);
	}
	return 0;
}