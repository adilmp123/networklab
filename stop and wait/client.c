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

int main() {
    int sockfd;
    int recvstatus, ackno;
    int frame_no, i;
    char buffer[max];
    struct timeval timeout;
    struct sockaddr_in server_address;

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    int server_size = sizeof(server_address);
    connect(sockfd, (struct sockaddr*)&server_address, server_size);

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    printf("Enter number of frames: ");
    scanf("%d", &frame_no);

    for (i = 0; i < frame_no; i++) {
        sprintf(buffer, "%d", i);
        print("Send Frame: %d", i);
        send(sockfd, buffer, max, 0);

        recvstatus = recv(sockfd, buffer, max, 0);

        if (recvstatus < 0) {
            print("Timeout error, resending frame %d", i);
            i--;  // Decrement i to resend the same frame
            continue;
        } else {
            ackno = atoi(buffer);
            print("Received ack: %d", ackno);
            if (ackno != i + 1) {
                print("Invalid ackno, resending frame %d", i);
                i--;  // Decrement i to resend the same frame
                continue;
            }
        }
    }
    sprintf(buffer, "%d", -1);
    send(sockfd, buffer, max, 0);
    close(sockfd);
}
