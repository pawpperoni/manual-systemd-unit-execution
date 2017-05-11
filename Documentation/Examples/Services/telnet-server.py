#! /usr/bin/python
# -*- coding: utf-8 -*-

# telnet-server.py - A simple Telnet Server
# Bruno Mondelo Giaramita
# 2017-05-11 Escola Del Treball

import sys
import socket
import datetime
import select
import signal
import os
from subprocess import Popen, PIPE

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

# PID file
PID_FILE = "/var/run/telnet-server.pid"

# Output variables
STDOUT = sys.stdout.write
FLOUT = sys.stdout.flush
STDERR = sys.stderr.write
FLERR = sys.stderr.flush

# Socket information
HOST = ""
PORT = 4172

# Character meaning the STX
START_CHARACTER = '\2'  # ASCII 4 STX

# Character meaning the ETX
END_CHARACTER = '\3'  # ASCII 4 ETX

# Character meaning the EOT
END_TRANSMISSION = '\4'  # ASCII 4 EOT

# Client information
client_list =  {}
"""
The form of the dictionary:
  Key: Connection
  Value: Dictionary:
         order(str): str
         outfd(str): file descriptor  Popen out descriptor
         errfd(str): file descriptor  Popen err descriptor
"""

# Fork, kill parent
program_id = os.fork()

if (program_id != 0):
  
  father_status = 0
  
  STDOUT("Forked child with PID: {}\n".format(program_id))
  FLOUT()
  
  # Write PID
  try:
    ff = open(PID_FILE, "w")
    ff.write(str(program_id))
    ff.close()
  except IOError as e:
    STDERR("Canno't write PID into {}: {} - {}\n".format(PID_FILE,
      e.errno, e.strerror))
    FLOUT()
    father_status = 1
    
  sys.exit(father_status)

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
      client_list[conn] = {
        "order": "",
        "outfd": None,
        "errfd": None
      }
      
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
      
      # Check if reading Popen, if not concat the order
      if client_list[actual]["outfd"]:        
        order_line = client_list[actual]["outfd"].readline()
        client_list[actual]["outfd"].flush()
        if order_line:
          actual.sendall(order_line)
        else:
          client_list[actual]["outfd"] = None
          # ETX
          actual.sendall(END_CHARACTER)
      elif client_list[actual]["errfd"]:
        order_line = client_list[actual]["errfd"].readline()
        client_list[actual]["errfd"].flush()
        if order_line:
          actual.sendall(order_line)
        else:
          client_list[actual]["errfd"] = None
          # STDERR is the last, EOT
          actual.sendall(END_TRANSMISSION)
      else:
        # Concat data if it's not end
        if not END_TRANSMISSION in data:
          client_list[actual]["order"] += data
          continue
        client_list[actual]["order"] += data[:-1]
        # Open POPEN
        try:
          pipe_data = Popen((client_list[actual]["order"]).split(),
              stdout=PIPE, stderr=PIPE)
          STDOUT("Client: {} Order: {}\n".format(actual.getpeername()[0],
            client_list[actual]["order"]))
          FLOUT()
        except:
          STDERR("Error processing order: {} from: {}\n".format(
            client_list[actual]["order"], actual.getpeername()[0]))
          FLERR()
          actual.sendall("Bad order!\n" + END_TRANSMISSION)
          continue
        finally:
          # Free data
          client_list[actual]["order"] = ""
        # Assign fluxes
        client_list[actual]["outfd"] = pipe_data.stdout
        client_list[actual]["errfd"] = pipe_data.stderr
        # Send start
        actual.sendall(START_CHARACTER)

# Close socket
s.close()

sys.exit(0)


