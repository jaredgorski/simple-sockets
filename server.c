#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT "8080"
#define BACKLOG 10

int main
(int argc, char *argv[])
{
	char buf[1024] = {0}; /* the buffer for incoming messages */

	struct sockaddr_storage their_addr;
	socklen_t addrlen;
	struct addrinfo hints, *res;
	int status, sockfd, new_fd, bytes_received;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		/* IPv4 or IPv6, whatever */
	hints.ai_socktype = SOCK_STREAM;	/* TCP */
	hints.ai_flags |= AI_PASSIVE;		/* fill in my IP for me */

	/* get addrinfo linked list in res */
	if ((status = getaddrinfo(NULL, PORT, &hints, &res)) < 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}

	/* get socket */
	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		perror("!socket\n");
		exit(1);
	};

	/* bind to socket */
	if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("!bind\n");
		exit(1);
	};

	/* listen on socket file descriptor for connections */
	if (listen(sockfd, BACKLOG) < 0) {
		perror("!listen\n");
		exit(1);
	};

	printf("Server listening for connection on localhost at port: %s\n", PORT);

	/* accept incoming connection */
	addrlen = sizeof(their_addr);
	if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addrlen)) < 0) {
		perror("!accept\n");
		exit(1);
	}

	/* ready to communicate on socket descriptor new_fd! */

	printf("Connection established.\n");
	while(1) {
		bytes_received = recv(new_fd, buf, sizeof(buf), 0);

		if (bytes_received == 0) {
			break;
		} else {
			printf("> client: %s\n", buf);
		}

		memset(&buf, 0, sizeof(buf));
	}

	printf("! Client closed; shutting down server.\n");
	close(new_fd);
	close(sockfd);

	exit(0);
}
