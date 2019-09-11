#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
int main() {

	struct sockaddr_in servaddr;
	char buf[64] = {0};

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("192.168.221.138");

	puts("create socket.");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	puts("connect.");
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	socklen_t len;
	struct sockaddr_in cliaddr;
	len = sizeof(cliaddr);
	
	getsockname(sockfd, (struct sockaddr*)&cliaddr, &len);
	printf("cliaddr:%s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	int n = read(sockfd, buf, 64);
	write(STDOUT_FILENO, buf, n);

	close(sockfd);

	return 0;
}
