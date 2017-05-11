#! /usr/bin/python
# -*- coding: utf-8 -*-

# telnet-client.py - A simple Telnet Client
# Bruno Mondelo Giaramita
# 2017-05-11 Escola Del Treball

import sys
import socket

################################################################

STDOUT = sys.stdout.write
STDERR = sys.stderr.write

HOST = "localhost"
PORT = 4172

# Character meaning the STX
START_CHARACTER = '\2'  # ASCII 4 STX

# Character meaning the ETX
END_CHARACTER = '\3'  # ASCII 4 ETX

# Character meaning the EOT
END_TRANSMISSION = '\4'  # ASCII 4 EOT

# Character meaning the ACK
ACK_TRANSMISSION = '\6'

# Create the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
s.connect((HOST, PORT))

while True:
  
  order_ask = str(raw_input("telnet> "))
  s.sendall(order_ask + END_TRANSMISSION)
  
  # End of receive message
  is_receiving = True
  
  while is_receiving:
    
    # Receive data from server
    data = s.recv(1024)
    
    # No data closed server
    if not data:
      STDERR("Server error!\n")
      break
    
    # Start receiving
    if data[-1] == START_CHARACTER:
      data = data[:-1]
      STDOUT("\nstdout:\n")
    
    # Received all STDOUT
    elif data[-1] == END_CHARACTER:
      data = data[:-1]
      STDOUT("\nstderr:\n")
    
    # Received all data
    elif data[-1] == END_TRANSMISSION:
      data = data[:-1]
      is_receiving = False
      
    # Show data received
    STDOUT(data)
    
    if is_receiving:
      s.sendall(ACK_TRANSMISSION)

# Close connection
s.close()

sys.exit(0)


