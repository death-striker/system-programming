//Client side implementation of UDP
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8006
#define MAX 1024
using namespace std;
// Driver code
int main() {
    int sockfd;
    char buffer[MAX];
    char hello[MAX] = "Hello from client";
    struct sockaddr_in servaddr;
    socklen_t len;

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;

    sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    cout<<"Hello message sent.\n";

    n = recvfrom(sockfd, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    buffer[n] = '\0';
    cout<<"Server :"<<buffer<<"\n";

    close(sockfd);
    return 0;
}
