#include "all_package.h"

extern ssize_t readline(int fd, void *vptr, size_t maxlen);
extern ssize_t writen(int fd, const void *vptr, size_t n);

void str_cli(FILE *fp, int sockfd)
{
	char sendline[MAXLINE], recvline[MAXLINE];

	while(fgets(sendline, MAXLINE, fp) != NULL) {
		writen(sockfd, sendline, strlen(sendline));

		if(readline(sockfd, recvline, MAXLINE) == 0) {
			perror("readline:");
			exit(0);
		}
	
		fputs(recvline, stdout);
	}
}
