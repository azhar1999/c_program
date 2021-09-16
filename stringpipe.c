#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int count[3];
char str[100],nc[5],nw[5],nl[5],string2[100],string[100],temp[100],output[100];
int w=1,c=0,line=0;



int main(){
    int fd1[2];  
    int fd2[2];  
    char str1[100];
  
   
 
    int id;
  
    if (pipe(fd1)==-1){
         printf("an error has occured");
        return 1;
    }
    if (pipe(fd2)==-1){
         printf("an error has occured");
        return 1;
    }
  
    id = fork();
  
    if (id < 0){
        printf("fork failed");
        return 1;
    }
  
    
    else if (id == 0){
       printf("enter  string :");
       scanf("%[^$]", str1);
  
        close(fd1[0]); 
  
       
        write(fd1[1], &str1, 100);
        close(fd1[1]);
  
       
        wait(NULL);
  
        close(fd2[1]); 
  

        read(fd2[0], &output, 100);
        printf("%s\n", output);
        close(fd2[0]);
    }
  
    
    else{
        FILE* fp;
        FILE* fp1;
     
    
    	fp= fopen("file.txt", "w");
        close(fd1[1]);  
  
        
        read(fd1[0], &str, 100);
        for (int i=0;str[i]!='\0';i++)
		{ 
		if (str[i] =='\n')
			{
			line++;
			w++;
			}
			else
			{
			  if (str[i] == ' ' || str[i] == '\t')
				{
				  w++;
				  c++;
				}
				else
				{
				  c++;
				}
			 }
		 }
       
        
      
  	line++;
        close(fd1[0]);
        fprintf(fp, "Characters: %d\nWords: %d\nLines : %d\n", c, w, line);
        fclose(fp);
        
        close(fd2[0]);
	fp1 = fopen("file.txt", "r");
	while (fgets(temp, 100, fp1) != NULL)
		{ 
		strcat(string2, temp);
		}
        
        write(fd2[1], &string2, 100);
        close(fd2[1]);
  
        exit(0);
    }
    }
