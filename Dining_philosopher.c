#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define N 5

pthread_mutex_t forks[N];
sem_t room;
void *philosopher(void *arg){
    int id = (int)arg;
    while(1){
        usleep((rand()%500+500)*1000);
        sem_wait(&room);
        pthread_mutex_lock(&forks[id]);
        pthread_mutex_lock(&forks[(id+1)%N]);
        usleep((rand()%300+200)*1000);
        pthread_mutex_unlock(&forks[(id+1)%N]);
        pthread_mutex_unlock(&forks[id]);
        sem_post(&room);
        usleep((rand()%500+200)*1000);
    }
    return NULL;
}

int main(int argc,char **argv){
    int n = N;
    if(argc>1) n = atoi(argv[1])>1?atoi(argv[1]):N;
    pthread_t th[n];
    int ids[n];
    srand(time(NULL));
    sem_init(&room,0,n-1);
    for(int i=0;i<n;i++) pthread_mutex_init(&forks[i],NULL);
    for(int i=0;i<n;i++){
        ids[i]=i;
        pthread_create(&th[i],NULL,philosopher,&ids[i]);
    }
    for(int i=0;i<n;i++) pthread_join(th[i],NULL);
    for(int i=0;i<n;i++) pthread_mutex_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}
