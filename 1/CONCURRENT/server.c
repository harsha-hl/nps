#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h> //sockaddr_in
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int connfd){
	char buff[MAX];
	int n;
	for(;;){
		bzero(buff,MAX);

		read(connfd, buff, sizeof(buff));
		printf("From client: %s\n To client :", buff);
		bzero(buff,MAX);
		n=0;
		while((buff[n++] = getchar()) != '\n');
		write(connfd, buff, sizeof(buff));

		if(strncmp("exit", buff, 4) == 0){
			printf("Server Exit.\n");
			break;
		}
	}
}

int main(){
	int sockfd, connfd, len, clientNum = 1;
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Socket creation failed\n");
		exit(0);
	}
	else printf("Socket successfully created.\n");
	bzero(&servaddr, sizeof(servaddr));


	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(15001);

	if(bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
		printf("Soket bind failed.\n");
		exit(0);
	}
	else printf("Socket bind successfull.\n");

	if(listen(sockfd, 5) != 0){
		printf("Listen failed.\n");
		exit(0);
	}
	else printf("Server listening.\n");
	len = sizeof(cli);

	while(1){
		connfd = accept(sockfd, (SA*)&cli, &len);
		if(connfd < 0){
			printf("Server accept failed.\n");
			exit(0);
		}
		else {
			pid_t id = fork();
			if(id == 0){
				close(sockfd);
				func(connfd);	
			}
			else close(connfd);		
		}
	}
}
