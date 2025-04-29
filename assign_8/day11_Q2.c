#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

int a;
int main(void)
{
	char cmd[264], *args[32], *ptr;
	while(1)
	{
		printf("cmd> ");
		gets(cmd);

		int i = 0;
		ptr = strtok(cmd, " ");
		args[i] = ptr;
		do{
			i++;
			a = i;
			ptr = strtok(NULL, " ");
			args[i] = ptr;
		}while(ptr != NULL);
		int b = a-1;
		int is_async = 0;
		if(strcmp(args[b],"&") == 0)
		{
			args[b]=NULL;
			is_async = 1;
		}
		if(is_async)
		{
			printf("inside asynchronous\n");
			if(strcmp(args[0], "cd")== 0)
			{
				chdir(args[1]);
			}
			else if(strcmp(args[0], "exit")== 0)
			{
				_exit(0);
			}
			else
			{
				int pid = fork();
				if(pid==0)
				{
					int err = execvp(args[0],args);
					if(err < 0){
						printf("%s commant is failed\n",args[0]);
						_exit(-1);
					}
					exit(1);
				}
				else{
				sleep(1);
				}


			}
		}
		else
		{	
			printf("inside synchronous\n");
			if(strcmp(args[0], "cd") == 0)
			{
				chdir(args[1]);
			}
			else if(strcmp(args[0], "exit")== 0)
			{
				_exit(0);
			}
			else
			{
				int pid = fork();
				if(pid==0)
				{
					int err = execvp(args[0],args);
					if(err < 0){
						printf("%s commant is failed\n",args[0]);
						_exit(-1);
					}
				}
				else{
					int s;
					waitpid(pid, &s, 0);
				}
			}
		}
	}
	return 0;
}
