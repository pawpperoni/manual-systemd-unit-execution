#! /bin/sh

OUT="/dev/null"
ERR="/dev/null"

# Check verbose argument
if [ $# -gt 0 ]
  then
    if [ $1 = "-v" ] || [ $1 = "--verbose" ]
      then
        OUT="/dev/stdout"
        ERR="/dev/stderr"
      fi
  fi

# Create binaries directory
if [ ! -d bin ]
  then
    mkdir bin/
    echo "Created binaries directory"
  fi

# Copy all the source
cp src/* bin

# Change the permissions of python files
chmod +x bin/*.py

# Build Image
echo "Builind docker image"
docker build -t timer-activation . 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 2
  fi
echo "Done!"

docker stop msue-timer 1> $OUT 2> $ERR

docker rm msue-timer > /dev/null 1> $OUT 2> $ERR
if [ $? -eq 0 ]
  then
    echo "Erased old docker!"
  fi

# Create the docker
docker run --name="msue-timer" --hostname="msue-timer" --detach timer-activation 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 3
  fi
echo "Done!"

exit 0

