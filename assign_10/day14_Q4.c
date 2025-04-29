#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>

#define QUEUE_SIZE 5
#define SHM_KEY 12345
#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

struct circular_queue {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
};

void parent_process(int sem_id, struct circular_queue* queue) {
    srand(time(NULL));
    
    while (1) {
        int num = rand() % 100;
        struct sembuf sem_ops[2];

        sem_ops[0].sem_num = SEM_EMPTY;
        sem_ops[0].sem_op = -1;
        sem_ops[0].sem_flg = 0;

        sem_ops[1].sem_num = SEM_MUTEX;
        sem_ops[1].sem_op = -1;
        sem_ops[1].sem_flg = 0;

        semop(sem_id, sem_ops, 2);

        queue->queue[queue->rear] = num;
        queue->rear = (queue->rear + 1) % QUEUE_SIZE;

        printf("Parent: Added %d to queue\n", num);

        sem_ops[0].sem_num = SEM_MUTEX;
        sem_ops[0].sem_op = 1;
        sem_ops[0].sem_flg = 0;

        sem_ops[1].sem_num = SEM_FULL;
        sem_ops[1].sem_op = 1;
        sem_ops[1].sem_flg = 0;

        semop(sem_id, sem_ops, 2);

        sleep(1);
    }
}

void child_process(int sem_id, struct circular_queue* queue) {
    while (1) {
        struct sembuf sem_ops[2];

        sem_ops[0].sem_num = SEM_FULL;
        sem_ops[0].sem_op = -1;
        sem_ops[0].sem_flg = 0;

        sem_ops[1].sem_num = SEM_MUTEX;
        sem_ops[1].sem_op = -1;
        sem_ops[1].sem_flg = 0;

        semop(sem_id, sem_ops, 2);

        int num = queue->queue[queue->front];
        queue->front = (queue->front + 1) % QUEUE_SIZE;

        printf("Child: Removed %d from queue\n", num);

        sem_ops[0].sem_num = SEM_MUTEX;
        sem_ops[0].sem_op = 1;
        sem_ops[0].sem_flg = 0;

        sem_ops[1].sem_num = SEM_EMPTY;
        sem_ops[1].sem_op = 1;
        sem_ops[1].sem_flg = 0;

        semop(sem_id, sem_ops, 2);

        sleep(2);
    }
}

int main() {
    int shm_id = shmget(SHM_KEY, sizeof(struct circular_queue), 0666 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    struct circular_queue* queue = (struct circular_queue*)shmat(shm_id, NULL, 0);
    if (queue == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    queue->front = queue->rear = 0;

    int sem_id = semget(SHM_KEY, 3, 0666 | IPC_CREAT);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    semctl(sem_id, SEM_EMPTY, SETVAL, QUEUE_SIZE);
    semctl(sem_id, SEM_FULL, SETVAL, 0);
    semctl(sem_id, SEM_MUTEX, SETVAL, 1);

    pid_t pid = fork();
    
    if (pid == 0) {
        child_process(sem_id, queue);
    } else if (pid > 0) {
        parent_process(sem_id, queue);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}

