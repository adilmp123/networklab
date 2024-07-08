#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> 
#include <arpa/inet.h> 
#define max 1024
#define port 3000
#define print printf("\n");printf

int main()
{
    int sockfd;
    int recvstatus,flag=1,ackno;
    int win_size,frame_no,win_start,win_end,i;
    char buffer[max];
    struct timeval timeout;
    struct sockaddr_in server_address;

    timeout.tv_sec=5;
    timeout.tv_usec=0;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int server_size = sizeof(server_address);
    connect(sockfd,(struct sockaddr*)&server_address,server_size);

    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

    printf("Enter windowsize and no of frames: ");
    scanf("%d",&win_size);
    scanf("%d",&frame_no);

    win_start=0;
    win_end=win_size-1;
    i=win_start;

    while(win_start<win_end)
    {
        while(i<=win_end)
        {
            sprintf(buffer,"%d",i);
            print("Send Frame: %d",i);
            send(sockfd,buffer,max,0);
            i++;
        }

        recvstatus = recv(sockfd,buffer,max,0);

        if(recvstatus<0)
        {
            print("Time out Error, resending frames %d to %d",win_start,win_end);
            i=win_start;
            continue;
        }
        else
        {
            ackno = atoi(buffer);
            print("received ack: %d",ackno);
            if(ackno==win_start+1)
            {
                win_start++;
                if(win_end<frame_no-1) win_end++; 
            }
            else
            {
                print("Invalid ackno resending frames %d to %d",win_start,win_end);
                i=win_start;
                continue;
            }
        }
    }
    sprintf(buffer,"%d",-1);
    send(sockfd,buffer,max,0);
    close(sockfd);
}