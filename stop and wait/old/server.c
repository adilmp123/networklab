#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#define PORT 3000
#define and &&

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
    int sockfd, addrSize;
    struct sockaddr_in serverAddr, cli;
    char buffer[1024];

    int frameID=0;
    Frame frameRecv, frameSend;

    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    serverAddr.sin_addr.s_addr=INADDR_ANY;
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    addrSize = sizeof(cli);
    while (true)
    {
        int f_recv_size = recvfrom(sockfd, &frameRecv, sizeof(Frame), 0, (struct sockaddr *)&cli, &addrSize);
        if (f_recv_size > 0 && frameRecv.frameID == 1 && frameRecv.seqNo == frameID)
        {
            printf("[+]Frame Recieved : %s\n", frameRecv.packet.data);

            frameSend.seqNo = 0;
            frameSend.frameID = 0;
            frameSend.ack = frameRecv.seqNo + 1;
            sendto(sockfd, &frameSend, sizeof(frameSend), 0, (struct sockaddr *)&cli, addrSize);
            printf("[+]Ack Send\n");
        }
        else
        {
            printf("[+]Frame Not Recieved\n");
        }
        frameID++;
    }
    close(sockfd);
    return 0;  
}
