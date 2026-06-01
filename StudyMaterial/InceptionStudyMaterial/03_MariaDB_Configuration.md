# Inception — MariaDB Database Configuration

This document explains the configuration of the MariaDB database service, detailing its [Dockerfile](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/mariadb/Dockerfile) and initialization script [docker_entry.sh](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/mariadb/tools/docker_entry.sh).

---

## 1. MariaDB Dockerfile (`mariadb/Dockerfile`)

```dockerfile
FROM debian:bookworm

RUN apt update && apt install -y \
    mariadb-server \
    mariadb-client && \
    rm -rf /var/lib/apt/lists/*
```
* **What it is for:** Installs the MariaDB server and client utilities on a Debian base image.

```dockerfile
RUN mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld && \
    chmod 755 /var/run/mysqld
```
* **What it is for:** Prepares the system directory for MariaDB's runtime socket.
* **Why it is needed:** MariaDB uses this socket file to process local communication. The folder must be owned by the `mysql` user, otherwise the database server cannot write to it and will fail to start.

```dockerfile
RUN sed -i 's/bind-address.*=.*/bind-address = 0.0.0.0/' \
    /etc/mysql/mariadb.conf.d/50-server.cnf
```
* **What it is for:** Configures MariaDB's network listener configuration.
* **Why it is needed:** By default, MariaDB only listens on localhost (`127.0.0.1`), blocking external connections.
* **How it works:** Replaces the bind address with `0.0.0.0` (all network interfaces). This allows WordPress (on a different container/IP) to connect to MariaDB over the private bridge network.

```dockerfile
COPY ./tools/docker_entry.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/docker_entry.sh

EXPOSE 3306
CMD ["docker_entry.sh"]
```
* **What it is for:** Binds and executes the startup script on container boot, exposing default MariaDB port `3306`.

---

## 2. MariaDB Entrypoint Script (`mariadb/tools/docker_entry.sh`)

This script handles database initialization and starting the server.

```bash
#!/bin/bash
set -e

chown -R mysql:mysql /var/lib/mysql
```
* **`chown -R mysql:mysql /var/lib/mysql`**: Ensures that the mounted database volume has the correct file permission ownership.

### Creating System Tables
```bash
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi
```
* **What it is for:** Installs the core system tables.
* **Why it is needed:** If a fresh volume is mounted, it contains no system tables.
* **How it works:** Checks if the system database folder `/var/lib/mysql/mysql` exists. If missing, runs `mysql_install_db` to build default system schemas.

### Database Bootstrap (First Run SQL Configuration)
```bash
if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then
    echo "First run: creating database and users..."
    
    mysqld_safe --skip-networking &
    pid="$!"
```
* **What it is for:** Starts a temporary database instance.
* **Why it is needed:** We need to execute SQL commands to configure databases, users, and passwords, but we cannot run standard SQL scripts unless a database server is running.
* **How it works:** Starts a temporary server using `mysqld_safe` with `--skip-networking` (to prevent external access during configuration). The `&` symbol pushes the execution to the background, and `pid="$!"` captures its process ID.

```bash
    until mysqladmin ping >/dev/null 2>&1; do
        sleep 1
    done
```
* **What it is for:** Blocks the script execution until the database starts.
* **Why it is needed:** Prevents execution of SQL commands before the server is ready.
* **How it works:** Loops, running `mysqladmin ping` every second. Discards error messages (`>/dev/null 2>&1`) and exits the loop when the server returns a successful ping response.

```bash
    mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
    mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
    mysql -u root -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
    mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
    mysql -u root -e "FLUSH PRIVILEGES;"
```
* **What it is for:** Executes SQL commands using variables injected from the `.env` file.
* **How it works:**
  1. Creates the WordPress database schema.
  2. Creates the application user (`$MYSQL_USER`) for any connection host (`'%'`).
  3. Grants privileges on the database to this user.
  4. Changes the database root user password.
  5. Runs `FLUSH PRIVILEGES` to reload user privileges in memory.

```bash
    echo "Database setup complete!"
    mysqladmin -u root --password="${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$pid"
fi
```
* **What it is for:** Shuts down the temporary instance.
* **Why it is needed:** Restarts the server normally to apply networking.
* **How it works:** Issues a shutdown command with the new root password and waits (`wait "$pid"`) for the background process to exit.

### Starting Main Database Server
```bash
echo "Starting MariaDB..."
exec mysqld --user=mysql --datadir=/var/lib/mysql
```
* **What it is for:** Starts the database server in the foreground.
* **How it works:** Uses `exec` to start the database server as PID 1, keeping the container alive and ready to process database queries from WordPress.

---

## Next Steps

Now let's examine the application server: **WordPress**.

👉 Proceed to [04_WordPress_Configuration.md](./04_WordPress_Configuration.md)
