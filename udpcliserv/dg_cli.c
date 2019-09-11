#include "all_package.h"

void dg_cli(FILE *fp, int sockfd, struct sockaddr *pservaddr, socklen_t servlen)
{
	int n;
	char sendline[MAXLINE], recvline[MAXLINE+1];
	
	while(fgets(sendline, MAXLINE, fp) != NULL) {
		if(sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen) < 0) {
			perror("sendto");
			return;
		}

		if((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
			perror("recvfrom");
			return;
		}

		recvline[n] = 0;
		fputs(recvline, stdout);
	}

}
