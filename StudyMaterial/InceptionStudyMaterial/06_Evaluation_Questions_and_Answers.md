# Inception — Evaluation Q&A Cheat Sheet

This document compiles the most common questions asked by 42 evaluators during the Inception defense, along with clear, technical, and accurate answers to help you explain the project successfully.

---

## 1. Virtualization & Core Architecture

### Q1: What is the difference between a Virtual Machine (VM) and a Docker Container?
* **Answer:** A VM virtualizes hardware. It runs a complete guest operating system, including its own kernel, on top of a hypervisor. This requires significant CPU, RAM, and disk space. A container virtualizes the operating system. It shares the host system's kernel and runs as an isolated process in user space, using Linux kernel features like **namespaces** (for isolation) and **cgroups** (for resource limits). This makes containers lightweight, fast to boot, and highly efficient.

### Q2: Why do we run NGINX and WordPress (PHP-FPM) in separate containers?
* **Answer:** This design adheres to the **one-process-per-container** principle. It provides process isolation and mirrors production environments where components are scaled independently (e.g. running multiple web servers behind a load balancer pointing to a pool of application servers).

### Q3: Why is NGINX needed? Why can't WordPress serve the website directly?
* **Answer:** WordPress is a PHP application. PHP-FPM executes the code but is not a web server; it cannot parse HTTP requests, serve static assets (images, CSS), or manage SSL handshakes directly. NGINX acts as a reverse proxy and web server: it handles incoming HTTPS connections, serves static files directly from the shared volume, and forwards dynamic requests to PHP-FPM on port 9000.

---

## 2. Docker Compose & Configuration

### Q4: What is the difference between the `ports` and `expose` directives?
* **Answer:** 
  * `ports` maps a port on the host machine to a port in the container (e.g. `"443:443"`). This makes the port accessible from outside the host machine.
  * `expose` documents that the container listens on a specific port, but **does not** map it to the host. The port is only accessible to other containers on the same network. In this project, only NGINX uses `ports` to publish port 443, while other services rely on internal network communication.

### Q5: What does the `depends_on` directive do? Does it guarantee database readiness?
* **Answer:** No, it only controls **startup order**. It tells Docker Compose to launch the database container before the WordPress container. However, it does not check if the database engine inside the container has finished booting and is ready to receive queries. We handle this manually in `wordpress/tools/entrypoint.sh` using a loop that pings the database with `mysqladmin` until it responds.

---

## 3. Storage & Networking

### Q6: What is the difference between a Docker Volume and a Bind Mount?
* **Answer:** 
  * **Named Volumes** are managed entirely by Docker. Docker handles file permissions, directory creation, and stores data in a dedicated directory on the host filesystem.
  * **Bind Mounts** link a specific path on the host directly to a path inside the container.
  * *Project Context:* The project guidelines forbid using bind mounts. Instead, we use named volumes and configure Docker's data directory (`data-root`) in `/etc/docker/daemon.json` to store all volume files inside `/home/<login>/data`.

### Q7: How do NGINX and WordPress access the same files?
* **Answer:** They share the same named volume `wp-volume`. It is mounted at `/var/www/html` inside both the `wordpress` and `nginx` containers. This allows NGINX to read and serve static assets directly, while WordPress updates files in the same directory.

### Q8: How does inter-container communication work? How does NGINX know where WordPress is?
* **Answer:** Both containers are connected to the custom bridge network `inception`. Docker operates an internal DNS server for custom networks. When NGINX attempts to connect to `wordpress:9000`, the DNS server resolves the hostname `wordpress` to the private IP address of the WordPress container.

---

## 4. Scripting & Lifecycles

### Q9: Why do we use `exec` at the end of our entrypoint scripts?
* **Answer:** `exec` replaces the shell process (PID 1) with the target server process (e.g. `exec mysqld`). If we did not use `exec`, the shell script would remain active as PID 1, and the database server would run as a child process. This would prevent the container from receiving standard Linux signals (like SIGTERM), causing slow shutdowns and unclean exits.

### Q10: How do you ensure the MariaDB script is idempotent (safe to run multiple times)?
* **Answer:** The script checks if the database files have already been initialized on the volume by searching for the `/var/lib/mysql/mysql` directory. If it exists, the script skips the `mysql_install_db` and SQL user creation steps and starts the database server immediately. This ensures that restarting the container does not overwrite existing data or fail with duplicate user errors.

### Q11: What exactly happens when you run `make fclean`?
* **Answer:**
  1. Stops and removes all container structures.
  2. Deletes the custom bridge network.
  3. Force-removes the Docker volumes `srcs_db-volume` and `srcs_wp-volume`.
  4. Runs `docker system prune` to clear all image layers, networks, and build caches.
  5. Deletes the physical directories `/home/arimoham/data/volumes/` on the host to ensure all database and website files are fully wiped.
