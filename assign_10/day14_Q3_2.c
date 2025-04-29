#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    int nums[2], sum;

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Enter two numbers: ");
    scanf("%d %d", &nums[0], &nums[1]);

    write(sock_fd, nums, sizeof(nums));
    read(sock_fd, &sum, sizeof(sum));

    printf("Sum received from server: %d\n", sum);

    close(sock_fd);
    return 0;
}

