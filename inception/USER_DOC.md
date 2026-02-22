# User Documentation

*This document explains how to use and manage the Inception web infrastructure.*

---

## Overview of Services

The Inception stack provides a complete web hosting environment with the following services:

| Service | Description | Access |
|---------|-------------|--------|
| **WordPress** | Content Management System for creating and managing website content | `https://arimoham.42.fr` |
| **NGINX** | Web server that handles HTTPS connections and serves the WordPress site | Port 443 |
| **MariaDB** | Database server storing all WordPress data (posts, users, settings) | Internal only |
| **Redis** | Caching system that speeds up WordPress performance | Internal only

---

## Starting and Stopping the Project

### Starting the Services

To start all services, open a terminal in the project root directory and run:

```bash
make
```

This command will:
1. Build all Docker images
2. Start all containers in the background

Wait approximately 30-60 seconds for all services to fully initialize.

### Stopping the Services

To stop all services (containers remain available for restart):

```bash
make down
```

To stop services and remove orphan containers:

```bash
make clean
```

To completely reset everything (removes all data and Docker resources):

```bash
make fclean
```

> ⚠️ **Warning:** `make fclean` will permanently delete all WordPress content and database data!

### Restarting the Services

To rebuild and restart everything:

```bash
make re
```

---

## Accessing the Website

### WordPress Site

1. Open your web browser
2. Navigate to: **`https://arimoham.42.fr`**
3. Accept the self-signed SSL certificate warning (this is expected in development)

> **Note:** Ensure `arimoham.42.fr` is mapped to `127.0.0.1` in your `/etc/hosts` file.

### WordPress Admin Panel

1. Navigate to: **`https://arimoham.42.fr/wp-admin`**
2. Enter your administrator credentials:
   - **Username:** As configured in `WP_ADMIN` environment variable
   - **Password:** As configured in `WP_ADMIN_PASS` environment variable

## Locating and Managing Credentials

### Where Credentials Are Stored

All credentials are defined in the environment file:

```
srcs/.env
```

### Required Credentials

| Variable | Description |
|----------|-------------|
| `MYSQL_ROOT_PASSWORD` | MariaDB root user password |
| `MYSQL_DATABASE` | Name of the WordPress database |
| `MYSQL_USER` | Database user for WordPress |
| `MYSQL_PASSWORD` | Password for the database user |
| `WP_ADMIN` | WordPress administrator username |
| `WP_ADMIN_PASS` | WordPress administrator password |
| `WP_ADMIN_EMAIL` | WordPress administrator email |
| `WP_USER` | Additional WordPress user username |
| `WP_USER_PASS` | Additional WordPress user password |
| `WP_USER_EMAIL` | Additional WordPress user email |

### Changing Credentials

1. Stop the services: `make down`
2. Edit `srcs/.env` with new values
3. For database credential changes, run: `make fclean` (this deletes all data)
4. Restart: `make`

> **Important:** Changing database credentials after initial setup requires a full reset (`make fclean`) as the database is initialized with the original credentials.

---

## Checking Service Status

### View Running Containers

```bash
docker ps
```

Expected output should show 6 running containers:
- `nginx`
- `wordpress`
- `mariadb`
- `redis`

### View Container Logs

To follow logs from all services in real-time:

```bash
make logs
```

To view logs for a specific service:

```bash
docker logs <container_name>
```

Examples:
```bash
docker logs nginx
docker logs wordpress
docker logs mariadb
```

### Check Service Health

#### Test NGINX/WordPress:
```bash
curl -k https://arimoham.42.fr
```

#### Test MariaDB Connection:
```bash
docker exec -it mariadb mysql -u root -p
```

#### Test Redis:
```bash
docker exec -it redis redis-cli ping
```
Expected response: `PONG`

### Common Issues

| Symptom | Possible Cause | Solution |
|---------|---------------|----------|
| Cannot access `arimoham.42.fr` | Missing hosts entry | Add `127.0.0.1 arimoham.42.fr` to `/etc/hosts` |
| SSL certificate warning | Self-signed certificate | Accept the warning (expected behavior) |
| WordPress shows database error | MariaDB not ready | Wait 30 seconds and refresh |
| Containers keep restarting | Configuration error | Check logs with `docker logs <container>` |
| Port already in use | Conflicting service | Stop other services using ports 443, 8080, 4200, 6379 |

---