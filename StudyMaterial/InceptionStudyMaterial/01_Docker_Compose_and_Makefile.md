# Inception — Docker Compose & Makefile

This document explains the root [Makefile](file:///c:/42AD/staff-evaluation/inception/Makefile) and the [docker-compose.yml](file:///c:/42AD/staff-evaluation/inception/srcs/docker-compose.yml) files line-by-line, explaining what each option does, why it is needed, and how it executes.

---

## 1. The Root Makefile (`/Makefile`)

The Makefile automates building and stopping the infrastructure.

```makefile
NAME = inception
DATA_PATH = /home/arimoham/data
COMPOSE_FILE = ./srcs/docker-compose.yml
```
* **`DATA_PATH`**: The required host storage location.
* **`COMPOSE_FILE`**: Path to the compose definition.

### Makefile Targets Explained

#### `up:`
```makefile
up:
	@sudo mkdir -p $(DATA_PATH)
	@docker compose -f $(COMPOSE_FILE) up -d --build
```
* **What it is for:** Builds the custom Docker images and boots the containers.
* **Why it is needed:** Starts the application stack.
* **How it works:**
  1. Creates the `/home/arimoham/data` directory on the host with `sudo` permissions (to avoid permission errors).
  2. Runs `docker compose up` with:
     * `-f $(COMPOSE_FILE)`: Specifies the location of the compose file.
     * `-d`: Runs containers in "detached" mode (background).
     * `--build`: Forces Docker to rebuild the images from the Dockerfiles before starting.

#### `down:`
```makefile
down:
	@docker compose -f $(COMPOSE_FILE) down
```
* **What it is for:** Stops and removes running containers.
* **Why it is needed:** Performs a clean, temporary stop of the stack.
* **How it works:** Stops the containers, removes container structures, and removes the private `inception` network. It does **not** delete volumes, preserving your database.

#### `clean:`
```makefile
clean:
	@docker compose -f $(COMPOSE_FILE) down --remove-orphans
```
* **What it is for:** Stops containers and cleans up leftover resource objects.
* **Why it is needed:** Clears out old containers that were renamed or detached from the compose file.

#### `fclean:`
```makefile
fclean: clean
	@docker volume rm -f srcs_db-volume srcs_wp-volume 2>/dev/null || true
	@docker system prune -af --volumes
	@sudo rm -rf $(DATA_PATH)/volumes/srcs_*
```
* **What it is for:** Performs a complete destructive reset of all Docker objects.
* **Why it is needed:** Cleans the environment, deleting database contents and site configurations.
* **How it works:**
  1. Calls `clean` to stop containers.
  2. Force removes the Docker volume objects: `srcs_db-volume` and `srcs_wp-volume`.
  3. Runs `docker system prune -af --volumes` to delete all cached images, networks, build caches, and unused volumes.
  4. Deletes the physical volume files inside the host storage path `/home/arimoham/data/volumes/`.

---

## 2. Docker Compose File (`/srcs/docker-compose.yml`)

The `docker-compose.yml` file defines the architecture services, networks, and volumes.

### Services Block

#### `mariadb`
```yaml
  mariadb:
    build: ./requirements/mariadb/
    container_name: mariadb
    image: mariadb
    restart: always
    env_file:
      - .env
    volumes:
      - db-volume:/var/lib/mysql
    networks:
      - inception
```
* **`build`**: Path to the folder containing the MariaDB Dockerfile.
* **`container_name` / `image`**: Defines the running container name and image label.
* **`restart: always`**: If the container crashes or the host reboot, Docker starts it again automatically.
* **`env_file`**: Reads `srcs/.env` and injects its keys (e.g. `MYSQL_DATABASE`) as environment variables.
* **`volumes`**: Mounts named volume `db-volume` to `/var/lib/mysql` inside the container where database engine files are kept.
* **`networks`**: Connects this service to the private `inception` network.

#### `wordpress`
```yaml
  wordpress:
    build: ./requirements/wordpress/
    container_name: wordpress
    image: wordpress
    restart: always
    env_file:
      - .env
    volumes:
      - wp-volume:/var/www/html
    depends_on:
      - mariadb
      - redis
    networks:
      - inception
```
* **`depends_on`**: Declares that WordPress cannot start until `mariadb` and `redis` container structures are up. (Note: does not guarantee the database service is fully ready to receive queries; that is handled in the shell entrypoint).

#### `nginx`
```yaml
  nginx:
    build: ./requirements/nginx/
    container_name: nginx
    image: nginx
    restart: always
    ports:
      - "443:443"
    env_file:
      - .env
    volumes:
      - wp-volume:/var/www/html
    depends_on:
      - wordpress
    networks:
      - inception
```
* **`ports`**: Maps host port `443` to container port `443`. This exposes NGINX to public network traffic.
* **`volumes`**: Maps the same `wp-volume` to `/var/www/html`. NGINX needs direct access to this directory to serve static files (like stylesheets and images) directly without routing them to PHP.

---

### Volumes Block

```yaml
volumes:
  db-volume:
  wp-volume:
```
* **What it is for:** Declares named volumes at the root level of the compose document.
* **Why it is needed:** Registers the volume IDs so Docker compose knows how to mount them.
* **How it works:** Instructs Docker to create two storage directories managed by the Docker daemon.

---

### Networks Block

```yaml
networks:
  inception:
    driver: bridge
```
* **What it is for:** Declares a custom network.
* **Why it is needed:** Establishes the private network space.
* **How it works:** Uses the `bridge` driver to construct an isolated software network interface on the host machine. All containers attached to this network are assigned private IP addresses in a custom subnet and can communicate with each other.

---

## Next Steps

Now let's inspect the entry point service: **NGINX**.

👉 Proceed to [02_Nginx_Configuration.md](./02_Nginx_Configuration.md)
