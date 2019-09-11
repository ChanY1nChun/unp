#include "all_package.h"

extern void str_cli(FILE *fp, int sockfd);


int main(int argc, char **argv) {
	
	int sockfd;
	struct sockaddr_in servaddr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		return sockfd;
	}
	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect error");
		return -1;
	}

	str_cli(stdin, sockfd);

	

	exit(0);
} 
