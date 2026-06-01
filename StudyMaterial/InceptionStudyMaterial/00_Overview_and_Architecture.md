# Inception — Overview & Architecture

Welcome to the Inception Study Materials! This guide is designed to help you understand every aspect of the Inception project, from the high-level virtualization concept to the detailed container configurations and script execution steps.

---

## 1. What is Inception?

**Inception** is a system administration project at 42 that introduces you to **Docker** and virtualization. The goal is to build a complete multi-service web infrastructure using **Docker Compose**.

Each service must run in its own dedicated container, built from scratch using custom **Dockerfiles** (mostly based on `debian:bookworm`), and they must communicate securely over a custom private Docker network.

### The Stack Topology

The infrastructure runs a WordPress website over HTTPS:
- **NGINX:** The entry point. Handles SSL termination (HTTPS on port 443) and routes static assets or forwards dynamic requests.
- **WordPress (with PHP-FPM):** The application server. Executes PHP scripts and communicates with the database and cache.
- **MariaDB:** The database backend. Stores WordPress tables (posts, users, options).
- **Redis (Bonus):** In-memory data structure cache. Speeds up WordPress by caching database queries.

```
                  Public Traffic (HTTPS)
                            │
                            ▼ [Port 443]
                       ┌─────────┐
                       │  NGINX  │
                       └────┬────┘
                            │
               FastCGI      │ [Port 9000]
            (Internal IP)   ▼
                       ┌─────────┐
                       │WordPress│
                       └─┬─────┬─┘
                         │     │
          MySQL [Port 3306]    │ Redis [Port 6379]
                         ▼     ▼
                    ┌───────┐ ┌───────┐
                    │MariaDB│ │ Redis │
                    └───────┘ └───────┘
                     (Private internal-only hosts)
```

---

## 2. Core Concepts: Virtual Machines vs. Containers

A fundamental question during evaluation is the difference between Virtual Machines (VMs) and Containers.

| Feature | Virtual Machine (VM) | Docker Container |
| :--- | :--- | :--- |
| **Architecture** | App $\rightarrow$ Guest OS $\rightarrow$ Hypervisor $\rightarrow$ Host OS $\rightarrow$ Infrastructure | App $\rightarrow$ Docker Daemon $\rightarrow$ Host OS $\rightarrow$ Infrastructure |
| **Kernel** | Each VM has its own guest kernel. | Shares the Host OS kernel via namespaces and cgroups. |
| **Resource Overhead**| Heavy. Requires allocating RAM, CPU, and disk space for a complete OS. | Extremely lightweight. Only runs the service process. |
| **Boot Time** | Minutes (must boot a full OS). | Seconds (starts a single process). |
| **Isolation** | Strong hardware-level isolation. | Process-level isolation (namespace isolation). |

### Why Docker is Used Here
Docker is chosen for microservice architectures. It allows packaging services with all their dependencies into lightweight, reproducible layers, ensuring they run exactly the same way on any host.

---

## 3. Network and Security Model

All containers run inside a single user-defined bridge network named `inception`.

### Service Name DNS resolution
Docker runs an internal DNS server for bridge networks. Containers can resolve each other's IP addresses using their container/service names. For example:
- NGINX connects to WordPress at `wordpress:9000`.
- WordPress connects to the database at `mariadb:3306`.
- WordPress connects to Redis at `redis:6379`.

### Network Security (Port Exposure)
- **Only NGINX exposes ports to the host system:** It exposes port `443` for HTTPS traffic.
- **Internal services do not expose ports to the host:** MariaDB, WordPress, and Redis do not use `ports` directives in the compose file. Their ports are only accessible to other containers inside the private `inception` network. This prevents external clients from directly attacking the database or cache.

---

## 4. Volume Persistence and Host Storage

By default, files written inside a running container are stored in a temporary writable layer. If the container is destroyed, those files are lost.
To keep data persistent across container restarts, we use **Docker Volumes**.

### Shared Storage Mapping
- **`wp-volume`:** Mounted at `/var/www/html` in both the `wordpress` and `nginx` containers. This allows NGINX to serve static files directly, while forwarding dynamic requests to PHP-FPM running inside the WordPress container.
- **`db-volume`:** Mounted at `/var/lib/mysql` in the `mariadb` container, preserving database tables.

### Host Storage Redirection (`data-root`)
The project guidelines state that volume data must be saved to `/home/<login>/data`. 
- Bind mounts (e.g. mounting a host folder path directly like `-v /home/arimoham/data:/var/www/html`) are forbidden.
- Instead, we use Docker named volumes. To save these volumes to the `/home/<login>/data` directory on the host, we configure Docker's daemon file `/etc/docker/daemon.json`:
  ```json
  {
    "data-root": "/home/arimoham/data"
  }
  ```
  This instructs the Docker service to store all internal volumes and image cache inside `/home/arimoham/data/volumes/` instead of the default `/var/lib/docker/`.

---

## Next Steps

Now that you understand the architecture, let's explore **how the infrastructure is defined and run** via Docker Compose and the Makefile.

👉 Proceed to [01_Docker_Compose_and_Makefile.md](./01_Docker_Compose_and_Makefile.md)
