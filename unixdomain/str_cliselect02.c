#include "all_package.h"

extern ssize_t readline(int fd, void *vptr, size_t maxlen);
extern ssize_t writen(int fd, const void *vptr, size_t n);
static int max(int a, int b);

void str_cli(FILE *fp, int sockfd)
{
	int maxfdpl, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;
	
	FD_ZERO(&rset);
	stdineof = 0;
	while(1) {
		if(stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdpl = max(fileno(fp), sockfd) + 1;

		if (select(maxfdpl, &rset, NULL, NULL, NULL) < 0) {
			perror("select error");
			return;
		}
	
		if(FD_ISSET(sockfd, &rset)) {
			if ((n = read(sockfd, buf, MAXLINE)) == 0) {
				if(stdineof == 1)
					return;
				else {
					perror("read");
					exit(0);
				}
			}
			write(STDIN_FILENO, buf, n);			
		}
		
		if(FD_ISSET(fileno(fp), &rset)) {
			if ((n = read(fileno(fp), buf, MAXLINE)) == 0) {
				
					stdineof = 1;
					shutdown(sockfd, SHUT_WR);
					FD_CLR(fileno(fp), &rset);
					continue;
				}
				
				write(sockfd, buf, n);
			
		}
	}
}

int max(int a, int b)
{
	return a > b ? a : b;
}
