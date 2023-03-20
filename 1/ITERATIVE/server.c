#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>

void func(int sockfd){
	int n;
	char buff[100];
	while(1){
		bzero(buff, 100);
		n = read(sockfd, buff, 100);
		printf("From client : %s\nTo client : ", buff);
		n = 0;
		bzero(buff, 100);
		while((buff[n++] = getchar()) != '\n');
		write(sockfd, buff, n);
	}
}

int main(){
	int sockfd, connfd, len;
	struct sockaddr_in serv, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(16001);
	bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	listen(sockfd, 5);
	len = sizeof(cli);

	connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
	func(connfd);

	close(sockfd);

	return 0;
}
