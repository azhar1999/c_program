#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main(){    
	if(fork()==0){ 
      			sleep(2);
       			printf("this is first child\n");   }   
       else{
             if(fork()==0){ 
                       sleep(1);           
                       printf("this is second child\n");      
                        } 
             else{           
                   if(fork()==0){   
                                 printf("this is third child\n"); 
                                 }
                    else{
                          sleep(3);
                          printf("this is parent process");
                           exit(0);}       
                   }   
               } 
            }
