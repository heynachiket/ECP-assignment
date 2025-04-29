#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[2];
    int pid1, pid2;
    int s1, s2;

    pipe(arr);

    pid1 = fork();
    if (pid1 == 0) {
        close(arr[0]);
        dup2(arr[1], STDOUT_FILENO);
        close(arr[1]);
        execlp("who", "who", NULL);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(arr[1]);
        dup2(arr[0], STDIN_FILENO);
        close(arr[0]);
        execlp("wc", "wc", NULL);
        exit(1);
    }

    close(arr[0]);
    close(arr[1]);

    waitpid(pid1, &s1, 0);
    waitpid(pid2, &s2, 0);

    return 0;
}

