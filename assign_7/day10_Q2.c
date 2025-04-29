#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int ret, s1, s2, s3, s4, s5, pid1, pid2, pid3, pid4, pid5;
	printf("program started \n");

	pid1 = fork();
	if(pid1 == 0)
	{
		pid2 = fork();
		if(pid2 == 0)
		{
			pid3 = fork();
			if(pid3 == 0)
			{
				pid4 = fork();
				if(pid4 == 0)
				{
					pid5 = fork();
					if(pid5 == 0)
					{	
						char *args[]={"./program.out",NULL};
						ret=execv("./program.out", args);
						if(ret == -1){
							printf("execl 5() is failed\n");
							_exit(ret);
						}
						waitpid(pid5,&s5,0);
						sleep(1);
					}

					else
					{
						char *args[]={"gcc","-o","program.out","circle.o","square.o","rectangle.o","main.o",NULL};
						ret=execv("/usr/bin/gcc", args);
						if(ret == -1){
							printf("execl5() is failed\n");
							_exit(ret);
						}
						waitpid(pid4,&s5,0);
						sleep(1);
					}
				}

				else
				{
					char *args[]={"gcc", "-c", "main.c",NULL};
					ret=execv("/usr/bin/gcc", args);
					if(ret == -1){
						printf("execl4() is failed\n");
						_exit(ret);
					}
					waitpid(pid4,&s4,0);
					sleep(1);
				}
			}

			else
			{
				char *args[]={"gcc", "-c", "rectangle.c",NULL};
				ret=execv("/usr/bin/gcc", args);
				if(ret == -1){
					printf("execl3() is failed\n");
					_exit(ret);
				}
				waitpid(pid3,&s3,0);
			}
		}

		else
		{
			char *args[]={"gcc", "-c", "square.c",NULL};
			ret=execv("/usr/bin/gcc", args);
			if(ret == -1){
				printf("execl2() is failed\n");
				_exit(ret);
			}
			waitpid(pid2,&s2,0);
		}
	}

	else
	{
		char *args[]={"gcc", "-c", "circle.c",NULL};
		ret=execv("/usr/bin/gcc", args);
		if(ret == -1){
			printf("execl1() is failed\n");
			_exit(ret);
		}
		waitpid(pid1,&s1,0);
	}

	printf("progran ended\n");
	return 0;
}
