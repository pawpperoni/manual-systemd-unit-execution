#! /bin/sh

# Compile the C
gcc -o bin/socket-activation src/socket-activation.c

# Copy the python
cp src/write-file.py bin/write-file.py

# Change the permissions
chmod +x bin/write-file.py

# Build Image
docker build -t socket-activation .

docker rm msue-socket
# Create the docker
docker run --name="msue-socket" --hostname="msue-socket" --detach socket-activation
