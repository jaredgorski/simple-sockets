#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main
(int argc, char *argv[])
{
	int sockfd = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\nError creating socket\n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address - Address not supported\n");
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection failed.\n");
		return -1;
	};

	send(sockfd, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(sockfd, buffer, 1024);
	printf("%s\n", buffer);
	return 0;
}
