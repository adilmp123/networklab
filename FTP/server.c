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
    char buff[4096];
    int sockfd,newsockfd;
    struct sockaddr_in serverAddress,connectionAddress;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family=AF_INET;    
    serverAddress.sin_port=htons(port);    
    serverAddress.sin_addr.s_addr=INADDR_ANY;    
    int size = sizeof(serverAddress);
    int csize = sizeof(connectionAddress);
    
    bind(sockfd,(struct sockaddr *)&serverAddress,size);
    
    listen(sockfd,4);
    newsockfd = accept(sockfd,(struct sockaddr*)&connectionAddress,&csize);
    
    read(newsockfd,name,max);
    FILE* f1 = fopen(name,"r");

    while(fgets(buff,4096,f1)!=NULL)
    {
        write(newsockfd,buff,max);
    }
}