# Socket-based activation
# Bruno Mondelo Giaramita
# # 2017-05-17 Escola Del Treball

FROM fedora
MAINTAINER "Bruno Mondelo Giaramita"

# Install ps
RUN dnf install -y procps; exit 0

# Copy binaries
COPY bin /usr/sbin

# The entry point of the docker
#ENTRYPOINT ["/bin/bash"]
ENTRYPOINT /sbin/socket-activation /usr/bin/python3 /sbin/write-file.py
