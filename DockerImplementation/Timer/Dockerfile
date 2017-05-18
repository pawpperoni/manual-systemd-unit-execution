# Timer-based activation
# Bruno Mondelo Giaramita
# # 2017-05-18 Escola Del Treball

FROM fedora
MAINTAINER "Bruno Mondelo Giaramita"

# Install crontab
RUN dnf install -y cronie; exit 0

# Copy files
COPY bin /opt
# Copy crontab configuration
RUN cp /opt/root /var/spool/cron
# Copy the binaries
RUN cp /opt/*py /usr/sbin/

# The entry point of the docker
ENTRYPOINT ["/usr/sbin/crond", "-x", "proc"]
