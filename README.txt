Compile client.cpp with:

    g++ client.cpp -o chatclient

Run client with:

    ./chatclient SERVER_ADDRESS PORT_NUM

Run server with:

    python3 server.py PORT_NUM

Once you start the server you will wait for a connection and for the first message before
you get a chance to reply. Send SIGINT to shut it down.

Once you start the client you will be prompted to enter your user name. You will
then be prompted to send the first message and will wait for a response. Send '\quit'
to close the connection.
