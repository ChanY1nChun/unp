#include "all_package.h"

extern void dg_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen);

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];

	if(argc != 2) {
		fputs("must type IP.", stdout);
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error");
		return sockfd;
	}

	dg_cli(stdin, sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	return 0;
}
