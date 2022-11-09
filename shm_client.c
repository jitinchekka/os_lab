// Client
// Reader or client
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
	int n;
	int shmid = shmget((key_t)1075, 1024, 0666);
	if (shmid < 0)
	{
		perror("Error with SHM");
		exit(0);
	}
	char *str = shmat(shmid, NULL, 0);
	if (str == (char *)(-1))
	{
		perror("Error with shmat");
		exit(1);
	}
	char ch = str[0];
	n = str[1];
	for (int i = 0; i < n; i++)
	{
		printf("This is client.\nEnter the string to concatenate\n");
		char mystr[100];
		//  getchar();
		scanf("%s", mystr);
		strcat(str + 2, mystr);
		printf("Concatenated string is %s\n", str + 2);
		str[0] = '#';
		if (i == n - 1)
		{
			continue;
		}
		while (str[0] != '*')
			sleep(1);
	}
	shmdt(str);
	shmctl(shmid, IPC_RMID, NULL);
}