#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 255

int main(int argc, char ** argv) {
	if (argc < 3) {
		printf("usage: %s IP PORT\n", argv[0]);
		return 1;
	};
	const char * host_arg = argv[1];
	const char * str_port = argv[2];
	int port = atoi(str_port);

	int fd;
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
	};

	inet_pton(AF_INET, host_arg, &(addr.sin_addr));

	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("failed to create a socket");
		return 1;
	};

	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("failed to connect to socket");
		return 1;
	};
	printf("Connected! Type exit or ^D to disconnect\n");
	
	char buf[256];
	static const char EXIT_COMMAND[] = "exit\n";
	
	for (;;) {
		ssize_t bytes_stdin, bytes_sent, bytes_received;
		printf("> ");
		fflush(stdout);
		bytes_stdin = read(STDIN_FILENO, buf, MAX_SIZE);
		if (bytes_stdin == 0) {
			printf(EXIT_COMMAND);
			break;
		};
		if (bytes_stdin < 0) {
			perror("failed to read user input");
			break;
		};
		buf[bytes_stdin] = '\0';
		if (strncmp(buf, EXIT_COMMAND, sizeof(EXIT_COMMAND)) == 0) {
			printf(EXIT_COMMAND);
			break;
		};
		bytes_sent = write(fd, buf, bytes_stdin);
		if (bytes_sent < 0) {
			perror("failed to send bytes");
			break;
		}
		bytes_received = read(fd, buf, MAX_SIZE);
		if (bytes_received == 0) {
			printf("Connection closed.\n");
			break;
		};
		if (bytes_received < 0) {
			perror("failed to read from socket");
			break;
		};
		write(STDOUT_FILENO, buf, bytes_received);
	}
	close(fd);
	return 0;
};
