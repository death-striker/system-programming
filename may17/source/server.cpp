#include <iostream>
#include "../include/func.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
using namespace std;
int main(int argc, char* argv[]){
        createSM();
        int sock = createSocket("0.0.0.0",8006);
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
	//Creating  new process for each client
        while(1){
        int client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_addr_len);
        if(client_sock < 0){
		perror("accept error");
            return -1;
        }
        cout << "client accepted successfully" << endl;
        int clientsNO = writeSM();
        cout << "Number of clients connected : " << clientsNO << endl;

        pid_t pid = fork();
        if(pid < 0){
		perror("fork error");
            return -1;
        }
        else if(pid == 0){
            close(sock);
            char buf[1024];
            while(1){
                memset(buf, 0, sizeof(buf));
                int len = recv(client_sock, buf, sizeof(buf), 0);
                if(len < 0){
			perror("recv error");
                    return -1;
                }
                else if(len == 0){
                    cout << "client closed" << endl;
                    break;
                }
		/*else if(buf=="bye"){
			cout<<"client closed"<<endl;
			break;
		}*/
                else{
                    cout << "client send: " << buf << endl;
                    memset(buf,0,sizeof(buf));
                    //if(buf!="bye"){
		    cout << "please input: ";
                    cin.getline(buf,sizeof(buf));
                    send(client_sock, buf, strlen(buf), 0);
		    //}
                }
            }
            close(client_sock);
            exit(0);
        }
        else{
            close(client_sock);
        }
    }
    destroySM();
    close(sock);
}
