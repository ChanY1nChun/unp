#include "all_package.h"

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);

int my_open(const char *pathname, int mode)
{
	int fd, sockfd[2], status;
	pid_t childpid;
	char c, argsockfd[10], argmode[10];

	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) < 0) {
		perror("socketpair");
		return -1;
	}

	if((childpid = fork()) == 0) {
		close(sockfd[0]);
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile", "openfile", argsockfd, pathname, argmode, (char*)NULL);
		perror("execl");
		return -1;
	}

	close(sockfd[1]);
	waitpid(childpid, &status, 0);
	if(WIFEXITED(status) == 0) {
		puts("child did not exit");
		return -1;
	}
	
	if((status = WEXITSTATUS(status)) == 0)  {
		if(read_fd(sockfd[0], &c, 1, &fd) < 0) {
			puts("read_fd error");
			return -1;
		}
	}
	
	else {
		errno = status;
		fd = -1;
	}



	close(sockfd[0]);
	return fd;

}
