//This program creates a TCP client and connects with TCP server
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
using namespace std;
int main(int argc,char* argv[]){
        const char* port = "8006";
        int portno = atoi(port);
        //create a socket
        int socketid = socket(AF_INET,SOCK_STREAM,0);
        if(socketid==-1){
		perror("socket failed");
                return -1;
        }
        cout << "***Socket created successfully***" << endl;

        //create a server address to connect
        struct sockaddr_in serveraddr;

        //clear the structure
        memset(&serveraddr,0,sizeof(serveraddr));

        //set the server address
        serveraddr.sin_family=AF_INET;
        serveraddr.sin_port=htons(portno);
        serveraddr.sin_addr.s_addr= inet_addr("127.0.0.1");

        //connect to the server
        int connect_status = connect(socketid,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
        if(connect_status==-1){
                perror("connection failed");
                return -1;
        }
        cout << "***Connection successful***" << endl;
        cout << "Enter the message to be sent to the server : ";//message to the server
        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
		perror("Message failed");
                return -1;
        }
        cout << "***Message sent successfully***" << endl;

        while(1){

        char buffer[256];// buffer to store message
        memset(buffer,0,sizeof(buffer));//clear the buffer

        //receive the message
        int len=sizeof(serveraddr);
        ssize_t receive_status = recv(socketid,buffer,256,0);
        if(receive_status==-1){
                cout<<"Message receiving failed"<<endl;
                return -1;
        }
        else if(receive_status==0){
                cout<<"Server closed the connection"<<endl;
                break;
        }
        cout << "***Message received successfully***" << endl;

        cout<<"Message received : "<<buffer<<endl; //print the message

        if(strcmp(buffer,"bye")==0)
        break;

        cout << "Message to be sent to the server : ";//message to server
        const char* message;
        string m;
        getline(cin,m);
        message = m.c_str();
        ssize_t send_status = send(socketid,message,strlen(message),0);
        if(send_status==-1){
		perror("Message sending failed");
                return -1;
        }
        cout << "***Message sent***" <<endl;
        if(strcmp(message,"bye")==0)
        break;
        }
        //close the socket
        close(socketid);
}
