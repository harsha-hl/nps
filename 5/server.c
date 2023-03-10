#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>

void func(int connfd1, int connfd2){
	int n;
	char buff[1000];
	while(1){
		if((n = read(connfd1, buff, sizeof(buff))) > 0){
		write(connfd2, buff, n);
		n = read(connfd2, buff, sizeof(buff));
		write(connfd1, buff, n);
	}
	else{
		n = read(connfd2, buff, sizeof(buff));
		write(connfd1, buff, n);
		n = read(connfd1, buff, sizeof(buff));
		write(connfd2, buff, n);
	}

	}

}

int main(){
	int sockfd, connfd1, connfd2, len;
	struct sockaddr_in serv, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(16001);
	bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));
	listen(sockfd, 5);
	len = sizeof(cli);
	while(1){
		connfd1 = accept(sockfd, (struct sockaddr *)&cli, &len);
		connfd2 = accept(sockfd, (struct sockaddr *)&cli, &len);
		if(fork() == 0){
			close(sockfd);
			func(connfd1, connfd2);
		}
	}
		close(sockfd);
		close(connfd1);
		close(connfd2);
	return 0;
}
