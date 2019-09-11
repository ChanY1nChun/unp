#include "all_package.h"

extern ssize_t readline(int fd, void *vptr, size_t maxlen);
extern ssize_t writen(int fd, const void *vptr, size_t n);

void str_cli(FILE *fp, int sockfd)
{
	int maxfdpl;
	fd_set rset, tmp;
	char sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);
	FD_ZERO(&tmp);
	FD_SET(fileno(fp), &rset);
	FD_SET(sockfd, &rset);
	maxfdpl = max(fileno(fp), sockfd) + 1;
	while(1) {
		tmp = rset;
		if (select(maxfdpl, &tmp, NULL, NULL, NULL) < 0) {
			perror("select error");
			return -1;
		}
	
		if(FD_ISSET(sockfd, &tmp)) {
			if(readline(sockfd, recvline, MAXLINE) == 0) {
				perror("readline:");
				exit(0);
			}
			fputs(recvline, stdout);
		}
		if(FD_ISSET(fileno(fp), &tmp)) {
			if(fgets(sendline, MAXLINE, fp) == NULL) {
				return;
			writen(sockfd, sendline, strlen(sendline));
			}
		}
	}
}
