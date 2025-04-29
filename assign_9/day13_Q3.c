#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd[2];
    pipe(fd); 
	int size = fcntl(fd[1], F_GETPIPE_SZ);  
    printf("Pipe buffer size: %d bytes\n", size);

    return 0;
}

