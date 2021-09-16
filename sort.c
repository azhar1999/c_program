#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define MAX 20

int n;

int array[MAX];

   

void swap(int a , int b){
	
    if(a==b){
        return;
    }
    int temp=array[a];
    array[a]=array[b];
    array[b]=temp;
}

void selection_sort(int first,int last){
    for(int i=first;i<last;i++){
        int min=i;
        for(int j=i;j<last;j++){
            if(array[j]<array[min]){
                min=j;
            }
        }
        swap(i,min);
    }
}

void *func(void * num){
    int *a= (int*) num;
    if(*a==1){
        selection_sort(0,n/2);
    }
    else{
        selection_sort(n/2,n);
    }
    pthread_exit(NULL);
    return NULL;
}

int main(){
    printf("\nEnter n : ");
    scanf("%d",&n);
    printf("\nEnter elements : \n ");
    for(int i=0;i<n;i++){
        scanf("%d",&array[i]);
    }
   
    pthread_t thread1,thread2;
    int a=1,b=2;
    int *num1=&a,*num2=&b;
    pthread_create(&thread1,NULL,func,(void *)num1);
    pthread_create(&thread2,NULL,func,(void *)num2);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    a=0;
    b=n/2;
    int c=0;
    int result[20];
    while(a<n/2 && b<n){
        if(array[a]<array[b]){
            result[c]=array[a];
            c++;
            a++;
        }
        else{
            result[c]=array[b];
            c++;
            b++;
        }
    }
    while(a<n/2){
        result[c]=array[a];
        c++;
        a++;
    }
    while(b<n){
        result[c]=array[b];
        c++;
        b++;
    }
   
    for(int i=0;i<n;i++){
        array[i]=result[i];
    }
    
    
    printf("\n");
    for(int i=0;i<n;i++){
        printf("\t%d",array[i]);
    }
    printf("\n");

    return 0;
}
