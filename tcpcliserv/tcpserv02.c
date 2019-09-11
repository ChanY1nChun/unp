#include "all_package.h"

extern void str_echo(int fd);
void sig_chld(int signo);

int main(int argc, char **argv) {

	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
		return listenfd;	
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		return -1;
	}

	if(listen(listenfd, 5) < 0) {
		perror("listen error");
		return -1;
	}

	signal(SIGCHLD, sig_chld);

	while(1) {
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
			if(errno == EINTR)
				continue;
			else
				perror("accept:");
		}


		if((childpid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
	
		close(connfd);
	}

	return 0;
}


void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		;
	return;
}
