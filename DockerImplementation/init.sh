#! /bin/bash

# Start all the resources
# Usage: init.sh [-p|--path] [-s|--socket] [-t|--timer]
# Usage: init.sh -h|--help

# Help function
function show_help () {
  
  # Error
  if [ $1 -ne 0 ]
  then
    echo "Try 'init.sh --help' for more information\n" > /dev/stderr
  else
    # Show usage
    echo "Usage: init.sh [-p|--path] [-s|--socket] [-t|--time]"
    echo "Usage: init.sh -h|--help"
    
    # Show function
    echo "Start up resources"
    echo -e "\n\
  -h, --help          Show this help and exits\n\
  -p, --path PATH     Starts the path Unit\n\
  -s, --socket        Starts the socket Unit\n\
  -t, --time          Starts the timer Unit"
  fi
  
  exit $1
  
}

path=1
socket=1
timer=1

# Parse arguments
while [ $# -ge 1 ]
  do
    case $1 in
      "-h"|"--help")
        show_help 0
        ;;
      "-p"|"--path")
        path=0
        path_directory=$2
        shift
        ;;
      "-s"|"--socket")
        socket=0
        ;;
      "-t"|"--timer")
        timer=0
        ;;
      *)
        echo "init.sh: unknown option: '$1'" > /dev/stderr
        show_help 1
    esac
    shift
  done

# Start path
if [ $path -eq 0 ]
  then
    echo "Starting path with $path_directory"
  fi

# Start socket
if [ $socket -eq 0 ]
  then
    echo "Starting socket"
  fi
  
# Start timer
if [ $timer -eq 0 ]
  then
    echo "Starting timer"
  fi
  
# Let a bash active
/bin/bash
