#include "all_package.h"

extern void str_cli(FILE *fp, int sockfd);
extern int connect_timeo(int sockfd, const struct sockaddr *saptr, socklen_t len, int nsec);

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

	if(connect_timeo(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr), 1) < 0) {
		perror("connect error");
		return -1;
	}

	str_cli(stdin, sockfd);

	

	exit(0);
} 
