#include <sys/types.h> // client - pic.c
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // gcc pic.c -o pic -lunp
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    char message[256] = "50", receiveMessage[256]; //Send/receive a message to server;
    int sockfd = 0;
    struct sockaddr_in info; //socket的連線
    double value = 0,value1=0, result = 0;
    pid_t pid,pid2;
    int fd[2];
    pipe(fd);
    pid2 = fork(); //fork a child process
    pid = fork(); //fork a child process
    if (pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed");
        return 1;
    } //socket的建立
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) { printf("Fail to create a socket."); }
    bzero(&info, sizeof(info));
    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost test
    if (pid == 0 && pid2 > 0) { // child process
        close(fd[0]);
        info.sin_port = htons(8900);
        int err = connect(sockfd, (struct sockaddr *) &info, sizeof(info));
        if (err == -1) { printf("Connection error"); }
        recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
        value = atof(receiveMessage);
        write(fd[1], &value, sizeof(value));
        close(fd[1]);
        close(sockfd);
    } else if (pid2 == 0 && pid > 0) {
        close(fd[0]);
        info.sin_port = htons(8700);
        int err = connect(sockfd, (struct sockaddr *) &info, sizeof(info));
        if (err == -1) { printf("Connection error"); }
        recv(sockfd, receiveMessage, sizeof(receiveMessage), 0);
        value = atof(receiveMessage);
        write(fd[1], &value, sizeof(value));
        close(fd[1]);
        close(sockfd);
    }else if (pid2 > 0 && pid > 0){
        pid2=wait(NULL);
        read(fd[0], &value1, sizeof(value1));
        pid=wait(NULL);
        read(fd[0], &value, sizeof(value));
        printf("parent Server: %.6f\n", value);
        printf("Child Server: %.6f\n", value1);
        printf("H(1,60): %.6f\n", value + value1);
    }
    return 0;
}