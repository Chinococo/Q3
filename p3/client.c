#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int CharToInt(char * data){
	int a = 0;
	for(int i=0;i<strlen(data);i++)
		a*=10,a+=(data[i]-'0');
	return a;
}
int main(int argc , char *argv[])
{
    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;
	
    //localhost test
    	//printf("%s\n",argv[1]);	
	//printf("%d\n",CharToInt(argv[2]));	
    info.sin_addr.s_addr = inet_addr(argv[1]);
    info.sin_port = htons(CharToInt(argv[2]));


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


    //Send a message to server
    char receiveMessage[1000] = {};
    //send(sockfd,message,sizeof(message),0);
    recv(sockfd,receiveMessage,sizeof(receiveMessage)+1,0);

    printf("%s\n",receiveMessage);
    //printf("close Socket\n");
    close(sockfd);
    return 0;
}