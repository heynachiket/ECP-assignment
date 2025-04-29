#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

typedef struct{
	int start;
	int end;
	int result;
}sumargs;

void *sum_range(void *args){
	sumargs* data = (sumargs*)args;
	data->result =0;
	for(int i = data->start; i<= data->end; i++){
		data->result += i;
	}
	return NULL;
}

int main()
{
pthread_t thread;
sumargs args = {1,100,0};
pthread_create(&thread, NULL, sum_range, &args);
pthread_join(thread, NULL);
printf("sum for ramge %d to %d is : %d\n",args.start,args.end,args.result);
return 0;
}
