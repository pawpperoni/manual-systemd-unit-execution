# Path-based activation
# Bruno Mondelo Giaramita
# # 2017-05-17 Escola Del Treball

FROM fedora
MAINTAINER "Bruno Mondelo Giaramita"

# Install ps
RUN dnf install -y procps; exit 0

# Copy binaries
COPY bin /usr/sbin

# Create a directory to control
RUN mkdir /etc/msue

# The entry point of the docker
#ENTRYPOINT ["/bin/bash"]
ENTRYPOINT ["/sbin/path-activation", "--atime", "--mtime", "--ctime", "--file", "/etc/msue", "/usr/bin/python3", "/sbin/write-file.py"]
