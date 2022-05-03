#include<stdio.h>
#include<string.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<time.h>

#define PORT 80
#define QUEUE 5

int main(int argc, char *argv[])
{
	int sock;
	int clientSock;
	int newClient;
	int c;
	int readSize;
	struct sockaddr_in server;
	struct client;
	char contents[2000];

	//make socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("socket failed");
	}
	puts("created socket");
	
	//get socket address
	bzero((char*)&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );
	
	if(bind(sock,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind failed");
		return 1;
	}
	puts("binding succeeded");
	
	listen(sock, QUEUE);//Multiple Running Games
	
	//get connection
	puts("looking for client");
	c = sizeof(struct sockaddr_in);
	
	//Create Constant Server
	while (1)
	{
		//accept connection
		newClient = accept(sock, (struct sockaddr*)&client, (socklen_t*)&c);
		if (newClient < 0)
		{
			perror("client not accepted");
			close(newClient);
		}
		puts("client accepted");

		// Accepts Multiple Clients
		pid = fork();
		if (pid > 0)
		{
			close(newClient);
		}
		else if (pid == 0)
		{
			close(clientSock);


			// Tic-Tac-Toe Functionality
		}
	}


	
	//get and reply to message
	while((readSize = recv(clientSock, contents, 2000, 0)) > 0 )
	{
		//strcpy(contents, "server speaking");
		//send(clientSock, contents, 3, 0);
		write(clientSock, contents, strlen(contents));
	}
	
	if(readSize == 0)
	{
		puts("client disconnected");
		fflush(stdout);
	}
	else if(readSize == -1)
	{
		perror("no data/connection failed");
	}
	
	return 0;
}