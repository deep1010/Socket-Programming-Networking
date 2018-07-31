// Server side of the network

#include <semaphore.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#define PORT 8080

int main(void)
{
	int listenfd = 0;
	int connfd = 0;
	int opt = 1;
	struct sockaddr_in serv_addr;
	char buffer[1024];
	int numrv;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		printf("Socket failed\n");
		return -1;
	}
	else
		printf(">> Socket created\n");

	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(buffer, '0', sizeof(buffer));

	// Forcefully attaching socket to the port 8080
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		printf("Error : Port attaching failed\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);

	if(bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
	{
		printf("Error : Binding failed\n");	
	}
	else
	{
		printf(">> Socket binded with host:127.0.0.1 and port:%d\n", PORT);
	}

	while(1)
	{
		if(listen(listenfd, 5) == -1)
		{
			printf("Error : Failed to listen\n");
			return -1;
		}

		if((connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL))<0)
		{
			printf("Error : Failed to connect\n");
			return -1;
		}
		else
		{
			char clip[100]={};
			inet_ntop(AF_INET, &(serv_addr.sin_addr), clip, INET_ADDRSTRLEN);
			printf(">> Waiting for request... from %s\n",clip);;
		}

		while(1)
		{
			char fname[1025] = {0};
	//		write(connfd, "ON", 2);	

			int valread = read(connfd, fname, 1024);
			if(strcmp(fname,"q")==0)
			{
				printf(">> Ending...\n");
				break;
			}

			printf(">> Filename: %s\n",fname);

			/* Open the file that we wish to transfer */

			char source[50000]={0};
			strcpy(source, "./Data/");
			strcat(source, fname);
			FILE *fp = fopen(source,"r");
			if(fp==NULL)
			{
				write(connfd, "ERROR", 5);	
				goto jump;   
			}

			/* Read data from file and send it */
			/* First read file in chunks of 10 bytes */
			unsigned char buff[10]={0};
			while(fscanf(fp, "%c", buff)!=EOF)
			{
				write(connfd, buff, sizeof(buff));
			}
			write(connfd, "CLOSE", 5);
			printf(">> File sending completed\n");

			fclose(fp);
jump:
			(1==1);
		}
		printf(">> Disconnecting...\n");
		close(connfd);
	}
	return 0;
}


