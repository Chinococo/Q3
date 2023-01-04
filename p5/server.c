#include<stdio.h> //udpc.c
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#define SERVER "127.0.0.1"
#define BUFLEN 255
#define PORT 8885
void die(char *s) {
    perror(s);
    exit(1);
}
unsigned long fsize(char* file) {
    FILE * f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
}
int main(int argc, char *argv[]) {
    char * name =(char *)malloc(sizeof(char)*100);
    //printf("%s",argv[1]);
    sprintf(name,"./%s",argv[1]);
    struct sockaddr_in si_other;
    char message[BUFLEN], fname[20], str[10];
    FILE *f;
    int s,i;
    unsigned long size;
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s ==-1) { die("socket"); }
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) { // converts the specified string,
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    FILE *fp = fopen(name, "rb");
    fseek(fp, 0L, SEEK_END);
    unsigned char buff[255] = {0};
    // calculating the size of the file
    long int res = ftell(fp);
    sprintf(buff,"%ld", res);
    //printf("%s",buff);
    fclose(fp);
    sendto(s, buff,  sizeof(buff) ,0, (struct sockaddr *) &si_other, sizeof(si_other));
    fp = fopen("./google.png", "rb");
    
    while (1) {
/* First read file in chunks of 256 bytes */
        //unsigned char buff[256] = {0};
        int nread = fread(buff, 1, 255, fp);
        //printf("Bytes read %d \n", nread);
        if (nread > 0) {
            //printf("Sending %s\n",buff);
            sendto(s, buff, sizeof(buff), 0 , (struct sockaddr *) &si_other, sizeof(si_other));
        }
/* There is something tricky going on with read ..
* Either there was error, or we reached end of file. */
        if (nread < 255) {
            /*
            if (feof(fp))
                printf("End of file\n");
            if (ferror(fp))
                printf("Error reading\n");*/
             break;   
        }
    }
    
    fclose(fp);
    close(s);
    return 0;
}