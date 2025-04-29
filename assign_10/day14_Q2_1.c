#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/msg.h>
#define MSG_KEY 12345

struct msg_buffer{
	long msg_type;
	char fifo_name[256];
	char file_name[256];
};

int main()
{
	int msgid;
	struct msg_buffer message;
	char buffer[1024];
	int fifo_fd,bytes_read;

	msgid=msgget(MSG_KEY, 0666 | IPC_CREAT);
	if(msgid == -1)
	{
		perror("msgget failed");
		_exit(1);
	}

	printf("Enter FIFO name: ");
	scanf("%s",message.fifo_name);
	printf("Enter file name :");
	scanf("%s",message.file_name);

	message.msg_type =1;
	if(msgsnd(msgid, &message,sizeof(message),0)== -1)
	{
		perror("msgsnd failed");
		_exit(1);
	}

	fifo_fd=open(message.fifo_name, O_RDONLY);
	if(fifo_fd == -1)
	{
		perror("file not open");
		_exit(1);
	}

	FILE *output_file = fopen("recived_file","wb");
	if(!output_file){
		perror("file open failed");
		_exit(1);
	}

	while((bytes_read = read(fifo_fd, buffer, sizeof (buffer)))>0){
		fwrite(buffer, 1, bytes_read, output_file);
	}

	printf("file received and saved as 'recivedd file'\n");

	close(fifo_fd);
	fclose(output_file);
	return 0;
}
