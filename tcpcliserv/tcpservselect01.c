#include "all_package.h"

//extern ssize_t writen(int fd,const void *vptr, size_t n);

int main(int argc, char **argv)
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready, client[FD_SETSIZE];
	ssize_t n;
	fd_set rset, allset;
	char buf[MAXLINE];
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return listenfd;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(8000);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind");
		return -1;
	}

	if(listen(listenfd, 5) < 0) {
		perror("listen");
		return -1;
	}

	maxfd = listenfd;
	maxi = -1;
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	while(1) {
		rset = allset;
		if((nready = select(maxfd+1, &rset, NULL, NULL, NULL)) < 0) {
			perror("select error");
			return -1;
		}
		
		if(FD_ISSET(listenfd, &rset)) {
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

			for (i = 0; i < FD_SETSIZE; i++)
				if(client[i] < 0) {
					client[i] = connfd;
					break;
				}

			if(i == FD_SETSIZE)
				 return -1;

			FD_SET(connfd,&allset);
			if (connfd > maxfd)	maxfd = connfd;
			if (i > maxi) maxi = i;

			if(--nready <= 0) continue;
		}

		for(i = 0; i <= maxi; i++) {
			if((sockfd = client[i]) < 0)
				continue;
			if(FD_ISSET(sockfd, &rset)) {
				if((n = read(sockfd, buf, MAXLINE)) == 0) {
					close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
				} else
					write(sockfd, buf, n);

				if(--nready <= 0)
					break;
			}
		}



		
	}
	
}
