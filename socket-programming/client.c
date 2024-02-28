#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define PORT 3000

int main()
{
    struct sockaddr_in serverAddress;
    char * message = "Hi server, this is client";
    char recieverBuffer[100];
    int socketDescriptor =  socket(AF_INET,SOCK_STREAM,0);

    if(socketDescriptor<0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }   
    int status = 0;
    serverAddress.sin_family=AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_zero[8]='\0';
    status = connect(socketDescriptor,(struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(status < 0)
    {
        perror("error in connecting with the server");
        exit(EXIT_FAILURE);
    }

    write(socketDescriptor,message,strlen(message));
    read(socketDescriptor,recieverBuffer,100);
    printf("Message from the server: %s\n",recieverBuffer);

    close(socketDescriptor);
    return 0;

}
