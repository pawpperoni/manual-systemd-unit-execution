# Timer-based activation
# Bruno Mondelo Giaramita
# # 2017-05-18 Escola Del Treball

FROM fedora
MAINTAINER "Bruno Mondelo Giaramita"

# Install ps
RUN dnf install -y cronid; exit 0

# The entry point of the docker
#ENTRYPOINT ["/bin/bash"]
ENTRYPOINT /sbin/socket-activation /usr/bin/python3 /sbin/write-file.py
