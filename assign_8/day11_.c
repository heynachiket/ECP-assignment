#include<stdio.h>
#include<string.h>

int v;

int main()
{
	char str[50], *ptr, *argv[50];
	printf("Enter string : \n");
	scanf("%[^\n]s",str);

	printf("Entered string : %s\n",str);

	int i=0;

	ptr = strtok(str, " ");
	argv[i]=ptr;
	do{
		i++;
		v = i;
		ptr = strtok(NULL, " ");
		argv[i] = ptr;
	}while(ptr != 0);

	int a=0;
	while(argv[a]!= NULL)
	{
		printf("argv[%d] : %s\n",a,argv[a]);
		a++;
	}
	int l = v -1;
	if(strcmp(argv[l],"desd")==0)
	{
		printf("last same\n");
	}
	else
	{
		printf("last not same\n");
	}
	return 0;
}
