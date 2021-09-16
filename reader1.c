#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t wrt;
pthread_mutex_t mutex;
int count = 1, numreader = 0;
key_t key;
int shmid;

void *writer()
{
    sem_wait(&wrt);
    key = ftok("shmfile",65);
    shmid = shmget(key,1024,0666|IPC_CREAT);
    int *num = (int*) shmat(shmid,(void*)0,0);
    count++;
    *num = count;
    printf("Data written in memory: %d\n",count);
    shmdt(num);
    sem_post(&wrt);
}
void *reader()
{
	
    pthread_mutex_lock(&mutex);     
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); 
    }
    if(numreader == 2) {
        sleep(1); }
    
    pthread_mutex_unlock(&mutex);
    key = ftok("shmfile",65);
    shmid = shmget(key,1024,0666|IPC_CREAT);
    int* num = (int*) shmat(shmid,(void*)0,0);
    printf("Reader %d read data from memory: %d\n",numreader,count);
    shmdt(num);
    pthread_mutex_lock(&mutex);    
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt);         
    }
    pthread_mutex_unlock(&mutex);
}

void main()
{
    pthread_t read[100],write[100];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);
    int rnum, wnum;
    printf("Enter the number of readers : ");
    scanf("%d", &rnum);
    printf("\nEnter the number of writers : ");
    scanf("%d", &wnum);
    printf("\n");
    for(int i = 0; i < rnum; i++) {
        pthread_create(&read[i], NULL, (void *)reader, NULL);
    }
    for(int i = 0; i < wnum; i++) {
        pthread_create(&write[i], NULL, (void *)writer, NULL);
    }

    for(int i = 0; i < rnum; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < wnum; i++) {
        pthread_join(write[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    shmctl(shmid,IPC_RMID,NULL);
    pthread_exit(NULL);

}
