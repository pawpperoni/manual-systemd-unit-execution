#! /usr/bin/python
# -*- coding: utf-8 -*-

# echo-server.py - A echo TCP server
# Bruno Mondelo Giaramita
# 2017-05-10 Escola Del Treball

import sys
import socket
import datetime
import select
import signal

################################################################

def sigterm_handler (signum, frame):
  
  """
  SIGTERM signal handler
  Input: int
  Output: None
  """
  
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
PORT = 4111

# Create the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket
s.bind((HOST, PORT))

# Listen
s.listen(1)

# List desctriptor of connections
list_connections = [s]

while True:
  # Stay in select
  alive, x, y = select.select(list_connections, [], [])
  # Process select
  for actual in alive:
    # New connection
    if actual == s:
      conn, addrs = actual.accept()
      list_connections.append(conn)
      STDOUT("Added new client with IP: {}\n".format(addrs[0]))
    # Changed status
    else:
      message = actual.recv(1024)
      # Close connection
      if not message:
        STDERR("[{}]: [BYEBYE]: Closed host: {}\n".format(
          str(datetime.datetime.now()), actual.getpeername()[0]))
        FLERR()
        actual.close()
        list_connections.remove(actual)
      else:
        # Echo back
        STDOUT("[{}]: {}".format(actual.getpeername()[0], message))
        FLOUT()
        actual.send(message)

# Close socket
s.close()

sys.exit(0)

