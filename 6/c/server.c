#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>

int main(){
	int sockfd, len;
	struct sockaddr_in serv, cli;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(16001);
	bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	len = sizeof(cli);
		int n;
	char buff[100];
	while(1){
	bzero(buff,sizeof(buff));
	n = recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&cli, &len);
	sendto(sockfd, buff, n, 0, (struct sockaddr *)&cli, len);
	}
	close(sockfd);
	return 0;
}
