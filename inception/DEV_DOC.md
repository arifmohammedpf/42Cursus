# Developer Documentation

*This document describes how to set up, build, and maintain the Inception infrastructure from a developer perspective.*

---

## Environment Setup from Scratch

### Prerequisites

Ensure the following are installed on your system:

| Requirement | Minimum Version | Installation (Debian/Ubuntu) |
|-------------|-----------------|------------------------------|
| Docker | 20.10+ | `sudo apt install docker.io` |
| Docker Compose | 2.0+ | `sudo apt install docker-compose-plugin` |
| Make | 4.0+ | `sudo apt install make` |
| Git | 2.0+ | `sudo apt install git` |

Verify installations:
```bash
docker --version
docker compose version
make --version
```

### Add User to Docker Group

To run Docker without sudo:
```bash
sudo usermod -aG docker $USER
newgrp docker
```

### Clone the Repository

```bash
git clone <repository-url> Inception
cd Inception
```

### Configure Docker Data Root

To store Docker volumes in `/home/<login>/data` as required by the subject, configure Docker's daemon:

```bash
sudo mkdir -p /home/<login>/data
sudo nano /etc/docker/daemon.json
```

Add the following configuration:

```json
{
  "data-root": "/home/<login>/data"
}
```

Restart Docker to apply changes:

```bash
sudo systemctl restart docker
```

Verify the new data root:

```bash
docker info | grep "Docker Root Dir"
```

### Configure DNS Resolution

Add the domain to your hosts file:
```bash
sudo sh -c 'echo "127.0.0.1 <login>.42.fr" >> /etc/hosts'
```

---

## Configuration Files

### Environment Variables (.env)

Create the environment file at `srcs/.env`:

```bash
touch srcs/.env
```

Required variables:

```env
# Domain Configuration
DOMAIN_NAME=login.42.fr

# MariaDB Configuration
MYSQL_ROOT_PASSWORD=your_secure_root_password
MYSQL_DATABASE=wordpress_db
MYSQL_USER=wp_user
MYSQL_PASSWORD=your_secure_db_password

# WordPress Admin
WP_SITE_TITLE=Inception
WP_ADMIN=<admin_user>
WP_ADMIN_PASS=<your_secure_admin_password>
WP_ADMIN_EMAIL=<admin@example.com>

# WordPress Additional User
WP_USER=<editor>
WP_USER_PASS=<your_secure_user_password>
WP_USER_EMAIL=<editor@example.com>

# SSL Certificate Info
SSL_COUNTRY=<country-initials>
SSL_STATE=<state>
SSL_CITY=<city>
SSL_ORG=<org>
SSL_UNIT=<unit>
```

### Secrets Management

For development, credentials are stored in the `.env` file.

### Project Structure

```
Inception/
├── Makefile                    # Build automation
├── README.md                   # Project overview
├── USER_DOC.md                 # User documentation
├── DEV_DOC.md                  # This file
└── srcs/
    ├── .env                    # Environment variables (create this)
    ├── docker-compose.yml      # Service orchestration
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   └── tools/
        │       └── docker_entry.sh
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── inception.conf
        │   └── tools/
        │       └── entrypoint.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   └── tools/
        │       └── entrypoint.sh
        └── bonus/
            ├── redis/
               ├── Dockerfile
               └── conf/
                    └── redis.conf
```

---

## Building and Launching the Project

### Using the Makefile

The Makefile provides convenient commands for common operations:

| Command | Description |
|---------|-------------|
| `make` or `make all` | Build and start all containers |
| `make up` | Same as `make all` |
| `make bonus` | Build with bonus services (same as `make all`) |
| `make down` | Stop all containers |
| `make clean` | Stop containers and remove orphan containers |
| `make fclean` | Full cleanup (prunes all Docker resources including volumes) |
| `make re` | Rebuild from scratch |
| `make logs` | Follow container logs |

### Direct Docker Compose Commands

For more control, use Docker Compose directly:

