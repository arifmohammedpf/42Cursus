#!/bin/bash
set -e

chown -R mysql:mysql /var/lib/mysql

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi

if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then
    echo "First run: creating database and users..."
    
    mysqld_safe --skip-networking &
    pid="$!"
    
    until mysqladmin ping >/dev/null 2>&1; do
        sleep 1
    done

    mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
    mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
    mysql -u root -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
    mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
    mysql -u root -e "FLUSH PRIVILEGES;"
    
    echo "Database setup complete!"
    mysqladmin -u root --password="${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$pid"
fi

echo "Starting MariaDB..."
exec mysqld --user=mysql --datadir=/var/lib/mysql