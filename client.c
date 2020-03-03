#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define HOST "127.0.0.1"
#define PORT "8080"
#define MAX_MSG_SZ 1024

int main
(int argc, char *argv[])
{
	char *msg = malloc(MAX_MSG_SZ);
	if (msg == NULL) {
		printf("No memory.\n");
		exit(1);
	}

	int status, sockfd, bytes_sent;
	struct addrinfo hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		/* IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;	/* TCP */
	hints.ai_flags |= AI_PASSIVE;		/* set IP for me */

	/* get addrinfo linked list in res */
	if ((status = getaddrinfo(HOST, PORT, &hints, &res)) < 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(1);
	}

	/* get socket */
	if ((sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) < 0) {
		perror("!socket\n");
		exit(1);
	}

	/* connect */
	if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
		perror("!connect\n");
		exit(1);
	}

	printf("Opening client. Enter '.exit' to close.\n");
	while(1) {
		printf("> ");
		fgets(msg, MAX_MSG_SZ, stdin);

		/* remove trailing newline, if there */
		if ((strlen(msg) > 0) && (msg[strlen(msg) - 1] == '\n')) {
			msg[strlen(msg) - 1] = '\0';
		}

		bytes_sent = send(sockfd, msg, strlen(msg), 0);

		if (strcmp(msg, ".exit") == 0) {
			break;
		}

		*msg = '\0';
	}

	printf("! Closing client.\n");
	close(sockfd);

	free(msg);

	exit(0);
}
