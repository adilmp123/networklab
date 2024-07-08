#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#define port 3000
#define max 100

int main()
{
    int n;
    char name[max],recvline[max];
    printf("Enter file name: ");
    scanf("%s",name);
    printf("\n");
    int sockfd;
    struct sockaddr_in serverAddress;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family=AF_INET;    
    serverAddress.sin_port=htons(port);    
    serverAddress.sin_addr.s_addr=INADDR_ANY;    
    int size = sizeof(serverAddress);
    connect(sockfd,(struct sockaddr*)&serverAddress,size);
    write(sockfd,name,max);

    while((n=read(sockfd,recvline,max))!=0)
    {
        printf("%s",recvline);
    }
}