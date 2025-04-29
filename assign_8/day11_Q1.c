#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sigint_handler(int sig)
{

}

int main(void)
{
int i = 1;
signal(SIGINT, sigint_handler);
while(1)
{
	printf("running : %d\n",i);
	i++;
	sleep(1);
}
return 0;
}
