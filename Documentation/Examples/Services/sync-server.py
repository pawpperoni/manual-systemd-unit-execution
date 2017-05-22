#! /usr/bin/python
# -*- coding: utf-8 -*-

# sync-server.py - A synchronization server
# Bruno Mondelo Giaramita
# 2017-05-15 Escola Del Treball

import sys
import os
import hashlib
import time
import re

################################################################

def get_all_dirs (directory):

  """
  Recursive function to get all directories
  Input: str
  Output: Iterator
  """
  
  # Iterate all the file directory
  # Yield all files
  # Call this function for directories
  for root, dirs, files in os.walk(directory):
    for dir_name in dirs:
      yield root, dir_name

def get_all_files (directory):
  
  """
  Recursive function to get all files
  Input: str
  Output: Iterator
  """
  
  # Iterate all the file directory
  # Yield all files
  # Call this function for directories
  for root, dirs, files in os.walk(directory):
    for file_name in files:
      yield root, file_name

def digest_file (filename):
  
  """
  Digest the filename into MD5
  Input: str
  Output: str
  """
  
  # Create the hash
  hash_md5 = hashlib.md5()
    
  # Open file and get the hash
  with open(filename, "rb") as ff:
    for chunk in iter(lambda: ff.read(4096), b""):
      hash_md5.update(chunk)
  
  # Return the has digest
  return hash_md5.hexdigest()

def charge_file (file_flux, dictionary):
  
  """
  Charge file and hash in dictionary
  Input: File stream, dictionary
  Output: None
  """
  
  line = 1
  
  for one_line in file_flux:
    info_file = one_line.split()
    try:
      dictionary[info_file[0]] = info_file[1]
    except:
      STDERR("Bad configuration in line: {} - '{}'\n".format(str(line), one_line))
      FLERR()
    line += 1

################################################################

print "Hello! executing syn-server.py!"
print "Sleep of 50 seconds"

i = 0

while i < 20:
    time.sleep(1)
    sys.stdout.write(".")
    sys.stdout.flush()
    i += 1

sys.stdout.write("\n")

# Output variables
STDOUT = sys.stdout.write
FLOUT = sys.stdout.flush
STDERR = sys.stderr.write
FLERR = sys.stderr.flush

# Directory to read new files
SYNC_DIR = "/etc/sync-folder"

# File containing the hash of the files
# The daemon will check for the files hash and will know
# if they changed
HASH_FILE = "/etc/sync-server.changes"

# Directory to send files
MASTER_DIRECTORY = "/etc/recv-folder"

# The dictionary with old hashes
file_hashes = {}

# Open file with old MD5
try:
  ff = open(HASH_FILE, "r")
  charge_file(ff, file_hashes)
  ff.close()
except:
  STDERR("Hash file: {} doesn't exists, creating a new one\n".format(HASH_FILE))
  FLERR()

hash_descriptor = open(HASH_FILE, "w")

# Create directories
for one_dir in get_all_dirs(SYNC_DIR):
  # Get relative root
  rel_regex = re.search("{}/(.*)".format(SYNC_DIR), one_dir[0])
  if rel_regex:
    new_dir = "{}/{}/{}".format(MASTER_DIRECTORY, rel_regex.group(1), one_dir[1])
  else:
    new_dir = "{}/{}".format(MASTER_DIRECTORY, one_dir[1])
  try:
    os.mkdir(new_dir)
    STDOUT("Created dir: {}\n".format(new_dir))
  except OSError as e:
    STDERR("Error creating dir '{}': {}\n".format(new_dir, str(e)))

# Compare file hash with old one
# No existing file o changed hash sync file
for one_file in get_all_files(SYNC_DIR):
  # Get relative root
  rel_regex = re.search("{}/(.*)".format(SYNC_DIR), one_file[0])
  if rel_regex:
    newname = "{}/{}/{}".format(MASTER_DIRECTORY, rel_regex.group(1), one_file[1])
  else:
    newname = "{}/{}".format(MASTER_DIRECTORY, one_file[1])
  filename = "{}/{}".format(one_file[0], one_file[1])
  if filename not in file_hashes or file_hashes[filename] != digest_file(filename):
    STDOUT("Synchronizing file: {}\n".format(filename))
    FLOUT()
    
    # Open old file
    try:
      ff = open(filename, "r")
    except:
      STDOUT("Canno't open file: '{}'\n".format(filename))
      FLERR()
      continue
      
    # Open new file
    try:
      oo = open(newname, "w")
    except:
      STDOUT("Canno't open file: '{}'\n".format(newname))
      FLERR()
      continue
    
    # Write all file  
    for one_line in ff:
      oo.write(one_line)
      
    oo.close()
    ff.close()
  
  # Write the new filename
  hash_descriptor.write("{} {}\n".format(filename, digest_file(filename)))

hash_descriptor.close()

sys.exit()
    
      
