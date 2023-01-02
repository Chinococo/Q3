#include<stdio.h> //udps.c
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define BUFLEN 256
#define PORT 8885

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    struct sockaddr_in si_me, si_other;
    int s, slen = sizeof(si_other), recv_len = 0;
    unsigned long flen = 0;
    char buf[BUFLEN], fname[20];
    FILE *fp;
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) == -1) {
        die("bind");
    }
    recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen);
    int len = atoi(buf);
    strcpy(fname, "output.png");
    fp = fopen(fname, "wb");
    memset(buf, 0, BUFLEN);
    for(int i=0;i<len/256+1;i++){
        recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, &slen);
        //printf("%lld\n", recv_len);
        //printf("string is: %s\n", buf);
        fwrite(buf, recv_len , 1, fp);
    }
    fclose(fp);
    close(s);
    return 0;
    
}