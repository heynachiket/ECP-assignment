#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

struct array{
	int *arr;
	int size;
};

void* thread_fun(void* param){
	struct array* a = (struct array*) param;
	int* arr = a->arr;
	int n = a->size;

	for(int i= 0; i<n-1;i++){
		for(int j =0 ; j<n-i-1; j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j];
				arr[j]= arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
	pthread_exit(NULL);
}

int main(void){
	int n;

	printf("Enter number of elements : ");
	scanf("%d",&n);

	int *arr = (int *)malloc(n * sizeof(int));
	if(arr == NULL){
		perror("malloc failed");
		return 1;
	}

	printf("Enter %d elements: ",n);
	for(int i= 0; i <n; i++){
		scanf("%d",&arr[i]);
	}

	struct array a;
	a.arr = arr;
	a.size = n;

	pthread_t tid;
	if(pthread_create(&tid, NULL, thread_fun, &a)!=0){
		perror("pthread_create failed");
		free(arr);
		return 1;
	}

	pthread_join(tid, NULL);

	printf("sorted array : \n");
	for(int i= 0;i<n; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
	free(arr);
	return 0;
}
