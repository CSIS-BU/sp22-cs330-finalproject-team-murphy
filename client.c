#include <stdio.h>	
#include <string.h>	
#include <sys/socket.h>	
#include <arpa/inet.h>	
#include <unistd.h>

//#define BUFFER_SIZE 2000
//#define PORT 80

int main(int argc, char* argv[])
{
	int socket;
	struct sockaddr_in serv;
	char message[1000], server_reply[2000];

	struct hostent* hostholder;
	char* host;

	host = "localhost";

	hostholder = gethostbyname(host);
	if (!hostholder)
	{
		printf(stderr, "Host not known", host);
		exit(1);
	}

	serv.sin_addr.s_addr = inet_addr(""); //address will go here
	serv.sin_family = AF_INET;
	bzero((char*)&serv, sizeof(serv));
	bopy(hostholder->h_addr, (char*)&serv.sin_addr, hostholder->h_length);
	serv.sin_port = htons(8888);

	//Creating the socket
	socket = socket(AF_INET, SOCK_STREAM, 0);
	if (socket == -1)
	{
		printf("Socket could not be created");
	}
	puts("Socket has been made");

	

	//connecting to the remote server
	if (connect(socket, (struct sockaddr*)&serv, sizeof(serv)) < 0)
	{
		perror("Connection has failed.");
		exit(1);
	}

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