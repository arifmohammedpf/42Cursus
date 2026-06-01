# Inception — WordPress & PHP-FPM Configuration

This document explains the configuration of the WordPress application server, detailing its [Dockerfile](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/wordpress/Dockerfile) and initialization script [entrypoint.sh](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/wordpress/tools/entrypoint.sh).

---

## 1. WordPress Dockerfile (`wordpress/Dockerfile`)

```dockerfile
FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php-fpm \
    php-mysqli \
    php-redis \
    mariadb-client \
    wget \
    && rm -rf /var/lib/apt/lists/*
```
* **What it is for:** Installs packages needed to run WordPress.
* **Why it is needed:**
  * `php-fpm`: FastCGI process manager to run PHP scripts.
  * `php-mysqli`: Driver allowing PHP to talk to MariaDB.
  * `php-redis`: PHP extension to connect to Redis.
  * `mariadb-client`: Provides `mysqladmin` to query database readiness.
  * `wget`: Used to download WordPress installation files.

```dockerfile
RUN sed -i 's/listen = \/run\/php\/php8.2-fpm.sock/listen = 9000/g' /etc/php/8.2/fpm/pool.d/www.conf
```
* **What it is for:** Reconfigures PHP-FPM's connection socket.
* **Why it is needed:** By default, PHP-FPM listens on a local Unix socket (`.sock` file) inside its local file system. Since NGINX runs in a separate container on a separate IP address, it cannot access this file.
* **How it works:** Replaces the socket path configuration with port `9000`. This instructs PHP-FPM to listen for incoming FastCGI connections on TCP port `9000` from any host.

```dockerfile
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp \
    && chmod +x /usr/local/bin/wp
```
* **What it is for:** Installs the WordPress Command Line Interface (**WP-CLI**).
* **Why it is needed:** Allows automating WordPress configuration via shell scripts instead of using a web interface.

```dockerfile
RUN mkdir -p /run/php
WORKDIR /var/www/html
EXPOSE 9000
ENTRYPOINT ["entrypoint.sh"]
```
* **What it is for:** Creates PHP runtime folders, sets workspace directory, and binds the startup script.

---

## 2. WordPress Startup Script (`wordpress/tools/entrypoint.sh`)

This script handles database connection checks, downloading WordPress, generating configs, and installing plugins.

```bash
#!/usr/bin/env bash
set -e

cd /var/www/html
```
* **`cd /var/www/html`**: Shifts the current working directory to the mounted `wp-volume` directory.

### MariaDB Readiness Loop
```bash
echo "Waiting for MariaDB..."
until mysqladmin -h mariadb -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" ping --silent; do
    sleep 2
done
echo "MariaDB is ready!"
```
* **What it is for:** Waits for the database server to be ready.
* **Why it is needed:** Docker Compose starts container structures concurrently. If WordPress tries to configure itself before MariaDB has finished initializing, it will crash.
* **How it works:** Loops, running `mysqladmin ping` against the `mariadb` host over the network. Blocks execution and sleeps 2 seconds until a success response is returned.

### Downloading WordPress Core
```bash
if [ ! -f ./wp-includes/version.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root
fi
```
* **What it is for:** Downloads WordPress core source files.
* **How it works:** Checks if `wp-includes/version.php` exists. If missing, runs WP-CLI to download files.

### Configuration Generation
```bash
if [ ! -f ./wp-config.php ]; then
    echo "Creating wp-config.php..."
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="mariadb"
```
* **What it is for:** Generates the `wp-config.php` database connection configuration.
* **How it works:** Runs WP-CLI to build `wp-config.php`, injecting credentials from environment variables and setting the database host to `mariadb`.

```bash
    # Redis configuration 
    echo "Adding Redis configuration..."
    sed -i "/require_once ABSPATH . 'wp-settings.php';/i \\
    define('WP_REDIS_HOST', 'redis');\\
    define('WP_REDIS_PORT', 6379);\\
    define('WP_CACHE', true);\\
    " ./wp-config.php
fi
```
* **What it is for:** Injects Redis connection parameters.
* **How it works:** Uses `sed` to insert three PHP lines right before the final line in `wp-config.php`:
  * `WP_REDIS_HOST`: Sets the Redis cache host to the container named `redis`.
  * `WP_REDIS_PORT`: Port `6379`.
  * `WP_CACHE`: Tells WordPress to enable object caching.

### Site Installation & Users Creation
```bash
if ! wp core is-installed --allow-root; then
    echo "Installing WordPress..."
    wp core install --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_SITE_TITLE}" \
        --admin_user="${WP_ADMIN}" \
        --admin_password="${WP_ADMIN_PASS}" \
        --admin_email="${WP_ADMIN_EMAIL}"
    
    wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASS}" \
        --allow-root
fi
```
* **What it is for:** Sets up database tables, admin credentials, and creates an additional author user.
* **Why it is needed:** Automates site configuration without manual input.
* **How it works:** Checks if WordPress is installed. If not, runs WP-CLI `core install` to build tables and configure the admin account, then creates the secondary user (`$WP_USER`) with the author role.

### Redis Object Cache Integration
```bash
if ! wp plugin is-installed redis-cache --allow-root; then
    echo "Installing Redis Object Cache plugin..."
    wp plugin install redis-cache --allow-root
fi

if ! wp plugin is-active redis-cache --allow-root; then
    echo "Activating Redis Object Cache plugin..."
    wp plugin activate redis-cache --allow-root
fi

echo "Enabling Redis object cache..."
wp redis enable --allow-root || true
```
* **What it is for:** Configures the Redis cache plugin.
* **How it works:**
  1. Installs the `redis-cache` plugin.
  2. Activates the plugin.
  3. Runs `wp redis enable` to write the cached files to `/var/www/html/wp-content/object-cache.php`. If this command fails (e.g. if Redis isn't fully ready yet), the `|| true` prevents the script from aborting.

### Starting PHP-FPM
```bash
echo "Starting PHP-FPM..."
exec php-fpm8.2 -F
```
* **What it is for:** Starts the PHP FastCGI manager in the foreground.
* **How it works:** `-F` runs the process in the foreground, keeping the container active and ready to handle requests from NGINX.

---

## Next Steps

Now let's examine the bonus cache service: **Redis**.

👉 Proceed to [05_Redis_Configuration_Bonus.md](./05_Redis_Configuration_Bonus.md)
