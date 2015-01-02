#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>

int main(int argc,char *argv[])
{
    int sockfd;
    char sendbuffer[200];
    char recvbuffer[200];
    struct sockaddr_in server_addr;
    struct hostent *host;
    int portnumber,nbytes;

    
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
 	exit(1);
    }

    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(3490);
    server_addr.sin_addr.s_addr=inet_addr("192.168.1.104");

    if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
	fprintf(stderr,"Connect error:%s\n",strerror(errno));
 	exit(1);
    }

    while(1)
    {
 	printf("Please input your word:\n");
  	scanf("%s",sendbuffer);
  	printf("1 : %s\n",sendbuffer);
  	if(strcmp(sendbuffer,"quit")==0)
     	{	
		printf("2\n");
		break;
	}
  	send(sockfd,sendbuffer,sizeof(sendbuffer),0);
	printf("3");  
	recv(sockfd,recvbuffer,200,0);
  	printf("recv data of my world is :%s\n",recvbuffer);
    }
    printf("4\n");
    close(sockfd);
    exit(0);
}
