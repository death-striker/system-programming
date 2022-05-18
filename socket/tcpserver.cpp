//The program to create a test TCP server
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
        struct sockaddr_in servaddr, cliaddr;
        char smsg[MAX] = "Hello from server to client";
        char cmsg[MAX];
        int sockfd,mlen,slen,connfd;//Initialising sock filedescriptor, message length, structure length
        socklen_t clen;
        slen = sizeof(sockaddr_in);
        memset(&servaddr,0,slen);
        memset(&cliaddr,0,slen);
        memset(cmsg,0,MAX);


        servaddr.sin_family = AF_INET;//To use internet family of addressing
        servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
        servaddr.sin_port = htons(PORTNO);


        sockfd = socket(AF_INET,SOCK_STREAM,0);
        bind(sockfd,(const struct sockaddr *)&servaddr,slen);
        listen(sockfd,5);

        connfd=accept(sockfd,(struct sockaddr *) &cliaddr, &clen);

        mlen=recv(connfd,cmsg,MAX,0);
        cout << cmsg << endl;
        mlen=send(connfd,smsg,strlen(smsg),0);
        cout << "Message sent from the server" << endl;
        close(connfd);
}
