// In each process, define an array of integers using malloc. Take the size of the array from the user and Insert values in your array (size and array elements may be different for both processes).

// (i) Parent Process:-

// (a) Print the array elements and their address,

// (b)sort the array and print its values.

// (ii) Child Process:-

// (a)Print the array elements and their address.

// (b) Reverse the array and print its values.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void main()
{
	pid_t pid;

	pid = fork();
	wait(NULL);

	if (pid < 0)
	{
		printf("Error");
	}
	else if (pid == 0)
	{
		printf("\nChild print : \n");
		int size;
		printf("Enter the size of the array : ");
		scanf("%d", &size);
		int *array = (int *)malloc(sizeof(int) * size);
		printf("\nEnter the elements of the array (bit by bit) : ");
		for (int i = 0; i < size; i++)
		{
			scanf("%d", &array[i]);
		}
		printf("Parent id : %d , Process : %d", getppid(), getpid());
		printf("\nThe elements of the array are : ");
		for (int i = 0; i < size; i++)
		{
			printf("%d ", array[i]);
		}
		printf("\nThe address of the array is : ");
		for (int i = 0; i < size; i++)
		{
			printf("%p ", &array[i]);
		}

		int temparray[size];
		printf("\nThe reversed array is : ");
		for (int i = 0; i < size; i++)
		{
			temparray[i] = array[size - i - 1];
			printf("%d ", temparray[i]);
		}
	}
	else if (pid > 0)
	{
		printf("\nParent print : \n");
		int size;
		printf("Enter the size of the array : ");
		scanf("%d", &size);
		int *array = (int *)malloc(sizeof(int) * size);
		printf("\nEnter the elements of the array (bit by bit) : ");
		for (int i = 0; i < size; i++)
		{
			scanf("%d", &array[i]);
		}
		printf("Parent id : %d , Process : %d", getppid(), getpid());
		printf("\nThe elements of the array are : ");
		for (int i = 0; i < size; i++)
		{
			printf("%d ", array[i]);
		}
		printf("\nThe address of the array is : ");
		for (int i = 0; i < size; i++)
		{
			printf("%p ", &array[i]);
		}
		printf("\n");

		int temp;
		temp = array[0];
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1 - i; j++)
			{
				if (array[j] > array[j + 1])
				{
					temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
				}
			}
		}
		printf("\nThe sorted array is : ");
		for (int i = 0; i < size; i++)
		{
			printf("%d ", array[i]);
		}
	}
}