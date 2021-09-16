#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

char str1[100], str2[100],string[200],concat[200],result[200];
int k=0;
int main()

{

    int fd1[2];
    int fd2[2];
   
    int id, k, i;

    printf("enter first string :");
    fgets(str1, 100, stdin);
    

    if (pipe(fd1) == -1)
    {
        printf("an error has occured");
        return 1;
    }
    if (pipe(fd2) == -1)
    {
        printf("an error has occured");
        return 1;
    }

    id = fork();
    if (id < 0)
    {
        printf("fork failed");
        return 1;
    }

    else if (id == 0)
    {
 
        close(fd1[0]);
        write(fd1[1], &str1, 100);
        close(fd1[1]);

        wait(NULL);

        close(fd2[1]);

        read(fd2[0], &result, 200);
        printf("concatenated string is %s\n", result);
        close(fd2[0]);
    }

    else
    {
    

        close(fd1[1]);
        printf("enter second string :");
        fgets(str2, 100, stdin);
        read(fd1[0], &string, 100);
	k=0;
        for (int i = 0;string[i]!='\n';i++)
		concat[k++]=string[i];
	for (int i = 0;str2[i]!='\n';i++)
		concat[k++]=str2[i];
       
     
        
        close(fd1[0]);

        close(fd2[0]);
        write(fd2[1], &concat, 200);
        close(fd2[1]);
        exit(0);
    }
}

