#include "all_package.h"

int my_open(const char *pathname, int);

int main(int argc, char **argv)
{
	int fd, n;
	char buf[BUFFSIZE];
	
	if(argc != 2) {
		puts("usage: mycat <pathname>");
		return -1;
	}

	if((fd = my_open(argv[1], O_RDONLY)) < 0) {
		perror("my_open");
		return -1;
	}

	while((n = read(fd, buf, BUFFSIZE)) > 0)
		write(STDOUT_FILENO, buf, n);

	exit(0);
}
