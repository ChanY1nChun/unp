#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>

#define MAXLINE 4096

int main() {
	
	struct sockaddr_in cliaddr, servaddr;
	socklen_t len, nread;
	int listenfd, connfd;
	char buf[MAXLINE] = {0};
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	listen(listenfd, 5);

	while(1) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
		printf("ip:%s, port:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		
		nread = read(connfd, buf, MAXLINE);
		write(connfd, buf, nread);

		
	}

	return 0;
}

