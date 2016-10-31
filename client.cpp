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

int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    std::string ip =  "127.0.0.1";

    //Create the client socket
    int client = socket(AF_INET, SOCK_STREAM, 0);

    //Verify socket was created, print message to std with result
    if(client < 0)
    {
        std::cout << "Error encountered while creating the client socket.\n";
        return 1;
    }else
    {
        std::cout << "Client socket created successfully.\n";
    }


    close(client);

    return 0;
}
