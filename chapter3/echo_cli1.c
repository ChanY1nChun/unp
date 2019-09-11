#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXLINE 4096

int main(int argc, char **argv) {

	struct sockaddr_in servaddr;
	int sockfd, nread;
	char buf[MAXLINE] = {0};
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		perror("socket:");
		return sockfd;
	} 

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5000);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);
		
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect:");
		return -1;
	}

	while(1) {
		if ((nread = read(STDIN_FILENO, buf, sizeof(buf))) < 0) {
			perror("read:");
			return -1;
		}
	
		if(buf[0] == 'q') {
			close(sockfd);
			return 0;
		}
		
		if (write(sockfd, buf, nread) < 0) {
			perror("write:");
			return -1;
		}
		nread = read(sockfd, buf, sizeof(buf));
		if (write(STDOUT_FILENO, buf, nread) < 0) {
			perror("write:");
			return -1;
		}

		
		
	}
	

	return 0;
}
