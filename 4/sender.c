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
	struct sockaddr_in serv;
	
	sockfd= socket(AF_INET,SOCK_DGRAM,0);
	
	//memset(&serv,0,sizeof(serv));
	bzero(&serv,sizeof(serv));
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=inet_addr("225.0.0.37"); 
	serv.sin_port=htons(12345);

	
	while(1){
		char buffer[1024];
		int n =0;
		printf("Enter Broadcast Message : ");
		while((buffer[n++] = getchar())!='\n');
		sendto(sockfd,buffer,n,0,(struct sockaddr*)&serv,sizeof(serv));
	}
	
	
}
