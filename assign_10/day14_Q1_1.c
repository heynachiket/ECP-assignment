#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>  
#include <sys/stat.h>   
#include <fcntl.h> 

int main()
{
int fd, num1, num2, result;

mkfifo("cli_to_ser",0666);
mkfifo("ser_to_cli",0666);

printf("Enter two numbers : \n");
scanf("%d %d",&num1,&num2);

fd= open("cli_to_ser", O_WRONLY);
write(fd, &num1, sizeof(num1));
write(fd, &num2, sizeof(num2));
close(fd);

fd=open("ser_to_cli", O_RDONLY);
read(fd,&result, sizeof(result));
close(fd);

printf("sum of numbers : %d \n",result);

return 0;
}
