#! /bin/bash

# manually-mount.sh - Mounts a resource into the specified destination
# Bruno Mondelo Giaramita
# 2017-05-04 Escola Del Treball
# Usage: manually-mount.sh -s|--source DEVICE -d|--destination DIRECTORY [-f|--file-system FILESYSTEM] [-o|--options OPTIONS]
# Usage: manually-mount-sh -h|--help

AUTHOURS="\
  Bruno Mondelo"

PROGRAM_NAME="manually-mount.sh"

# Good exit
EXIT_OK=0

# Unknown argument
EXIT_BAD_ARGUMENT=147

# Missing required argument
EXIT_REQUIRED_ARGUMENT=150

# Error mounting
EXIT_BAD_MOUNT=1

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
      echo -e "Usage: $PROGRAM_NAME -s|--source DEVICE -d|--destination DIRECTORY [-f|--file-system FILESYSTEM] [-o|--options OPTIONS]\n\
Mounts a resource to the specified destination\n\
\n\
Options:\n\
  -d, --destination <directory>   The destination directory\n\
  -f, --file-system <filesystem>  The filesystem of the resource as specified in '/etc/filesystems'\n\
  -h, --help                      Shows this help and exits\n\
  -o, --options <options>         The mount options, see man mount(8) to the defined options\n\
  -s, --source <device>           The device to be mounted\n\
\n\
Examples:\n\
  $PROGRAM_NAME -s /dev/sdb2 -d /mnt\n\
  $PROGRAM_NAME -s /dev/sdc5 -d /mnt/ext-device -o rw,users -f ext2"
    fi
    
}

# Parse arguments
while [ $# -gt 0 ]
  do
    case $1 in
      -d|--destination)
        DESTINATION="$2"
        shift
        ;;
      -f|--file-system)
        OPTIONS="$OPTIONS -t \"$2\""
        shift
        ;;
      -h|--help)
        show_help 0
        exit $EXIT_OK
        ;;
      -o|--options)
        OPTIONS="$OPTIONS -o \"$2\""
        shift
        ;;
      -s|--source)
        SOURCE="$2"
        shift
        ;;
      *)
        echo "$PROGRAM_NAME: invalid option -- '$1'" > /dev/stderr
        show_help 1
        exit $EXIT_BAD_ARGUMENT
        ;;
    esac
    shift
  done

# Check required arguments
if [ -z $DESTINATION ] || [ -z $SOURCE ]
  then
    echo "$PROGRAM_NAME: Missing argument" > /dev/stderr
    show_help 1
    exit $EXIT_REQUIRED_ARGUMENT
  fi

# Mount the resource
mount$OPTIONS $SOURCE $DESTINATION

# Any error will lead to an exit error
if [ $? -ne 0 ]
  then
    echo "$PROGRAM_NAME: Bad mount" > /dev/stderr
    exit $EXIT_BAD_MOUNT
  fi

# No news good news
exit $EXIT_OK
