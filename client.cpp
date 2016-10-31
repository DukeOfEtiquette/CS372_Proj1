#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define PORT_NUM 9999
#define MSG_LEN 1024

int main(int argc, char **argv)
{
    char rcvMsg[MSG_LEN], sndMsg[MSG_LEN];
    struct sockaddr_in servAddr;
    struct hostent *server;

    //Create the client socket
    int client = socket(AF_INET, SOCK_STREAM, 0);

    //Verify socket was created, print message to std with result
    if(client < 0)
    {
        std::cout << "ERROR: Unable to create client socket.\n";
        return 1;
    }else
    {
        std::cout << "Client socket created successfully.\n";
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT_NUM);

    server = gethostbyname("localhost");
    bcopy((char *)server->h_addr, (char *)&servAddr.sin_addr.s_addr, server->h_length);


    int res = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));

    if(res == 0)
        std::cout << "Connection established on port number: " << PORT_NUM << std::endl;
    else{
        std::cout << "ERROR: Connection could not be established on port number: " << PORT_NUM << std::endl;
        close(client);
        return 1;
    }

    std::cout << "Sending msg...\n";
    char msg[] = "Hello server!";
    write(client, msg, strlen(msg));

    std::cout << "Receiving msg...\n";
    bzero(rcvMsg, MSG_LEN);
    recv(client, rcvMsg, MSG_LEN, 0);

    std::cout << "Msg rcv'd: " << rcvMsg << std::endl;

    close(client);

    return 0;
}
