#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSG_KEY 0x1234

typedef struct msg{
	long mtype;
	char text[20];
}msg_t;

int main()
{
	int pid,status,err;
	msg_t m1,m2,m3;
	int msgid = msgget(MSG_KEY, IPC_CREAT | 0600);
	if(msgid == -1){
		printf("msgget() is failed \n");
		_exit(1);
	}
	printf("program started\n");
	pid=fork();
	if(pid==0)
	{
		printf("Enter both numbers : ");
		scanf("%[^\n]s", m1.text);
		m1.mtype = 11;

		err= msgsnd(msgid, &m1,sizeof(m1.text),0);
		if(err == -1){
			printf("child message failed\n");
			_exit(1);
		}

		err=msgrcv(msgid, &m3, sizeof(m3.text),22,0);
		if(err == -1)
		{
			printf("res reciving failed\n");
			_exit(1);
		}
		else
		{
			int result = atoi(m3.text);
	        printf("result : %d\n", result);
		}
		_exit(0);
	}
	else
	{
		err=msgrcv(msgid, &m2, sizeof(m2.text),11,0);
		if(err == -1)
		{
			printf("meggase not recived sucessfully\n");
			_exit(1);
		}
		else
		{
			int num1, num2, res;
			sscanf(m2.text, "%d %d", &num1, &num2); 
			res = num1 + num2;
			sprintf(m3.text,"%d",res);
			m3.mtype = 22;
			err=msgsnd(msgid, &m3, sizeof(m3.text),0);
			if(err == -1){
				printf("res not sent\n");
				_exit(1);
			}
		}
		waitpid(pid, &status, 0);
	}
printf("program ended\n");
	return 0;
}
