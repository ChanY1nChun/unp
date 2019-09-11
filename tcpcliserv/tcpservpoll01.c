#include "all_package.h"
#include <limits.h>

int main(int argc, char **argv)
{
	int i, maxi, listenfd, connfd, sockfd;
	int nready;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	struct pollfd client[OPEN_MAX];
	struct sockaddr_in servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		return listenfd;
	}

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		return -1;
	}
	
	if(listen(listenfd, 5) < 0) {
		perror("listen error");
		return -1;
	}

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;
	for(i = 1; i < OPEN_MAX; i++)
		client[i].fd = -1;
	maxi = 0;

	while(1) {
		if((nready = poll(client, OPEN_MAX, INFTIM)) < 0) {
			if(errno == EINTR) 
				continue;
			else {
				perror("poll error");
				return -1;
			}
		}
	
		if(client[0].revents & POLLRDNORM) {   //new client connection
		again:
			clilen = sizeof(cliaddr);
			if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
				if(errno == EINTR)
					goto again;
				else {
					perror("accept error");
					return -1;
				}
			}

			for(i = 1; i < OPEN_MAX; i++) {
				if(client[i].fd < 0) {
					client[i].fd = connfd;
					break;
				}
			}

			if(i == OPEN_MAX) return -1;

			client[i].events = POLLRDNORM;
			if(i > maxi) maxi = i;

			if(--nready <= 0) continue;

		}

			for(i = 1; i < OPEN_MAX; i++) {	  //check all clients for data
				if(client[i].fd < 0)
					continue;
				if(client[i].revents & (POLLRDNORM | POLLERR)) {
					sockfd = client[i].fd;
					if((n = read(sockfd, buf, MAXLINE)) < 0) {
						if(errno == ECONNRESET) {   //connetction reset by client
							close(sockfd);
							client[i].fd = -1;
						} else {
							perror("read error");
							return -1;
						  } 
					} else if (n == 0) { //EOF
						close(sockfd);
						client[i].fd = -1;
					} else
						write(sockfd, buf, n);

					if(--nready <= 0)
						break;
				}

			}
	}

}
