#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
# define buffer_size 10

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int buffer[buffer_size];
int counter;
pthread_t tid;


void initialize(){
    pthread_mutex_init(&mutex,  NULL);
    sem_init(&full,0,0);
    sem_init(&empty,0,buffer_size);
    counter=0;
}

void *producer(void* param){
  int item,waittime;
  waittime = rand()%5;
  sleep(waittime);
  item=rand()%10;
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  printf("producer produced item %d \n",item);
  insert_item(item);
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
}

void *consumer(void* param){
      int item,waittime;
  waittime = rand()%5;
  sleep(waittime);
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  item=remove_item();
  printf("consumer consumed  item %d \n",item);
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
    
}

void insert_item(int item){
    buffer[counter++]=item;
}

int remove_item(){
    return(buffer[--counter]);
}

int main(){

    int n1,n2;
    int i;
    printf("enter number of producers");
    scanf("%d",&n1);
    printf("enter number of consumer");
    scanf("%d",&n2);
    initialize();

    for(i=0;i<n1;i++){
        pthread_create(&tid,NULL,producer,NULL);
    }
    for(i=0;i<n2;i++){
        pthread_create(&tid,NULL,consumer,NULL);
    }
   sleep(10);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
