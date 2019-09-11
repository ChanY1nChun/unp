#include "all_package.h"

extern void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);

int main(int argc, char **argv) 
{
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		return sockfd;
	}

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind");
		return -1;
	}

	dg_echo(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	
}
