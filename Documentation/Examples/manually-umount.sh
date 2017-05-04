#! /bin/bash

# manually-umount.sh - Umounts a resource
# Bruno Mondelo Giaramita
# 2017-05-04 Escola Del Treball
# Usage: manually-umount.sh RESOURCE
# Usage: manually-umount.sh -h|--help

AUTHOURS="\
  Bruno Mondelo"

# The program name
PROGRAM_NAME="manually-umount.sh"

# Good exit
EXIT_OK=0

# Unknown argument
EXIT_BAD_ARGUMENT=147

# Bad number of arguments
EXIT_BAD_NUMBER_ARGUMENTS=148

# Bad umount
EXIT_BAD_UMOUNT=1

# Help function
function show_help {
  
  # This function shows the help message
  # Input: int
  #         0 - full help
  #         1 - simple help
  # Output: None
  
  # Shows simple or full help
  if [ $1 -eq 1 ]
    then
      echo "Try '$PROGRAM_NAME --help' for more information" > /dev/stderr
  elif [ $1 -eq 0 ]
    then
      echo -e "Usage: $PROGRAM_NAME RESOURCE\n\
Umounts a resource\n\
\n\
Options:\n\
  -h, --help        Shows this help and exits\n\
\n\
Examples:\n\
  $PROGRAM_NAME /mnt\n"
    fi
    
}

# Check argument length
if [ $# -gt 1 ] || [ $# -lt 1 ]
  then
    echo "$PROGRAM_NAME: Bad usage" > /dev/stderr
    show_help 1
    exit $EXIT_BAD_NUMBER_ARGUMENTS
  fi

# Parse arguments
# Not valid options
# Help message
# If not process with umount
if [ $1 = "-h" ] || [ $1 = "--help" ]
  then
    show_help 0
    exit $EXIT_OK
elif [[ $1 == -* ]]
  then
    echo "$PROGRAM_NAME: Unknown option $1" > /dev/stderr
    show_help 1
    exit $EXIT_BAD_ARGUMENT
  fi

RESOURCE=$1

# Umount the resource
umount $RESOURCE

# Any error will lead to an exit error
if [ $? -ne 0 ]
  then
    echo "$PROGRAM_NAME: Bad umount" > /dev/stderr
    exit $EXIT_BAD_UMOUNT
  fi
  
exit $EXIT_OK


  

