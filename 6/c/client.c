#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>

void func(int sockfd){

}

int main(int argc, char* argv[]){
	int sockfd;
	struct sockaddr_in serv;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&serv, sizeof(serv));
	serv.sin_family = AF_INET;
	//serv.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET, argv[1], &serv.sin_addr);
	serv.sin_port = htons(16001);
	int n;
	char buff[100];
	while(1){
		n = 0;
		bzero(buff, 100);
		printf("Enter string : ");
		while((buff[n++] = getchar()) != '\n');
		sendto(sockfd, buff, n,0 ,(struct sockaddr *)&serv, sizeof(serv));
		bzero(buff, 100);
		n = recvfrom(sockfd, buff, sizeof(buff),0,NULL,NULL);
		printf("From server : %s\n", buff);
		
	}
	close(sockfd);
	return 0;
}
