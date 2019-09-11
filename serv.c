#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

	struct sockaddr_in servaddr;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("192.168.221.138");

	puts("1.create socket.");
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	puts("2.bind.");
	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	puts("3.listen.");
	listen(sockfd, 5);


	while(1) pause();
	return 0;
}
