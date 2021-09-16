#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int factorial(int a){
int fact=1;
while (a>0){
	fact=fact*a;
	a=a-1;}
	return fact;}
int main (int argc,char*argv[ ])
{
	int n=atoi(argv[1]);
	if(fork() ==0)	{
		for(int i =1; i <= n; i++){
		printf("%d  \n ",factorial(i));}
		printf("\n");}
	else{
	wait(NULL);}
	}

