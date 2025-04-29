#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>   

#define MSG_KEY 12345

struct msg_buffer {
    long msg_type;
    char fifo_name[256];
    char file_name[256];
};

int main() {
    int msgid, fifo_fd, bytes_read;
    struct msg_buffer message;
    char buffer[1024];
    FILE *input_file;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    if (msgrcv(msgid, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    input_file = fopen(message.file_name, "rb");
    if (!input_file) {
        perror("File open failed");
        exit(1);
    }

    if (mkfifo(message.fifo_name, 0666) == -1) {
        perror("mkfifo failed");
        exit(1);
    }

    fifo_fd = open(message.fifo_name, O_WRONLY);
    if (fifo_fd == -1) {
        perror("open failed");
        exit(1);
    }

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input_file)) > 0) {
        write(fifo_fd, buffer, bytes_read);
    }

    printf("File '%s' sent to client via FIFO '%s'.\n", message.file_name, message.fifo_name);

    close(fifo_fd);
    fclose(input_file);
    return 0;
}

