#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
	int sockfd;
	struct ip_mreq mreq;
	struct sockaddr_in serv;
	
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	
	u_int yes = 1;
	
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=htonl(INADDR_ANY); 
	serv.sin_port=htons(12345);
	
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes))<0){
		perror("Reuse error");
		exit(0);
	}

	if(bind(sockfd,(struct sockaddr*)&serv,sizeof(serv))!=0){
		printf("Bind Error");
		exit(0);
	}
	
	mreq.imr_multiaddr.s_addr = inet_addr("225.0.0.37");
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	
	if(setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0){
		perror("member error");
		exit(0);
	}
	
	char buffer[1024];
	
	while(1){
		int len = sizeof(serv);
		recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&serv,&len);
		printf("%s",buffer);	
		bzero(buffer,sizeof(buffer));
	}
	return 0;
}
