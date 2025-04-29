#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t m;
pthread_cond_t cv;
int flag = 0;

void *thread_fun1(void *param){
	char str[] = "SUMBEAM\n";
	pthread_mutex_lock(&m);
	for(int i=0; str[i] != '\0';i++){
		write(1,str + i, 1);
		sleep(1);
	}
	flag = 1;
	pthread_cond_signal(&cv);
	pthread_mutex_unlock(&m);
	return NULL;
}

void *thread_fun2(void *param)
{
	char str[] = "INFOTECH\n";
	pthread_mutex_lock(&m);
	while(flag == 0)
		pthread_cond_wait(&cv, &m);
	for(int i = 0; str[i]!= '\0'; i++){
		write(1, str+ i, 1);
		sleep(1);
	}
pthread_mutex_unlock(&m);
return NULL;
}

int main(void){
pthread_t t1, t2;

pthread_mutex_init(&m, NULL);
pthread_cond_init(&cv, NULL);

pthread_create(&t1,NULL,thread_fun1,NULL);
pthread_create(&t2,NULL,thread_fun2,NULL);

pthread_join(t1,NULL);
pthread_join(t2,NULL);

pthread_cond_destroy(&cv);
pthread_mutex_destroy(&m);

return 0;
}
