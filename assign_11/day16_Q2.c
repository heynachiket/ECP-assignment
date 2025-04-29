#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *thread_fun(void *param)
{
	int *arr = (int *)param;
	int i, j, min, temp;

	for(i=0; i<9;i++){
		min = i;
		for(j=i+1; j<10; j++){
			if(arr[j]< arr[min]){
				min=j;
			}
		}
		temp = arr[i];
		arr[i] = arr[min];
		arr[min]=temp;
	}
	return NULL;
}

int main(void){

	pthread_t th1;
	int err;
	int arr[10]={29, 10, 14, 37, 13, 5, 8, 19, 22, 1};

	err = pthread_create(&th1, NULL, thread_fun, (void *)arr);
	if(err != 0){
		perror("thread is not created");
		_exit(0);
	}

	pthread_join(th1, NULL);

	printf("sorted array : ");
	for(int i = 0; i < 10; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}
