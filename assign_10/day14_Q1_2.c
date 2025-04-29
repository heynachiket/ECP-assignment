#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 

int main()
{
int fd, num1, num2, sum;

mkfifo("cli_to_ser",0666);
mkfifo("ser_to_cli",0666);

fd = open("cli_to_ser",O_RDONLY);
read(fd,&num1,sizeof(num1));
read(fd,&num2,sizeof(num2));
close(fd);

sum = num1 + num2;

fd=open("ser_to_cli",O_WRONLY);
write(fd,&sum,sizeof(sum));
close(fd);

return 0;
}
