#include "all_package.h"


int main(int argc, char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if(argc != 2) {
		puts("unixbind <pathname>");
		return -1;
	}

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_UNIX;
	unlink(argv[1]);
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	
	
	if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return sockfd;
	}

	if(bind(sockfd, (struct sockaddr*)&addr1, SUN_LEN(&addr1)) < 0) {
		perror("bind");
		return -1;
	}

	len = sizeof(addr2);
	getsockname(sockfd, (struct sockaddr*)&addr2, &len);
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);

	return 0;

}
