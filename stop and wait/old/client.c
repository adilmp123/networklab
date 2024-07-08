#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#define and &&
#define PORT 3000
// export DOCKER_HOST=unix:///var/run/docker.sock

typedef struct 
{
    char data[1024];
}Packet;

typedef struct 
{
    int frameID;
    int seqNo;
    int ack;
    Packet packet;
}Frame;

int main()
{
    int sockfd;
    struct sockaddr_in serverAddr;

    char buffer[1024];

    int frameID=0;
    Frame frameRecv; 
    Frame frameSend; 
    int ackRecv=1;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);

    while(true)
    {
        if(ackRecv==1)
        {
            frameSend.seqNo=frameID;
            frameSend.frameID=1;
            frameSend.ack=0;

            printf("Enter data: ");
            scanf("%s",&buffer);
            strcpy(frameSend.packet.data,buffer);
            sendto(sockfd,&frameSend,sizeof(Frame),0,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
            printf("Frame Send\n");
        }
        int addrSize= sizeof(serverAddr);
        int fRecvSize = recvfrom(sockfd,&frameRecv,sizeof(frameRecv),0,(struct sockaddr*)&serverAddr,&addrSize);
        if(fRecvSize>0 and frameRecv.seqNo==0 and frameRecv.ack==frameID+1)
        {
            printf("Ack received\n");
            ackRecv=1;
        }
        else
        {
            printf("Ack not received\n");
            ackRecv=0;
        }
    }
    close(sockfd);
    return 0;


}
