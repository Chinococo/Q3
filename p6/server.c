//server.c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
  int welcomeSocket, newSocket, portNum, clientLen, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
  int i;

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  portNum = 7895;
  
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portNum);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  if(listen(welcomeSocket,5)==0)
    printf("");
  else
    printf("Error\n");

  addr_size = sizeof serverStorage;
  /*loop to keep accepting new connections*/
  while(1){
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    /*fork a child process to handle the new connection*/
    if(!fork()){
      nBytes = 1;
      /*loop while connection is live*/
      while(nBytes!=0){
        nBytes = recv(newSocket,buffer,1024,0);
        char * data = malloc(sizeof(char)*100);
        printf("Client said: %s\n",buffer);
        if (buffer[0]=='B'&&buffer[1]=='y'&&buffer[2]=='e'){
        	printf("close Socket");
        	shutdown(welcomeSocket,2);
        	return 0;
        	close(newSocket);
        }
        scanf("%s",data);
        send(newSocket,data,sizeof(data),0);
        printf("%d",strcmp(data,"Bye"));
        if (data[0]=='B'&&data[1]=='y'&&data[2]=='e'){
        	printf("close Socket");
        	shutdown(welcomeSocket,2);
        	return 0;
        	exit(0);
        }
      }
      close(newSocket);
      exit(0);
    }
    /*if parent, close the socket and go back to listening new requests*/
    else{
      close(newSocket);
    }
  }

  return 0;
}