```bash
# Build images without starting
docker compose -f srcs/docker-compose.yml build

# Start in foreground (see all logs)
docker compose -f srcs/docker-compose.yml up

# Start specific service
docker compose -f srcs/docker-compose.yml up -d nginx

# Rebuild specific service
docker compose -f srcs/docker-compose.yml up -d --build wordpress

# View service status
docker compose -f srcs/docker-compose.yml ps
```

---

## Managing Containers and Volumes

### Container Management

```bash
# List running containers
docker ps

# List all containers (including stopped)
docker ps -a

# Stop a specific container
docker stop <container_name>

# Start a stopped container
docker start <container_name>

# Restart a container
docker restart <container_name>

# Remove a stopped container
docker rm <container_name>

# Execute command in running container
docker exec -it <container_name> <command>

# Examples:
docker exec -it wordpress bash
docker exec -it mariadb mysql -u root -p
docker exec -it nginx nginx -t
```

### Volume Management

```bash
# List all volumes
docker volume ls

# Inspect a volume
docker volume inspect srcs_db-volume
docker volume inspect srcs_wp-volume

# Remove unused volumes
docker volume prune

# Remove specific volume (container must be stopped)
docker volume rm srcs_db-volume
```

### Network Management

```bash
# List networks
docker network ls

# Inspect the inception network
docker network inspect inception_inception

# View container IPs
docker network inspect inception_inception | grep -A 5 "Containers"
```

### Image Management

```bash
# List images
docker images

# Remove specific image
docker rmi <image_name>

# Remove all unused images
docker image prune -a

# Rebuild image without cache
docker compose -f srcs/docker-compose.yml build --no-cache <service>
```

---

## Data Storage and Persistence

### Volume Configuration

The project uses Docker named volumes to persist data:

```yaml
volumes:
  db-volume:
  wp-volume:
```

Named volumes are managed by Docker and stored in `/home/<login>/data/volumes/` (as configured in `daemon.json`).

### Data Locations

| Data | Container Path | Docker Volume |
|------|---------------|---------------|
| WordPress files | `/var/www/html` | `srcs_wp-volume` |
| MariaDB data | `/var/lib/mysql` | `srcs_db-volume` |

### Persistence Behavior

- **Container restart:** Data persists
- **`make down`:** Data persists
- **`make clean`:** Data persists (only removes orphan containers)
- **`make fclean`:** All data deleted (volumes removed, system pruned)

### Inspecting Data

```bash
# View WordPress files (inside container)
docker exec wordpress ls -la /var/www/html

# View database files (inside container)
docker exec mariadb ls -la /var/lib/mysql

# Inspect volume details
docker volume inspect srcs_wp-volume
docker volume inspect srcs_db-volume

# Check volume disk usage
docker system df -v | grep -E "wp-volume|db-volume"
```

---

## Debugging and Troubleshooting

### Viewing Logs

```bash
# All containers
make logs

# Specific container
docker logs nginx
docker logs wordpress
docker logs mariadb

# Follow logs in real-time
docker logs -f wordpress

# Last 100 lines
docker logs --tail 100 nginx
```

### Common Debug Commands

```bash
# View container resource usage
docker stats

# Check port bindings
docker port nginx

# Test internal networking
docker exec wordpress ping mariadb
docker exec nginx ping wordpress

# Check if services are listening
docker exec wordpress netstat -tlnp
docker exec mariadb netstat -tlnp
```

## Development Workflow

### Making Changes to Dockerfiles

1. Edit the Dockerfile
2. Rebuild the specific service:
   ```bash
   docker compose -f srcs/docker-compose.yml build --no-cache <service>
   ```
3. Restart the service:
   ```bash
   docker compose -f srcs/docker-compose.yml up -d <service>
   ```

### Making Changes to Configuration

1. Edit configuration files in `conf/` directories
2. Rebuild and restart:
   ```bash
   make re
   ```

### Testing Changes

```bash
# Quick test cycle
make down && make up

# Full rebuild (when Dockerfile changes)
make re
```

### Adding a New Service

1. Create directory: `srcs/requirements/<service_name>/`
2. Add `Dockerfile` and any configuration files
3. Add service to `docker-compose.yml`
4. Update Makefile if needed
5. Build and test: `make re`

---