#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//Server – pis.c, gcc pis.c -o simples -lunp
#include <math.h>

double get() {
    double ans = 0;
    for(int i=1;i<=30;i++)
        ans += (double)(1/(double)i);
    return ans;    
}

int main(int argc, char *argv[]) {
    double r = 0;
    int y = 0;
    char message[256], inputBuffer[256];
    int sockfd = 0, clientSockfd = 0; //socket的建立
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { printf("Fail to create a socket."); }
    struct sockaddr_in serverInfo, clientInfo; //socket的連線
    int addrlen = sizeof(clientInfo);
    bzero(&serverInfo, sizeof(serverInfo));
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd, (struct sockaddr *) &serverInfo, sizeof(serverInfo));
    listen(sockfd, 8);
    while (1) {
        clientSockfd = accept(sockfd, (struct sockaddr *) &clientInfo, &addrlen);
        r = get();
        snprintf(message, sizeof(message), "%.12f", r);
        send(clientSockfd, message, sizeof(message), 0);
        printf("calculate H(1) to H(30):%.6f\n", message);
    }
    return 0;
}