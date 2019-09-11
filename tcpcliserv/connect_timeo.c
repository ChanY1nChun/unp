#include "all_package.h"

static void connect_alarm(int signo);

int connect_timeo(int sockfd, const struct sockaddr *saptr, socklen_t len, int nsec)
{
	void *sigfunc;
	int n;
	sigfunc = signal(SIGALRM, connect_alarm);

	if(alarm(nsec) != 0) {
		puts("alarm has been set");
		return -1;
	}

	if((n = connect(sockfd, saptr, len)) < 0) {
		close(sockfd);
		if(errno == EINTR)
			errno = ETIMEDOUT;
	}
	
	alarm(0);
	signal(SIGALRM, sigfunc);

	return n;
}

void connect_alarm(int signo)
{
	return;
}
