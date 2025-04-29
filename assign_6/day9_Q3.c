#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret,count=1;
	printf("program started..\n");
	while(1)
	{
		ret=fork();
		if(ret == -1){
			printf("fork failed..\n");
			_exit(0);
		}
		else if(ret ==0)
		{
			for(int i=1;i<=5;i++)
			{
				sleep(1);
			}
			_exit(0);
		}
		else
		{
			printf("count : %d\n",count);
			count++;
		}

	}

	return 0;
}
