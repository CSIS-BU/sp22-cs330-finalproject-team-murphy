#include <stdio.h>	
#include <string.h>	
#include <sys/socket.h>	
#include <arpa/inet.h>	
#include <unistd.h>
#define QUEUE_LENGTH 10

int main(int argc, char* argv[])
{
	int socket;
	struct sockaddr_in serv;
	char message[1000], server_reply[2000];

	//Creating the socket
	socket = socket(AF_INET, SOCK_STREAM, 0);
	if (socket == -1)
	{
		printf("Socket could not be created");
	}
	puts("Socket has been made");

	serv.sin_addr.s_addr = inet_addr(""); //address will go here
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);

	/*//connecting to the remote server
	if (connect(socket, (struct sockaddr*)&serv, sizeof(serv)) < 0)
	{
		perror("Connection has failed.");
		return 1;
	}*/

	if ((bind(socket, (struct sockaddr*)&serv, sizeof(serv))) < 0) {
		perror("Connection has failed");
		exit(1);
	}

	listen(socket, QUEUE_LENGTH);

	puts("Connection made\n");

	//constantly communicating with server
	while (1)
	{
		printf("Enter message : ");
		scanf("%s", message);

		//data sending
		if (send(socket, message, strlen(message), 0) < 0)
		{
			puts("message failed to send");
			return 1;
		}

		//receiving reply from the serve
		if (recv(socket, server_reply, 2000, 0) < 0)
		{
			puts("recovery of message failed");
			break;
		}

		puts("Server reply: ");
		puts(server_reply);
	}

	close(socket);
	return 0;
}