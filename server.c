#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>



int main(int argc,char *argv[])
{
	int sockfd,newsockfd,portno,clilen;
	char buffer[256];
	struct sockaddr_in serv_addr,cli_addr;
	int n;
	
	if (argc < 2)
	{
		printf("error,no port provided \n");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	
	if (sockfd < 0 )
	{
		printf("ERROR opening socket ");
		exit(1);
	}
	
	bzero((char *) &serv_addr,sizeof(serv_addr));
	
	portno = atoi(argv[1]);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) <0)
	{
		printf("ERROR on binding ");
		exit(1);
	}
	
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	newsockfd = accept (sockfd,(struct sockaddr *) &cli_addr, &clilen);
	
	if( newsockfd < 0 )
	{
		printf("ERROR on accept");
		exit(1);
	}
	
	bzero(buffer,256);
	
	n = read(newsockfd,buffer,255);
	
	if (n<0)
	{
		printf("ERROR reading from socket");
		exit(1);
		
	}
	
	printf("here is message : %s \n",buffer);
	
	n= write(newsockfd," server recieved your message ",30);
	
	if (n < 0) 
	{
		printf("ERROR writing to socket");
		exit(1);
		}
	return 0;
	
	}
	
	
	
	 
	 
	
	
	
	
	
	
	
			
	
		

	
	
