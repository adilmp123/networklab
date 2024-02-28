#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PORT 3000       
int main()
{
    int socketDescriptor;
    int clientSocket;
    char storageBuffer[100];
    int lengthOfAddress;
    int optionValue=1;
    struct sockaddr_in connectionAddress;
    struct sockaddr_in serverAddress;
    char * message = "Hi client, this is server";
    socketDescriptor = socket(AF_INET,SOCK_STREAM,0);

    if(socketDescriptor<0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    int status = setsockopt(socketDescriptor,SOL_SOCKET,SO_REUSEADDR,&optionValue,sizeof(optionValue));

    if(status<0)
    {
        perror("Couldn't set options");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_zero[8]='\0';
    status=bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
    if(status<0){
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    status = listen(socketDescriptor,4);

    if(status<0)
    {
        perror("Couldn't listen for connections");
        exit(EXIT_FAILURE);
    }

    lengthOfAddress = sizeof(connectionAddress);

    clientSocket = accept(socketDescriptor,(struct sockaddr*)&connectionAddress,&lengthOfAddress);

    if(clientSocket<0)
    {
        perror("couldn't establish a connection with client");
        exit(EXIT_FAILURE);
    }

    read(clientSocket,storageBuffer,100);

    printf("message from client: %s\n",storageBuffer);

    send(clientSocket,message,strlen(message),0);

    close(socketDescriptor);
    close(clientSocket);

    return 0;
}
