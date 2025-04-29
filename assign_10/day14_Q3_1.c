#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int nums[2], sum;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_fd, 1);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);

    read(client_fd, nums, sizeof(nums));
    sum = nums[0] + nums[1];
    write(client_fd, &sum, sizeof(sum));

    close(client_fd);
    close(server_fd);
    return 0;
}

