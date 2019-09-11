#include "all_package.h"

void dg_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
	int n;
	struct sockaddr_in preply_addr;
	char sendline[MAXLINE], recvline[MAXLINE+1];

	socklen_t preply_len = sizeof(preply_addr);
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		if(sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen) < 0) {
			perror("sendto");
			return;
		}

		if((n = recvfrom(sockfd, recvline, MAXLINE, 0, (struct sockaddr*)&preply_addr, &preply_len)) < 0) {
			perror("recvfrom");
			return;
		} 

		if(preply_len != servlen || memcmp(pservaddr, &preply_addr, preply_len) != 0) {
			printf("reply is not right\n");
			continue;
		}

		recvline[n] = 0;
		fputs(recvline, stdout);
	}

}
