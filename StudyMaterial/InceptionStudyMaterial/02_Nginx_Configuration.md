# Inception — NGINX & SSL Configuration

This document explains the configuration of the NGINX web server, including its custom [Dockerfile](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/nginx/Dockerfile), server block [inception.conf](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/nginx/conf/inception.conf), and startup script [entrypoint.sh](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/nginx/tools/entrypoint.sh).

---

## 1. NGINX Dockerfile (`nginx/Dockerfile`)

```dockerfile
FROM debian:bookworm
```
* **What it is for:** Sets the base operating system image.
* **Why it is needed:** The project requires building custom images from a standard base distro (Debian Bookworm).

```dockerfile
RUN apt-get update && apt-get install -y nginx openssl \
    && rm -rf /var/lib/apt/lists/*
```
* **What it is for:** Installs NGINX and the OpenSSL certificate utility.
* **Why it is needed:** NGINX handles incoming web requests, and OpenSSL is required to generate the self-signed TLS/SSL certificate.
* **How it works:** `rm -rf /var/lib/apt/lists/*` cleans up the apt package lists cache, minimizing image layer sizes.

```dockerfile
RUN mkdir -p /var/run/nginx
RUN rm -f /etc/nginx/sites-enabled/default
```
* **What it is for:** Directory initialization and configuration cleanup.
* **Why it is needed:** We must disable NGINX's default welcome page so that our custom domain configuration file takes priority.

```dockerfile
COPY ./conf/inception.conf /etc/nginx/conf.d/inception.conf
COPY ./tools/entrypoint.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/entrypoint.sh
```
* **What it is for:** Copies config assets and scripts into the image filesystem.

```dockerfile
EXPOSE 443
ENTRYPOINT ["entrypoint.sh"]
```
* **What it is for:** Documents listening ports and binds the startup script.
* **Why it is needed:** Port `443` is the standard port for HTTPS traffic.

---

## 2. NGINX Server Block Configuration (`nginx/conf/inception.conf`)

The configuration file defines how virtual hosts process requests.

```nginx
server {
    listen 443 ssl;
    listen [::]:443 ssl;
    
    server_name arimoham.42.fr;
    root /var/www/html;
    index index.php index.html;
```
* **`listen 443 ssl`**: Instructs NGINX to listen on port `443` for TLS-encrypted IPv4 traffic.
* **`listen [::]:443 ssl`**: Listens on port `443` for TLS-encrypted IPv6 traffic.
* **`server_name`**: Specifies the domain name. Requests matching this host are handled by this server block.
* **`root`**: The path containing the web files. Shared via `wp-volume`.
* **`index`**: Order of priority for search files when navigating to a folder.

```nginx
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_certificate /etc/nginx/ssl/inception.crt;
    ssl_certificate_key /etc/nginx/ssl/inception.key;
```
* **`ssl_protocols`**: Restricts connection handshakes to **TLSv1.2** and **TLSv1.3** for security.
* **`ssl_certificate` / `ssl_certificate_key`**: Paths to the public certificate and private key files inside the container.

```nginx
    location / {
        try_files $uri $uri/ /index.php?$args;
    }
```
* **What it is for:** Handles general requests.
* **Why it is needed:** Standard WordPress routing behavior.
* **How it works:** If a visitor requests `https://arimoham.42.fr/about`, NGINX first searches for a file named `about` (`$uri`), then a folder named `about/` (`$uri/`). If neither exists, it passes the request parameter to `/index.php` (`/index.php?$args`), allowing WordPress's router to parse the page dynamically.

```nginx
    location ~ \.php$ {
        include snippets/fastcgi-php.conf;
        fastcgi_pass wordpress:9000;
    }
}
```
* **What it is for:** Handles PHP file execution.
* **Why it is needed:** NGINX cannot process PHP files natively. It must forward them to PHP-FPM.
* **How it works:** Any URL ending in `.php` is captured by this location block. It packages the headers and routes the request to host `wordpress` on port `9000` via the FastCGI protocol.

---

## 3. NGINX Startup Script (`nginx/tools/entrypoint.sh`)

```bash
#!/bin/bash
set -e

mkdir -p /etc/nginx/ssl
```
* **`set -e`**: Aborts script execution if any command fails.
* **`mkdir -p /etc/nginx/ssl`**: Creates the folder to store the keys.

```bash
if [ ! -f /etc/nginx/ssl/inception.crt ]; then
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/inception.key \
        -out /etc/nginx/ssl/inception.crt \
        -subj "/C=$SSL_COUNTRY/ST=$SSL_STATE/L=$SSL_CITY/O=$SSL_ORG/OU=$SSL_UNIT/CN=$DOMAIN_NAME"
fi
```
* **What it is for:** Generates a self-signed TLS/SSL certificate.
* **Why it is needed:** Required for HTTPS communication. Generating it dynamically using environment variables avoids saving raw cryptographic keys inside the source code repository.
* **How it works:** Checks if the certificate file exists. If missing:
  * Uses `openssl` to generate a new key and public certificate.
  * `-x509`: Specifies a self-signed certificate structure.
  * `-nodes`: Disables password prompt protection (so NGINX can start automatically).
  * `-days 365`: Sets a 1-year expiration date.
  * `-newkey rsa:2048`: Generates a 2048-bit RSA key.
  * `-subj`: Injects certificate fields from the environment variables (e.g. `$DOMAIN_NAME`).

```bash
exec nginx -g 'daemon off;'
```
* **What it is for:** Runs NGINX in the foreground.
* **Why it is needed:** In Docker, a container's lifecycle is tied to its primary process (PID 1). If the primary process stops, the container halts.
* **How it works:** Runs NGINX with `daemon off;` to prevent it from spawning background processes. The `exec` command replaces the shell process with the NGINX executable, passing signals (like SIGTERM) directly to NGINX for a clean shutdown.

---

## Next Steps

Now let's examine the database service: **MariaDB**.

👉 Proceed to [03_MariaDB_Configuration.md](./03_MariaDB_Configuration.md)
