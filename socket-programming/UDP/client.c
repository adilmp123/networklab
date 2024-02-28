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
    int socketDescriptor;

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketDescriptor < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }   

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(sendto(socketDescriptor, message, strlen(message), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("error in sending message to the server");
        exit(EXIT_FAILURE);
    }

    socklen_t lengthOfAddress = sizeof(serverAddress);
    if(recvfrom(socketDescriptor, recieverBuffer, sizeof(recieverBuffer), 0, (struct sockaddr*)&serverAddress, &lengthOfAddress) < 0)
    {
        perror("error in receiving response from the server");
        exit(EXIT_FAILURE);
    }

    printf("Message from the server: %s\n", recieverBuffer);

    close(socketDescriptor);
    return 0;
}
