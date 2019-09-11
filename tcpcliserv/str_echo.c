#include "all_package.h"

extern ssize_t writen(int fd, const void *vptr, size_t n);

void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(sockfd, buf, MAXLINE)) > 0)
		writen(sockfd, buf, n);

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n < 0)
		perror("str_echo read error");
}
