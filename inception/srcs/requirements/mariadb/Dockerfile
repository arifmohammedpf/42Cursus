FROM debian:bookworm

RUN apt update && apt install -y \
    mariadb-server \
    mariadb-client && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld && \
    chmod 755 /var/run/mysqld

# Allow remote connections to MariaDB before build rather than at runtime
RUN sed -i 's/bind-address.*=.*/bind-address = 0.0.0.0/' \
    /etc/mysql/mariadb.conf.d/50-server.cnf

COPY ./tools/docker_entry.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/docker_entry.sh

EXPOSE 3306

CMD ["docker_entry.sh"]