#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main
(int argc, char *argv[])
{
	int sockfd, new_sock, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == 0) {
		perror("Error initializing socket");
		exit(1);
	}

	/* if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { */
	/* 	perror("Error attaching to port"); */
	/* 	exit(1); */
	/* } */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Error binding  to port");
		exit(1);
	}

	if (listen(sockfd, 3) < 0) {
		perror("Error listening to socket");
		exit(1);
	}

	if ((new_sock = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
		perror("Error accepting connection");
		exit(1);
	}

	printf("new_sock: %d", new_sock);

	valread = recv(new_sock, buffer, 1024, opt);
	printf("%s\n", buffer);
	send(new_sock, hello, strlen(hello), 0);
	printf("Hello message sent");
	return 0;
}
