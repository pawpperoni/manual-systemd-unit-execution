#! /usr/bin/python
# -*- coding: utf-8 -*-

# chat-server.py - A simple Chat Server
# Bruno Mondelo Giaramita
# 2017-05-15 Escola Del Treball

import sys
import socket
import select
import signal

################################################################

def sigterm_handler (signum, frame):
  
  """
  SIGTERM signal handler
  Input: int
  Output: None
  """
  
  STDOUT("Received SIGTERM: Closing server\n")
  FLOUT()
  
  # Close socket if openned
  if s:
    s.close()
  
  # Exit
  sys.exit(0)
  
################################################################

# Signal handler
signal.signal(signal.SIGTERM, sigterm_handler)

# Output variables
STDOUT = sys.stdout.write
FLOUT = sys.stdout.flush
STDERR = sys.stderr.write
FLERR = sys.stderr.flush

# Socket information
HOST = ""
PORT = 3598

# The password to login
PASSWORD = "mypass"

# The client information
client_list =  {}
"""
The form of the dictionary:
  Key: Connection
  Value: Boolean (Password inserted)
"""

# Create the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket
s.bind((HOST, PORT))

# Listen
s.listen(1)

# List desctriptor of connections
list_connections = [s]

STDOUT("Started server with port: {}\n".format(PORT))
FLOUT()

while True:
  
  # Stay in select
  alive, x, y = select.select(list_connections, [], [])
  
  # Process select
  for actual in alive:

    # New change on main socket = new connection
    if actual == s:
      # Accept connection
      try:
        conn, addrs = actual.accept()
      except:
        STDERR("Error accepting new connection: {}\n".format(addrs[0]))
        FLERR()
        continue
      
      # Add to select list
      list_connections.append(conn)
      
      # Add to clients information
      client_list[conn] = False
      
      # Send the password prompt
      conn.send("Password: ")
      
      STDOUT("Accepted new client: {}\n".format(addrs[0]))
      FLOUT()
      
    # New change in the connected
    else:
      # Receive data
      try:
        data = actual.recv(1024)
      except:
        STDERR("Client closed abruptly\n")
        FLERR()
        actual.close()
        list_connections.remove(actual)
        client_list.pop(actual, None)
        continue
      
      # No data, no client
      if not data:
        STDERR("Closed client: {}\n".format(actual.getpeername()[0]))
        FLERR()
        actual.close()
        list_connections.remove(actual)
        client_list.pop(actual, None)
        continue
        
      # The login is done
      # Send the message to all other clients
      if client_list[actual]:
        for one_connection in list_connections:
          if one_connection != s and one_connection != actual:
            one_connection.send("[{}]: {}".format(
              actual.getpeername()[0], data))
              
      # Prove the password
      # Incorrect - kick it
      else:
        data = data[:-1]
        if data == PASSWORD:
          STDOUT("Client {} correct loged in\n".format(actual.getpeername()[0]))
          FLOUT()
          actual.send("Correct login...\n")
          client_list[actual] = True
        else:
          STDOUT("Client {} bad log in\n".format(actual.getpeername()[0]))
          FLOUT()
          actual.send("Bad password\n")
          actual.close()
          list_connections.remove(actual)
          client_list.pop(actual, None)

# Close socket
s.close()

sys.exit(0)
