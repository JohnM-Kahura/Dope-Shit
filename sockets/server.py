#!/usr/bin/python

import socket               # Import socket module

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)         # Create a socket object
host = socket.gethostbyname(socket.gethostname()) # Get local machine name
port = 12345                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

print( 'host ip', host)
s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   print ('Got connection from', addr)
   c.send('Thank you for connecting'.encode('utf-8'))
  
   c.close()                # Close the connection

