# Inception Project - Complete Explanation

---

## Table of Contents
1. [MariaDB Dockerfile](#mariadb-dockerfile)
2. [MariaDB entrypoint.sh](#mariadb-entrypointsh)
3. [WordPress Dockerfile](#wordpress-dockerfile)
4. [WordPress entrypoint.sh](#wordpress-entrypointsh)
5. [Nginx Dockerfile](#nginx-dockerfile)
6. [Nginx inception.conf](#nginx-inceptionconf)
7. [Nginx entrypoint.sh](#nginx-entrypointsh)
8. [Redis Dockerfile](#redis-dockerfile)
9. [Redis redis.conf](#redis-redisconf)
10. [Makefile](#makefile)
11. [docker-compose.yml](#docker-composeyml)
12. [Volumes Explained](#volumes-explained)

---

## MariaDB Dockerfile

```dockerfile
FROM debian:bookworm
```
- Uses Debian Bookworm as the base image (blank canvas)

```dockerfile
RUN apt update && apt install -y \
    mariadb-server \
    mariadb-client && \
    rm -rf /var/lib/apt/lists/*
```
- `apt update` = refresh list of available software
- `apt install` = download and install software
- `mariadb-server` = the database engine
- `mariadb-client` = tools to talk to the database
- `-y` = automatically say yes to prompts
- `rm -rf /var/lib/apt/lists/*` = clean up leftover temp files to keep image small

```dockerfile
RUN mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld && \
    chmod 755 /var/run/mysqld
```
- `mkdir -p /var/run/mysqld` = create folder MariaDB needs for runtime files
  - `-p` = create parent folders too if missing, don't error if exists
- `chown -R mysql:mysql` = give ownership to mysql user:group
  - `mysql:mysql` format = `user:group`
  - `mysql` user is created automatically when MariaDB installs
- `chmod 755` = set permissions
  - Owner (mysql) = full access
  - Everyone else = read and execute only

> **Why create this folder manually?**
> In Docker, `/var/run` gets wiped on every restart. MariaDB needs this folder
> for its socket file (`mysqld.sock`) — the communication channel between programs.
> If it's missing → MariaDB crashes.

```dockerfile
RUN sed -i 's/bind-address.*=.*/bind-address = 0.0.0.0/' \
    /etc/mysql/mariadb.conf.d/50-server.cnf
```
- `sed` = find and replace tool
- Changes `bind-address` from `127.0.0.1` (localhost only) to `0.0.0.0` (everywhere)
- Without this → WordPress container cannot connect to MariaDB
- Done at BUILD time so it's baked in, not done at runtime

```dockerfile
COPY ./tools/docker_entry.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/docker_entry.sh
EXPOSE 3306
CMD ["docker_entry.sh"]
```
- Copy startup script into container and make it executable
- `EXPOSE 3306` = MariaDB's standard port
- `CMD` = run this script when container starts

---

## MariaDB entrypoint.sh

```bash
chown -R mysql:mysql /var/lib/mysql
```
- Fix ownership of data folder every time container starts
- `/var/lib/mysql` = where actual database data is stored

```bash
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql
fi
```
- Check if MariaDB system database exists
- `! -d` = if this folder does NOT exist
- `mysql_install_db` = one-time setup tool that comes with MariaDB
  - Creates core system tables MariaDB needs to function
  - Like a "first time setup wizard"

```bash
if [ ! -d "/var/lib/mysql/${MYSQL_DATABASE}" ]; then
    mysqld_safe --skip-networking &
    pid="$!"
```
- Check if our custom database exists
- If not → first run → start MariaDB temporarily in background
- `--skip-networking` = no outside connections yet
- `&` = run in background
- `pid="$!"` = save the process ID (like a ticket number)

```bash
    until mysqladmin ping >/dev/null 2>&1; do
        sleep 1
    done
```
- Wait until MariaDB is actually ready
- Tries every 1 second until it responds
- Like knocking on a door until someone answers

```bash
    mysql -u root -e "CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;"
    mysql -u root -e "CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';"
    mysql -u root -e "GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';"
    mysql -u root -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';"
    mysql -u root -e "FLUSH PRIVILEGES;"
```
- `CREATE DATABASE` = create our app's database
- `CREATE USER` = create a user for our app (`%` means from anywhere)
- `GRANT ALL PRIVILEGES` = give that user full access
- `ALTER USER root` = set root password
- `FLUSH PRIVILEGES` = save/apply all changes

```bash
    mysqladmin -u root --password="${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$pid"
fi
exec mysqld --user=mysql --datadir=/var/lib/mysql
```
- Shut down the temporary MariaDB
- `wait "$pid"` = wait until it FULLY stops before continuing
  - Without this → two MariaDB processes run at same time → crash
- `exec mysqld` = start MariaDB properly for real

### Flow
```
Container starts → Fix ownership → System DB missing? → Initialize
→ Our DB missing? → Start temp MariaDB → Create DB/users → Shutdown temp
→ Start real MariaDB ✅
```

---

## WordPress Dockerfile

```dockerfile
RUN apt-get install -y \
    php-fpm \
    php-mysqli \
    php-redis \
    mariadb-client \
    wget
```

| Package | Purpose |
|---------|---------|
| `php-fpm` | Runs PHP code (WordPress is written in PHP) |
| `php-mysqli` | Lets PHP talk to MariaDB |
| `php-redis` | Lets PHP talk to Redis |
| `mariadb-client` | Tools to connect to database |
| `wget` | Download files from internet |

```dockerfile
RUN sed -i 's/listen = \/run\/php\/php8.2-fpm.sock/listen = 9000/g' \
    /etc/php/8.2/fpm/pool.d/www.conf
```
- Changes PHP-FPM from socket file to port `9000`
- Nginx connects to PHP via network port (different containers)

```dockerfile
RUN wget https://raw.githubusercontent.com/.../wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp \
    && chmod +x /usr/local/bin/wp
```
- Download WP-CLI = command line tool for managing WordPress
- Allows installing WordPress, creating users, configuring — all from terminal

```dockerfile
WORKDIR /var/www/html
EXPOSE 9000
ENTRYPOINT ["entrypoint.sh"]
```
- `WORKDIR` = all commands run from this folder (where WordPress lives)
- `EXPOSE 9000` = PHP-FPM port
- `ENTRYPOINT` = harder to override than `CMD`

---

## WordPress entrypoint.sh

```bash
until mysqladmin -h mariadb -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" ping --silent; do
    sleep 2
done
```
- `-h mariadb` = connect to container named `mariadb` (`-h` = host)
- Wait until database is ready before doing anything
- Returns: success (exit 0) = stop waiting, fail (exit 1) = try again

```bash
if [ ! -f ./wp-includes/version.php ]; then
    wp core download --allow-root
fi
```
- Check if WordPress is already downloaded
- `version.php` = proof WordPress exists
- `--allow-root` = needed in Docker (running as root user)

```bash
if [ ! -f ./wp-config.php ]; then
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="mariadb"
```
- Creates `wp-config.php` = tells WordPress how to connect to database
- `--dbhost="mariadb"` = database is in container named `mariadb`

```bash
    sed -i "/require_once ABSPATH . 'wp-settings.php';/i \
    define('WP_REDIS_HOST', 'redis');\
    define('WP_REDIS_PORT', 6379);\
    define('WP_CACHE', true);\
    " ./wp-config.php
```
- Adds Redis settings into `wp-config.php`
- `WP_REDIS_HOST` = container named `redis`
- `WP_REDIS_PORT` = 6379
- `WP_CACHE` = enable caching

```bash
if ! wp core is-installed --allow-root; then
    wp core install --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_SITE_TITLE}" \
        --admin_user="${WP_ADMIN}" \
        --admin_password="${WP_ADMIN_PASS}" \
        --admin_email="${WP_ADMIN_EMAIL}"
fi
```
- Install WordPress if not already installed
- Creates admin account with environment variable values

```bash
wp plugin install redis-cache --allow-root
wp plugin activate redis-cache --allow-root
wp redis enable --allow-root || true
```
- Install Redis plugin (WordPress needs plugin to use Redis)
- Activate it (installing ≠ activating)
- Enable Redis caching (`|| true` = don't stop if fails)

```bash
exec php-fpm8.2 -F
```
- Start PHP-FPM in foreground
- `-F` = stay in foreground = keeps container alive
- Without `-F` → PHP goes to background → container shuts down

---

## Nginx Dockerfile

```dockerfile
RUN apt-get install -y nginx openssl
```
- `nginx` = web server
- `openssl` = tool to generate SSL certificates

```dockerfile
RUN rm -f /etc/nginx/sites-enabled/default
```
- Remove default Nginx config
- Would conflict with our custom config

```dockerfile
COPY ./conf/inception.conf /etc/nginx/conf.d/inception.conf
EXPOSE 443
ENTRYPOINT ["entrypoint.sh"]
```
- Copy our custom config
- Port `443` = HTTPS (port `80` = HTTP, `443` = HTTPS)

---

## Nginx inception.conf

```nginx
listen 443 ssl;
listen [::]:443 ssl;
```
- Listen on port 443 with SSL
- `[::]` = IPv6 format

```nginx
ssl_protocols TLSv1.2 TLSv1.3;
ssl_certificate /etc/nginx/ssl/inception.crt;
ssl_certificate_key /etc/nginx/ssl/inception.key;
```
- These are **Nginx config directives** (not CLI commands)
- `ssl_protocols` = only allow modern secure TLS versions
- `ssl_certificate` = public certificate (like an ID card)
- `ssl_certificate_key` = private key (used to encrypt/decrypt)

> **Note:** Port and HTTPS are different things!
> - `https://hello.com` = HTTPS on port 443 (default)
> - `https://hello.com:4242` = HTTPS on port 4242 (custom)
> - Our Nginx only listens on 443 → port 4242 would be refused

```nginx
location / {
    try_files $uri $uri/ /index.php?$args;
}
```
- Try exact file → try as folder → send to WordPress
- Makes WordPress "pretty URLs" work

```nginx
location ~ \.php$ {
    include snippets/fastcgi-php.conf;
    fastcgi_pass wordpress:9000;
}
```
- `~` = pattern matching
- `\.php$` = anything ending in `.php`
- `include` = paste contents of that file here (like #include in C)
- `fastcgi-php.conf` = pre-installed Nginx file with standard PHP settings
- **FastCGI** = protocol (translator) between Nginx and PHP
  - Nginx speaks HTTP, PHP speaks PHP, FastCGI translates between them
- `fastcgi_pass wordpress:9000` = send PHP to WordPress container

---

## Nginx entrypoint.sh

```bash
mkdir -p /etc/nginx/ssl

if [ ! -f /etc/nginx/ssl/inception.crt ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/inception.key \
        -out /etc/nginx/ssl/inception.crt \
        -subj "/C=$SSL_COUNTRY/ST=$SSL_STATE/L=$SSL_CITY/O=$SSL_ORG/OU=$SSL_UNIT/CN=$DOMAIN_NAME"
fi
```

| Part | Meaning |
|------|---------|
| `req -x509` | Create self-signed certificate |
| `-nodes` | No password on key (Nginx reads it automatically) |
| `-days 365` | Expires in 1 year |
| `-newkey rsa:2048` | Generate 2048-bit RSA key |
| `-subj` | Certificate owner info (pre-filled for Docker) |

**`-subj` fields:**
- `/C` = Country
- `/ST` = State
- `/L` = City
- `/O` = Organization
- `/OU` = Department
- `/CN` = Domain name (most important — must match your domain)

> `-subj` is NOT mandatory but required in Docker because nobody is
> there to answer the interactive questions manually.

**Two types of certificates:**
| Type | Signed by | Browser | Use |
|------|-----------|---------|-----|
| Official | Let's Encrypt etc. | ✅ Trusted | Real websites |
| Self-signed | Yourself | ⚠️ Warning | Dev/school projects |

```bash
exec nginx -g 'daemon off;'
```
- `daemon off` = stay in foreground = keeps container alive
- Same concept as PHP-FPM's `-F` flag

---

## Redis Dockerfile

```dockerfile
FROM alpine:3.22
```
- Uses Alpine Linux instead of Debian
- Alpine = only ~5MB vs Debian ~120MB
- Redis is simple → doesn't need full Debian

```dockerfile
RUN apk add --no-cache redis
```
- `apk` = Alpine's package manager (like `apt` in Debian)
- `--no-cache` = don't save package index (same as `rm -rf /var/lib/apt/lists/*`)

```dockerfile
CMD ["redis-server", "/etc/redis/redis.conf"]
```

**CMD vs ENTRYPOINT:**
| | CMD | ENTRYPOINT |
|--|-----|-----------|
| Override? | ✅ Easy | ❌ Hard |
| Purpose | Default command | Fixed command |

- Redis uses `CMD` = more flexible, easy to swap config for testing
- Could also use `ENTRYPOINT` or combine:
```dockerfile
ENTRYPOINT ["redis-server"]
CMD ["/etc/redis/redis.conf"]
```

> Redis has NO entrypoint script because it needs zero setup — just start with a config file.

---

## Redis redis.conf

```
bind 0.0.0.0
```
- Accept connections from anywhere (WordPress needs to reach Redis)

```
port 6379
```
- Redis default port (matches WordPress config and EXPOSE)

```
protected-mode no
```
- Disable protection mode (would require password)
- Safe to disable inside private Docker network

```
daemonize no
```
- Stay in foreground = keeps container alive
- All containers must have one foreground process:

| Container | Foreground process | How |
|-----------|-------------------|-----|
| MariaDB | `mysqld` | Default behavior |
| WordPress | `php-fpm8.2` | `-F` flag |
| Nginx | `nginx` | `daemon off` |
| Redis | `redis-server` | `daemonize no` |

```
maxmemory 256mb
maxmemory-policy allkeys-lru
```
- `maxmemory` = hard cap on RAM usage
- `allkeys-lru` = when full, delete Least Recently Used items first
  - LRU = items not used in longest time get deleted first

---

## Makefile

```makefile
NAME = inception
DATA_PATH = /home/arimoham/data
COMPOSE_FILE = ./srcs/docker-compose.yml
```
- Variables = shortcuts to avoid repeating long paths

| Command | What it does |
|---------|-------------|
| `make` / `make up` | Build and start everything |
| `make down` | Stop containers (keep data) |
| `make clean` | Stop + remove orphan containers |
| `make fclean` | Delete EVERYTHING (containers, images, volumes, data) |
| `make re` | Delete everything + rebuild from scratch |
| `make logs` | Watch live logs from all containers |

```makefile
up:
    @sudo mkdir -p $(DATA_PATH)
    @docker compose -f $(COMPOSE_FILE) up -d --build
```
- `@` = don't print the command
- `-d` = run in background (detached)
- `--build` = rebuild images before starting

```makefile
fclean: clean
    @docker volume rm -f srcs_db-volume srcs_wp-volume 2>/dev/null || true
    @docker system prune -af --volumes
    @sudo rm -rf $(DATA_PATH)/volumes/srcs_*
```
- `2>/dev/null` = hide error messages
- `|| true` = don't stop if volumes don't exist
- `docker system prune -af` = delete ALL unused Docker resources

```makefile
.PHONY: all up down clean fclean re logs
```
- Tells Make these are commands, not filenames
- Prevents conflicts if a file named `clean` exists

---

## docker-compose.yml

Defines all containers, how they connect, and what resources they share.

### Key settings explained

| Setting | Meaning |
|---------|---------|
| `build` | Build from this Dockerfile location |
| `container_name` | Name used by other containers to find it |
| `restart: always` | Auto-restart if container crashes |
| `env_file: .env` | Load passwords/settings from .env file |
| `depends_on` | Start this container after these ones |
| `ports: "443:443"` | Map host port → container port |

### Networks
```yaml
networks:
  inception:
    driver: bridge
```
- Private network for all containers
- Containers find each other by **container name**
- Only Nginx has `ports` → only Nginx talks to outside world

### Volumes
```yaml
volumes:
  db-volume:    # MariaDB data
  wp-volume:    # WordPress files (shared between WordPress + Nginx)
```

---

## Volumes Explained

### What does `wp-volume:/var/www/html` mean?

```yaml
volumes:
  - wp-volume:/var/www/html
```
- Connect volume `wp-volume` to folder `/var/www/html` inside container
- Think of it like a USB drive plugged into a port

### Why WordPress AND Nginx share wp-volume

```
WordPress writes files → /var/www/html
Nginx reads files      → /var/www/html (SAME volume = same files!)
```

Without shared volume → Nginx's `/var/www/html` would be empty → 404 errors

### Physical location with daemon.json

```json
{ "data-root": "/home/user/data" }
```

This tells Docker to store everything in `/home/user/data` instead of `/var/lib/docker`

| | Default | With daemon.json |
|--|---------|-----------------|
| Docker data | `/var/lib/docker` | `/home/user/data` |
| Volumes | `/var/lib/docker/volumes` | `/home/user/data/volumes` |

**Physical path of wp-volume:**
```
/home/user/data/volumes/srcs_wp-volume/_data/
```

### The "two doors" concept

```
Physical Room (actual files)
/home/user/data/volumes/srcs_wp-volume/_data/
        │
        ├── Door 1 → WordPress sees as /var/www/html
        └── Door 2 → Nginx sees as /var/www/html
```

Files physically live in one place. Containers access them through mounted paths.
Like Google Drive — files on Google's servers, you access from anywhere.

---

## Complete Architecture

```
Outside World
      ↓
   port 443 (HTTPS only)
      ↓
  [Nginx :443]
      │
      ├── Static files (from wp-volume)
      │
      └── PHP requests → [WordPress :9000]
                              │         │
                        [MariaDB    [Redis
                          :3306]    :6379]

All containers on private "inception" network
Data persisted in /home/user/data/volumes/
```

---

## Key Concepts Summary

| Concept | Explanation |
|---------|------------|
| `bind 0.0.0.0` | Accept connections from anywhere (not just localhost) |
| `daemon off` / `daemonize no` / `-F` | Keep process in foreground to keep container alive |
| `exec` | Replace script process with the main process |
| `ENTRYPOINT` vs `CMD` | ENTRYPOINT is fixed, CMD is overridable |
| Volumes | Persistent storage that survives container restarts |
| `depends_on` | Start order control between containers |
| Self-signed cert | SSL certificate you create yourself (shows browser warning) |
| FastCGI | Protocol/translator between Nginx and PHP |
| LRU | Least Recently Used — eviction policy for Redis |