#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
	int pipe1[2],pipe2[2];
	int pid,status;
	char msg1[20], msg2[20];
	pipe(pipe1);
	pipe(pipe2);

	printf("program stsrted\n");

	pid=fork();
	if(pid == 0)
	{
		close(pipe1[0]);
		close(pipe2[1]);
		printf("Enter both number : ");
		scanf("%[^\n]s",msg1);
		write(pipe1[1], msg1, sizeof(msg1));
		read(pipe2[0], msg2, sizeof(msg2));
		printf("sum : %s\n",msg2);
		close(pipe1[1]);
		close(pipe2[0]);

	}
	else
	{
		close(pipe1[1]);
		close(pipe2[0]);
		read(pipe1[0], msg1, sizeof(msg1));

		int num1,num2,res;
		sscanf(msg1,"%d %d",&num1, &num2);

		int sum = num1 + num2;
		sprintf(msg2,"%d",sum);

		write(pipe2[1], msg2, sizeof(msg2));
		wait(&status);

		close(pipe1[0]);
		close(pipe2[1]);
	}

	return 0;
}
