//client.c
//client.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  clientSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 7895;

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  while(1){
    fgets(buffer,1024,stdin);
    nBytes = strlen(buffer) + 1;

    send(clientSocket,buffer,nBytes,0);
    if (buffer[0]=='B'&&buffer[1]=='y'&&buffer[2]=='e'){
        	printf("close Socket\n");
        	exit(0);
    }	
    recv(clientSocket, buffer, 1024, 0);
    printf("Server Said: %s\n",buffer);   
    if (buffer[0]=='B'&&buffer[1]=='y'&&buffer[2]=='e'){
        	printf("close Socket\n");
        	exit(0);
    }
  }

  return 0;
}
