#include "all_package.h"

static void sig_chld(int signo);
extern void str_echo(int sockfd);

int main(int argc, char **argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	char path[100] = "/home/book/my2gcc/unp/net/unixdomain/unix.str";
	struct sockaddr_un cliaddr, servaddr;
	
	unlink(path);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, path);
	
	if((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return listenfd;
	}

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind");
		return -1;
	}
	
	listen(listenfd, 5);

	signal(SIGCHLD, sig_chld);

	while(1) {
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen)) < 0) {
			if(errno == EINTR) 
				continue;
			else {
				perror("accept");
				return -1;
			}
		}
	
		if((childpid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		
	 	close(connfd);
	}

}

void sig_chld(int signo)
{
	int status;
	while(waitpid(-1, &status, WNOHANG) > 0)
		;
	return; 
}
