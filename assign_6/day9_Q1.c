#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	int ret,i,s;
	printf("program started\n");
	for(i=1;i<=5;i++){
		ret = fork();
		if(ret == 0)
		{
			printf("pid of child  = %d\n",getpid());
			for(int a=1;a<=5;a++){
				printf("child %d : running = %d \n",i,a);
			}
			_exit(0);
		}
	
		else
		{
			printf("pid of parent : %d \n",getpid());
			waitpid(ret,&s,0);
		}
	}
printf("program ended..\n");
	return 0;
}
