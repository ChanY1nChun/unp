#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
int main() {

	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("192.168.221.138");

	puts("create socket.");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	puts("bind.");
	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	puts("listen.");
	listen(sockfd, 5);


	puts("accept.");
	socklen_t len = sizeof(cliaddr);
	int clifd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
	printf("cliaddr:%s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	len = sizeof(cliaddr);
	getsockname(clifd, (struct sockaddr*)&cliaddr, &len);
	printf("sockaddr:%s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	write(clifd, "Hello world.\n", 15);

	close(clifd);
	close(sockfd);

	return 0;
}
