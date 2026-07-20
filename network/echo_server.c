#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>

#define MAX_SIZE 1024

volatile sig_atomic_t stopped = 0;

void handle_sigint(int sig) {
	stopped = 1;
};


int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("usage: %s PORT\n", argv[0]);
		return 1;
	};

	const char * str_port = argv[1];
	int port = atoi(str_port);

	if (port < 1 || port > 65535) {
		printf("invalid port number (should be in range 1-65535)\n");
		return 1;
	};

	struct sigaction sa = {0};
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) < 0) {
		printf("can't register SIGINT handler\n");
		return 11;
	};

	int fd;

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK),
	};

	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		return 1;
	};

	if (bind(fd,(struct sockaddr *)&addr, sizeof(addr)) != 0) {
		close(fd);
		perror("bind");
		return 2;
	};

	if (listen(fd, 1) < 0) {
		close(fd);
		perror("listen");
		return 3;
	};
	printf("[*] Listening at 127.0.0.1:%d...\n", port); // well port is not hardcoded anymore
	while (!stopped) {
		int client_fd;
		struct sockaddr_in client_addr = {0};
		socklen_t client_len = sizeof(client_addr);
		client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
		if (client_fd < 0) {
			continue;
		};

		for (;;) {
			printf("[!] Accepted new connection\n");
			char buf[1025]; // leaving the space for \0
			ssize_t bytes_read;
			bytes_read = read(client_fd, buf, MAX_SIZE);
			if (bytes_read > 0) {
				printf("[<] read %d bytes from a client\n", (int)bytes_read);
				write(client_fd, buf, bytes_read);
				printf("[>] sent those bytes back\n");
			} else if (bytes_read == 0) {
				printf("[!] Client disconnected\n");
				break;
			} else {
				printf("[X] Error while reading from client\n");
				break;
			};
		};
		close(client_fd);
	};
	close(fd);
}
