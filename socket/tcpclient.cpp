//The program to create a test TCP Client
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define ADDRSERV "127.0.0.1"
#define PORTNO 8006
#define MAX 256
using namespace std;


int main() {
        struct sockaddr_in servaddr;
        char cmsg[MAX] = "Hello from client to server";
        char smsg[MAX];
        int sockfd,mlen,slen;//Initialising sock filedescriptor, message length, structure length
        socklen_t servaddrlen;
        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);

        memset(smsg,0,MAX);


        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);


        sockfd = socket(AF_INET,SOCK_STREAM,0);

        connect(sockfd,(struct sockaddr *)&servaddr,slen);
        mlen=send(sockfd,cmsg,strlen(cmsg),0);
        cout << "Message sent from the client" << endl;
        mlen=recv(sockfd,smsg,MAX,0);
        cout << smsg << endl;
        close(sockfd);
}
