#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

/* ********************
 * man 5 protocols
 * man 2 socket
 * ****************** */

volatile sig_atomic_t stopped = 0;

void handle_sigint(int sig) {
	stopped = 1;
};


int main(int argc, char ** argv) {
	struct sigaction sa = {0};
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);

	if (sigaction(SIGINT, &sa, NULL) < 0) {
		printf("can't register SIGINT handler\n");
		return 11;
	};

	int errno;
	int fd;

	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(8080),
		.sin_addr.s_addr = htonl(INADDR_LOOPBACK),
	};

	fd = socket(PF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		printf("%d\n", errno);
		return 1;
	};

	if (bind(fd,(struct sockaddr *)&addr, sizeof(addr)) != 0) {
		close(fd);
		printf("%d\n", errno);
		return 2;
	};

	if (listen(fd, 1) < 0) {
		close(fd);
		printf("%d\n", errno);
		return 3;
	};
	printf("[*] Listening at 127.0.0.1:8080...\n"); // yeah, this is hardcoded for now
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
			int MAX_SIZE = 1024;
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
