#include "all_package.h"

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char buf[MAXLINE];
	
	while(1) {
		len = clilen;
		if((n = recvfrom(sockfd, buf, MAXLINE, 0, pcliaddr, &len)) < 0) {
			perror("recvfrom");
			return;
		}
	
		if(sendto(sockfd, buf, n, 0, pcliaddr, len) < 0) {
			perror("sendto");
			return;
		}
	}
	
}
