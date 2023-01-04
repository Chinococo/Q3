#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
int CharToInt(char * data){
	int a = 0;
	for(int i=0;i<strlen(data);i++)
		a*=10,a+=(data[i]-'0');
	return a;
}
int main(int argc , char *argv[])

{
    //socket的建立
    char inputBuffer[256] = {};
    char *message = (char *)malloc(sizeof(char)*20);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(message,"%3d/%2d/%2d", tm.tm_year -11, tm.tm_mon + 1, tm.tm_mday);
    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(CharToInt(argv[1]));
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    listen(sockfd,5);

    while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        //recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        send(forClientSockfd,message,sizeof(message)+4,0);
        printf("Send To Client : %s\n",message);
    }
    return 0;
}