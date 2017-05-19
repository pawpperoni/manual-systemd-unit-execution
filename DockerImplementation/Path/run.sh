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

# Compile the C
echo "Compiling path-activation..."
gcc -o bin/path-activation src/path-activation.c 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 1
  fi
echo "Done!"

# Copy the python
cp src/*.py bin/

# Change the permissions
chmod +x bin/*.py

# Build Image
echo "Builind docker image"
docker build -t path-activation . 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 2
  fi
echo "Done!"

docker rm msue-path > /dev/null 1> $OUT 2> $ERR
if [ $? -eq 0 ]
  then
    echo "Erased old docker!"
  fi

# Create the docker
docker run --name="msue-path" --hostname="msue-path" --detach path-activation 1> $OUT 2> $ERR
if [ $? -ne 0 ]
  then
    echo "Error..."
    exit 3
  fi
echo "Done!"

exit 0

