#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define MSG_LEN 500

int main(int argc, char **argv)
{
    struct sockaddr_in servAddr;
    struct hostent *server;

    char usrName[MSG_LEN];

    //Get user name from client
    std::cout << "Please enter your session user name: ";
    scanf("%s", usrName);

    //Clear out stdin
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    //Store max send message length
    int sndLen = MSG_LEN - strlen(usrName); 

    //Create arrays for messages being received and sent
    char rcvMsg[MSG_LEN], sndMsg[sndLen];

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

    //Define server info that we are connecting to
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));

    server = gethostbyname(argv[1]);
    bcopy((char *)server->h_addr, (char *)&servAddr.sin_addr.s_addr, server->h_length);


    //Attempt to make a connection
    int res = connect(client, (struct sockaddr *)&servAddr, sizeof(servAddr));

    //Make sure it connected, otherwise exit
    if(res == 0)
        std::cout << "Connection established on port number: " << argv[2] << std::endl;
    else{
        std::cout << "ERROR: Connection could not be established on port number: " << argv[2] << std::endl;
        close(client);
        return 1;
    }

    write(client, usrName, strlen(usrName));

    //Formatting
    std::cout << std::endl;

    //While true loop that allows the client to send the first message
    //and waits for a response from the server
    while(1)
    {
        //Prompt client for a message to send
        std::cout << usrName << "> ";
        bzero(sndMsg, sndLen);
        fgets(sndMsg, sndLen, stdin);
        strtok(sndMsg, "\n");

        if(strcmp(sndMsg, "\\quit") == 0)
        {
            write(client, sndMsg, strlen(sndMsg));
            close(client);
            return 0;
        }

//        //Clear out buffer
//        bzero(rcvMsg, MSG_LEN);

        //Build message to send to chat server
//        strcat(rcvMsg, usrName);
//        strcat(rcvMsg, ": ");
//        strcat(rcvMsg, sndMsg);

        //Send the message
        write(client, sndMsg, strlen(sndMsg));
        //write(client, rcvMsg, strlen(rcvMsg));

        //Wait for a message receipt
        bzero(rcvMsg, MSG_LEN);
        recv(client, rcvMsg, MSG_LEN, 0);

        std::cout << "ChatServer> " << rcvMsg << std::endl;
    }

    close(client);

    return 0;
}
