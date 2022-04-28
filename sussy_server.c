#include <err.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <uninstd.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

int server(char* server_port)
{
	int sock_fd, new_sockfd;
	struct addrinfo hints, * serv_info;
	struct sockaddr_in client_addr;
	socklen_t length;
	int error;
	int yes = 1;
	unsigned char buffer[RECV_BUGGER_SIZE];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints_ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //use my ip-his note

	error = getaddrinfo(NULL, server_port, &hints, &serv_info);
	if (error)
	{
		errx(1, "%s", gai_strerror(error));
	}

	if ((sock_fd = socket(serv_info->ai_family, serv_info->ai_socktype,
		serv_info->ai_protocl)) < 0)
	{
		perror("server: socket error");
		exit(-1);
	}

	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("setsockopt");
		exit(-1);
	}

	if (bind(sock_fd, serv_info->ai_addr, serv_info->ai_addrlen) < 0)
	{
		close(sock_fd);
		perror("server: bind error\n");
		exit(-1);
	}
	freeaddrinfo(serv_info);

	if (serv_info == NULL) {
		fprintf(stderr, "server: failed to bind/n");
		exit(-1);
	}

	if (listen(sock_fd, QUEUE_LENGTH) < 0)
	{
		perror("server: listen error");
		exit(-1);
	}

	while (1)
	{
		length = sizeof client_addr;
		if ((new_sockfd = accept(sock_fd, (struct sockaddr*)
			&client_addr, &length)) < 0)
		{
			perror("server: accept error");
			exit(-1);
		}

		while ((error = recv(new_sockfd, buffer, RECV_BUFFER_SIZE, 0)) > 0)
		{
			fwrite(buffer, 1, error, stdout);
			fflush(stdout);

		}
		close(new_sockfd);
	}
	return 0;
}

int main(int argc, char** argv)
{
	char* server_port;

	if (argc != 2)
	{
		fprint(stderr, "Usage: ./server-c [server port]\n");
		exit(EXIT_FAILURE);
	}
	server_port = argv[1];
	return server(server_port);
}