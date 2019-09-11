#include "all_package.h"

static void *doit(void *);
extern void str_echo(int);
int main(int argc, char **argv)
{
	int listenfd, connfd;
	pthread_t tid;
	socklen_t addrlen, len;
	struct sockaddr_in cliaddr, servaddr;
	
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("listenfd error");	
		return listenfd;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		return -1;
	}

	listen(listenfd, 5);

	while(1) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &len);
		pthread_create(&tid, NULL, doit, (void *)connfd);
	}
}

static void *doit(void *arg)
{
	pthread_detach(pthread_self());
	str_echo((int)arg);
	close((int)arg);
	return NULL;
}
