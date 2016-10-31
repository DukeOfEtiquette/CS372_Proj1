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
    struct sockaddr_in servAddr;
    std::string ip =  "127.0.0.1";

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

    int res = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));

    if(res == 0)
        std::cout << "Connection established on port number: " << PORT_NUM << std::endl;
    else{
        std::cout << "ERROR: Connection could not be established on port number: " << PORT_NUM << std::endl;
        close(client);
        return 1;
    }

    close(client);

    return 0;
}
