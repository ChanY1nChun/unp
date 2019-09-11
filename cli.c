#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main() {

	struct sockaddr_in servaddr;
	
	struct sockaddr_in clivaddr;
	socklen_t clilen;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8080); 
	servaddr.sin_addr.s_addr = inet_addr("192.168.221.138"); 
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	clilen = sizeof(clivaddr);
	getsockname(sockfd, (struct sockaddr*)&clivaddr, &clilen);

	printf("clivaddr:%s:%d\n", inet_ntoa(clivaddr.sin_addr), ntohs(clivaddr.sin_port));

	return 0;
}
