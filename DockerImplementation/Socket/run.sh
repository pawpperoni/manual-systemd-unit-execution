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
if [ -d bin ]
  then
    mkdir bin/
  fi

# Compile the C
echo "Compiling socket-activation..."
gcc -o bin/socket-activation src/socket-activation.c 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 1
  fi
echo "Done!"

# Copy the python
cp src/write-file.py bin/write-file.py

# Change the permissions
chmod +x bin/write-file.py

# Build Image
echo "Builind docker image"
docker build -t socket-activation . 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 2
  fi
echo "Done!"

docker rm msue-socket > /dev/null 1> $OUT 2> $ERR
if [ $? -eq 0 ]
  then
    echo "Erased old docker!"
  fi

# Create the docker
docker run --name="msue-socket" --hostname="msue-socket" --detach socket-activation 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 3
  fi
echo "Done!"

exit 0
