#!/usr/bin/python
import sys
import socket
import signal

#Make sure usage is correct
if(len(sys.argv) != 2):
    print("usage: ./code.py port")
    sys.exit(1)

#Register signal and define signal function
def signal_handler(signal, frame):
    #CLOSE IT
    sock.close()

    print('\nExiting with the highest amount of grace')
    sys.exit(0)
    
signal.signal(signal.SIGINT, signal_handler)

#Use localhost and port# passed at cmd line
host = '127.0.0.1'
port = sys.argv[1] 

try:
    #Open socket and bind to desired host and port
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind( (host, int(port)) )

    print('Socket created.')

    #Listen with a backlog of 5
    sock.listen(1)

    while True:

        print('Listening for new connection...')

        #Accept a connect and store sock and addr
        (conn, addr) = sock.accept()
        name = conn.recv(500)
        name = name.decode()
        print('Connection made with {0}, waiting for message...'.format(name))

        #Constantly exchange messages with connection
        while True:
            print('{0}> '.format(name), end="", flush=True)
            msg = conn.recv(500);

            #If the message sent is to quit, then break out of while loop
            if msg.decode() == '\\quit':
                print('\n{0} has closed the connection.'.format(name))
                break
            #Else print message to screen and prompt for return message
            elif msg:
                print(msg.decode())
                msg = input('ChatServer> ')
                conn.send(msg.encode())

        #Close the connection
        conn.close()

except Exception as err:
    #If things go a bit haywire, go ahead and let the user know that
    print(err)
