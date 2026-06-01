# Inception — Redis Caching Configuration (Bonus)

This document explains the configuration of the Redis caching service, detailing its [Dockerfile](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/bonus/redis/Dockerfile) and configuration file [redis.conf](file:///c:/42AD/staff-evaluation/inception/srcs/requirements/bonus/redis/conf/redis.conf).

---

## 1. Redis Dockerfile (`bonus/redis/Dockerfile`)

```dockerfile
FROM alpine:3.22
```
* **What it is for:** Sets the base operating system image to Alpine Linux version 3.22.
* **Why it is needed:** Alpine Linux is a lightweight, security-oriented Linux distribution. Using Alpine for bonus services keeps the container image size small.

```dockerfile
RUN apk add --no-cache redis
```
* **What it is for:** Installs the Redis server package.
* **How it works:** `--no-cache` prevents caching the package index locally, reducing the container image size.

```dockerfile
COPY ./conf/redis.conf /etc/redis/redis.conf
EXPOSE 6379
CMD ["redis-server", "/etc/redis/redis.conf"]
```
* **What it is for:** Copies the configuration file, documents port `6379`, and starts the Redis server in the foreground.

---

## 2. Redis Configuration (`bonus/redis/conf/redis.conf`)

The configuration file defines how the Redis server behaves.

```ini
bind 0.0.0.0
port 6379
```
* **`bind 0.0.0.0`**: Instructs Redis to listen on all network interfaces. This allows the WordPress container to connect to it over the private bridge network.
* **`port 6379`**: Sets the listening port to `6379` (the default Redis port).

```ini
protected-mode no
daemonize no
```
* **`protected-mode no`**: Disables protected mode. When protected mode is active, Redis will refuse external queries unless a password is set. Since this container runs on an isolated private network, disabling this option simplifies integration.
* **`daemonize no`**: Prevents Redis from running as a background service, ensuring the process runs in the foreground as PID 1 to keep the container active.

```ini
maxmemory 256mb
maxmemory-policy allkeys-lru
```
* **`maxmemory 256mb`**: Restricts the database's memory usage to 256 Megabytes.
* **`maxmemory-policy allkeys-lru`**: Defines the data eviction policy when memory limits are reached.
  * `allkeys-lru` (Least Recently Used) instructs Redis to automatically remove the least recently accessed keys to make room for new cache data, preventing memory limit crashes.

---

## Next Steps

Now that we have covered all the configuration files, let's look at the **most common questions asked during evaluation**.

👉 Proceed to [06_Evaluation_Questions_and_Answers.md](./06_Evaluation_Questions_and_Answers.md)
