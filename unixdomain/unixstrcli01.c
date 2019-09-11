#include "all_package.h"

extern void str_cli(FILE *fp, int sockfd);

int main(int argc, char **argv) 
{
	int sockfd;
	struct sockaddr_un servaddr;
	char path[100] = "/home/book/my2gcc/unp/net/unixdomain/unix.str";
	
	if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, path);
	
	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect");
		return -1;
	}

	str_cli(stdin, sockfd);

	return 0;
	
}
