NAME = inception
DATA_PATH = /home/arimoham/data
COMPOSE_FILE = ./srcs/docker-compose.yml

all: up

bonus: all

up:
	@sudo mkdir -p $(DATA_PATH)
	@docker compose -f $(COMPOSE_FILE) up -d --build

down:
	@docker compose -f $(COMPOSE_FILE) down

clean:
	@docker compose -f $(COMPOSE_FILE) down --remove-orphans

fclean: clean
	@docker volume rm -f srcs_db-volume srcs_wp-volume 2>/dev/null || true
	@docker system prune -af --volumes
	@sudo rm -rf $(DATA_PATH)/volumes/srcs_*

re: fclean all

logs:
	@docker compose -f $(COMPOSE_FILE) logs -f

.PHONY: all up down clean fclean re logs