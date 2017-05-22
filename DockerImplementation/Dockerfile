# Path, Timer, Socker activation
# Bruno Mondelo Giaramita
# 2017-05-22 Escola Del Treball

FROM fedora
MAINTAINER "Bruno Mondelo Giaramita"

# Install ps, crond
RUN dnf install -y procps cronie; exit 0

# Copy binaries
COPY DockerImplementation/*/bin /usr/sbin

# Create a directory to control for path activation
RUN mkdir /etc/msue

# The entry point of the docker
#ENTRYPOINT ["/bin/bash"]
