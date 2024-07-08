#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define max 1024
#define print printf("\n");printf

void main()
{
    int sockfd;
    int newsockfd;
    int recvstatus,flag=1,ackno;
    int win_size,frame_no,win_start,win_end,i;
    char buffer[max];
    struct sockaddr_in server_address,client_address;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3000);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int server_size = sizeof(server_address);
    int client_size = sizeof(client_address);

    int next_frame_no=0;

    bind(sockfd,(struct sockaddr*)&server_address,server_size);
    
    listen(sockfd,5);
    newsockfd = accept(sockfd,(struct sockaddr*)&client_address,&client_size);

    while(1)
    {
        recv(newsockfd,buffer,max,0);
        frame_no=atoi(buffer);
        srand(time(0));
        sleep(2);
        if(frame_no==next_frame_no)
        {
            if(rand()%50<10)
            {
                print("lost frame");
                continue;
            }
            next_frame_no++;
            print("received frame %d",frame_no);
            print("sent ack %d",next_frame_no);
            sprintf(buffer,"%d",next_frame_no);
            send(newsockfd,buffer,max,0);
        }
        else if(frame_no==-1)
        {
            print("received %d frames",next_frame_no);
            break;
        }
        else
        {
            print("received frame %d",frame_no);
            print("discarding due to ouut of order");
        }
        
    }
    
    close(newsockfd);
    close(sockfd);
}