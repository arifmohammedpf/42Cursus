*This project has been created as part of the 42 curriculum by arimoham.*

# Inception

## Description

Inception is a system administration project that introduces Docker containerization by setting up a complete web infrastructure. The goal is to build a multi-service architecture using Docker Compose, where each service runs in its own container, communicating through a custom Docker network.

This project deploys a fully functional **WordPress website** with:
- **NGINX** as the web server with TLSv1.2/TLSv1.3 encryption
- **WordPress** with PHP-FPM for dynamic content
- **MariaDB** as the database backend
- **Redis** for object caching (bonus)

All mandatory services (NGINX, WordPress, MariaDB) are containerized using custom Dockerfiles built from Debian Bookworm, while bonus services (Redis) use Alpine Linux for a lighter footprint.

---

## Instructions

### Prerequisites

- Docker and Docker Compose installed
- `make` utility
- Sudo privileges (for volume management)

### Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone <repository-url> Inception
   cd Inception
   ```

2. **Configure environment variables:**
   Create a `.env` file in the `srcs/` directory with the required variables (see DEV_DOC.md for details).

3. **Update `/etc/hosts`:**
   ```bash
   sudo echo "127.0.0.1 arimoham.42.fr" >> /etc/hosts
   ```

4. **Build and start all services:**
   ```bash
   make
   ```

5. **Access the services:**
   - WordPress: `https://arimoham.42.fr`

### Available Make Commands

| Command | Description |
|---------|-------------|
| `make` or `make all` | Build and start all containers in detached mode |
| `make bonus` | Same as `make all` (includes bonus services) |
| `make up` | Build and start all containers in detached mode |
| `make down` | Stop all containers |
| `make clean` | Stop containers and remove orphan containers |
| `make fclean` | Full cleanup: stops containers, prunes all Docker resources including volumes |
| `make re` | Complete rebuild: runs `fclean` then `all` |
| `make logs` | Follow logs from all containers in real-time |

---

## Project Description

### Docker Architecture

This project leverages Docker to create isolated, reproducible environments for each service. Unlike traditional setups where all services run on a single machine, each component (NGINX, WordPress, MariaDB, Redis) runs in its own container with:
- Its own filesystem
- Defined network interfaces
- Controlled resource allocation

The services communicate through a dedicated Docker bridge network called `inception`.

### Sources and Services

| Service | Purpose | Base Image | Port |
|---------|---------|------------|------|
| **nginx** | Reverse proxy & SSL termination | debian:bookworm | 443 |
| **wordpress** | PHP-FPM application server | debian:bookworm | 9000 (internal) |
| **mariadb** | MySQL-compatible database | debian:bookworm | 3306 (internal) |
| **redis** | In-memory cache for WordPress | alpine 3.22 | 6379

---

## Design Choices and Comparisons

### Virtual Machines vs Docker

| Aspect | Virtual Machines | Docker Containers |
|--------|------------------|-------------------|
| **Isolation** | Complete OS simulation | Process isolation |
| **Resource Usage** | Heavy (full OS per VM) | Lightweight (shared kernel) |
| **Startup Time** | Minutes | Seconds |
| **Portability** | Machine images are large (GBs) | Images are smaller, layered |
| **Use Case** | Complete OS isolation, different OS types | Microservices, consistent environments |

**Project Choice:** Docker is required by the project subject. It was chosen for its lightweight nature, faster startup, and better suited architecture for microservices like web stacks.

### Secrets vs Environment Variables

| Aspect | Secrets | Environment Variables |
|--------|---------|----------------------|
| **Storage** | Encrypted, managed by orchestrator | Plain text in compose/shell |
| **Access** | Mounted as files, limited access | Available to all processes |
| **Security** | More secure, not in image layers | Can leak in logs, history |
| **Complexity** | More setup required | Simple to implement |

**Project Choice:** Environment variables are used via `.env` files for simplicity in a development context.

### Docker Network vs Host Network

| Aspect | Docker Network (Bridge) | Host Network |
|--------|------------------------|--------------|
| **Isolation** | Separate network namespace per container | Shares host's network stack |
| **Port Mapping** | Explicit port publishing required (`-p 443:443`) | Direct access to all host ports |
| **Inter-container Comms** | Via container names as DNS hostnames | Via localhost only |
| **Security** | Better isolation, controlled exposure | Less secure, potential port conflicts |
| **Use Case** | Multi-container apps, microservices | Performance-critical single containers |

**Project Choice:** A custom bridge network (`inception`) is required by the subject and provides service isolation. Containers communicate using service names as hostnames (e.g., `wordpress` can reach the database at `mariadb:3306`), making configuration cleaner and more maintainable.

### Docker Volumes vs Bind Mounts

| Aspect | Docker Volumes | Bind Mounts |
|--------|---------------|-------------|
| **Management** | Managed by Docker daemon | Direct host filesystem paths |
| **Portability** | Portable across hosts | Tied to specific host paths |
| **Performance** | Optimized for containers | Native filesystem speed |
| **Backup** | Via `docker volume` commands | Direct file access on host |
| **Location** | Configurable via `daemon.json` | Any host directory |
| **Permissions** | Docker handles permissions | May require manual setup |

**Project Choice:** Named volumes (`db-volume`, `wp-volume`) are used as bind mounts are forbidden by the subject. Docker's `daemon.json` is configured with `"data-root": "/home/arimoham/data"` to store all volume data in the required host location, while keeping volumes fully managed by Docker.

---

## Resources

### Official Documentation
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Developer Resources](https://developer.wordpress.org/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)
- [Redis Documentation](https://redis.io/documentation)

### Tutorials and Articles
- [Docker Crash Course](https://www.youtube.com/watch?v=Tyy1BUEmhwg&t=217s)

### AI Usage Disclosure

AI tools (GitHub Copilot/Gemini) were used to assist with:
- **Documentation**: Structuring README, USER_DOC, and DEV_DOC files
- **Configuration review**: Validating Dockerfile syntax and best practices
- **Troubleshooting**: Debugging container networking and service communication issues

All AI-generated content was reviewed, tested, and adapted to fit the specific project requirements.