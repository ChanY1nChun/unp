#include "all_package.h"


void *copyto(void *);

static int sockfd;
static FILE *fp;

void str_cli(FILE *fp_arg, int sockfd_arg)
{
	char recvline[MAXLINE];
	pthread_t tid;
	int n;
	
	sockfd = sockfd_arg;
	fp = fp_arg;

	pthread_create(&tid, NULL, copyto, NULL);

	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		write(STDIN_FILENO, recvline, n);
	}
}

void *copyto(void *arg)
{
	int n;
	char sendline[MAXLINE];
	
	while((n = read(STDIN_FILENO, sendline, MAXLINE)) > 0) {
		write(sockfd, sendline, n);
	}

	shutdown(sockfd, SHUT_WR);

	return NULL;
}
