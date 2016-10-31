#!/usr/bin/python
import sys
import socket
import signal

print('hello')

#Register signal and define signal function
def signal_handler(signal, frame):
    #CLOSE IT
    sock.close()

    print('\nExiting with the highest amount of grace')
    sys.exit(0)
    
signal.signal(signal.SIGINT, signal_handler)

#Use localhost and port# passed at cmd line
host = '127.0.0.1'
port = 9999 

try:
    #Open socket and bind to desired host and port
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind( (host, int(port)) )

    print('Socket created, listening for connection...')

    #Listen with a backlog of 5
    sock.listen(1)

    #Accept a connect and store sock and addr
    (conn, addr) = sock.accept()
    print('Connection made, waiting for msg')

    while True:
        msg = conn.recv(1024);

        if msg:
            print('msg received: {0}').format(msg)
        elif msg == '###':
            print('closing chat connection')
            break

    conn.close()

except Exception as err:
    #If things go a bit haywire, go ahead and let the user know that
    print(err)
