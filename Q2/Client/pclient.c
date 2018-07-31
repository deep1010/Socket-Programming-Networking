// client side of the network

#include <semaphore.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define PORT 8080
int main(void)
{
	int sockfd = 0;    // socket file descriptor
	int bytesReceived = 0;
	char buffer[1029];
	memset(buffer, '0', sizeof(buffer));
	struct sockaddr_in serv_addr;

	/* Create a socket first */
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
	{
		printf("Error : Could not create socket \n");
		return 1;
	}
	else
	{
		printf("Socket created\n");
	}

	/* Initialize sockaddr_in data structure */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT); // port
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	/* Attempt a connection */
	printf("Connection initiating...\n");
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("Error : Couldn't connect to server \n");
		return 1;
	}
	else
	{
		printf("Connection completed to server:127.0.0.1 on port:%d\n", PORT);
	}
	while(1==1)
	{
		printf("Enter the file name to be transferred: ");
		char fname[1025]={0};
		scanf("%s",fname);
		
//		read(sockfd, buffer, sizeof(buffer));
//		if(!(buffer[0]=='O' && buffer[1]=='N'))
//		{
//			printf("Error: Connection broke\n");
//			return 0;
//		} 
		
		if(strcmp(fname,"q")==0)
		{	send(sockfd, fname, strlen(fname), 0);
			return -1;}

		send(sockfd, fname, strlen(fname), 0);
		int valread;
		valread = read(sockfd, buffer, 10);
		if(buffer[0]=='E' && buffer[1]=='R' && buffer[2]=='R' && buffer[3]=='O' && buffer[4]=='R')
		{
			printf("File doesn't exist\n");
			continue;
		}

		/* Create file where data will be stored */
		FILE *fp;
		fp = fopen(fname, "w"); 
		if(NULL == fp)
		{
			printf("Error : Couldn't open file\n");
			return 1;
		}

		int init=0;
		/* Receive data in chunks of 10 bytes */
		while(1==1)
		{

			//			printf("buffer: %s\n",buffer);
			if(strcmp(buffer, "FOUND")==0)
			{
				printf("Transfer initiated\n");
			}
			else if(buffer[0]=='E' && buffer[1]=='R' && buffer[2]=='R' && buffer[3]=='O' && buffer[4]=='R')
			{
				printf("File doesn't exist\n");
				break;
			}
			else if(strcmp(buffer, "CLOSE")==0)
			{
				fclose(fp);
				if(init==1)
					printf("File tranfer completed\n");
				
				else
				{printf("Error: Connection broke\n");return 0;}

				break;
			}
			fprintf(fp, "%s", buffer);
			init=1;
			valread = read(sockfd, buffer, 10);
		}
	}
	return 0;
}
