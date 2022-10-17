#!/usr/bin/python
# # This is client.py file

import socket # Import socket module
import time
s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name/for this example
ports = 12345             #server port
portc = 32451 	   #client's own port for incoming connections (if any)
s.bind((host, portc))
s.connect((host, ports))
print(s.recv(1024))

while True:
   co, addr = s.accept()     # Establish connection with server.
   print ('Got connection from', addr)
   co.send('Thank you for connecting'.encode('utf-8'))
  

   co.send('hello'.encode('utf-8'))

   co.close ()                    # Close the socket when done
