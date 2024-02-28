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
    char storageBuffer[100];
    int lengthOfAddress;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
    char * message = "Hi client, this is server";

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    if(socketDescriptor < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr)) < 0)
    {
        perror("Couldn't bind socket");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        lengthOfAddress = sizeof(clientAddress);

        if(recvfrom(socketDescriptor, storageBuffer, sizeof(storageBuffer), 0, (struct sockaddr*)&clientAddress, (socklen_t*)&lengthOfAddress) < 0)
        {
            perror("Couldn't receive data");
            exit(EXIT_FAILURE);
        }

        printf("Message from client: %s\n", storageBuffer);

        if(sendto(socketDescriptor, message, strlen(message), 0, (struct sockaddr*)&clientAddress, lengthOfAddress) < 0)
        {
            perror("Couldn't send response");
            exit(EXIT_FAILURE);
        }
    }

    close(socketDescriptor);

    return 0;
}
