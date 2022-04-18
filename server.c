#include<stdio.h>
#include<string.h>	
#include<sys/socket.h>
#include<arpa/inet.h>	
#include<unistd.h>

int main(int argc, char *argv[])
{
	int sock;
	int clientSock;
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
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );//idk what port we will use this is for testing
	
	if(bind(sock,(struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("bind failed");
		return 1;
	}
	puts("binding succeeded");
	
	listen(sock, 3);//3 may need to be changed so more games can run simultaneously 
	
	//get connection
	puts("looking for client");
	c = sizeof(struct sockaddr_in);
	
	//accept connection
	clientSock = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c);
	if (clientSock < 0)
	{
		perror("client not accepted");
		return 1;
	}
	puts("client accepted");
	
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