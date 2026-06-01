# Inception Codebase Study Materials

This directory contains comprehensive study materials for the **Inception** project. These resources are designed to help you understand the architecture, Docker Compose, NGINX, MariaDB, WordPress, Redis, and virtualization concepts of the project, enabling you to explain the codebase clearly during your defense.

---

## 📖 Chapter Index

| Chapter | File | Description | Key Concepts Covered |
|:---:|---|---|---|
| **0** | [00_Overview_and_Architecture.md](./00_Overview_and_Architecture.md) | High-level project architecture overview. | Docker vs Virtual Machines, bridge networking, DNS service resolution, and volume persistence. |
| **1** | [01_Docker_Compose_and_Makefile.md](./01_Docker_Compose_and_Makefile.md) | Code integration and environment orchestration. | `docker-compose.yml` directives, host storage, dependency routing, and the Makefile target lifecycle. |
| **2** | [02_Nginx_Configuration.md](./02_Nginx_Configuration.md) | Web server, SSL termination, and reverse proxy setup. | Custom NGINX Dockerfile, vhost routing blocks (`inception.conf`), FastCGI forwarding, and OpenSSL cert generation. |
| **3** | [03_MariaDB_Configuration.md](./03_MariaDB_Configuration.md) | Relational database backend services. | MariaDB server installation, remote network binding (`0.0.0.0`), background bootstrap servers, and idempotent setup logic. |
| **4** | [04_WordPress_Configuration.md](./04_WordPress_Configuration.md) | PHP application server and automated bootstrapping. | PHP-FPM socket configuration, WP-CLI download and installation commands, user creation, and database connection checks. |
| **5** | [05_Redis_Configuration_Bonus.md](./05_Redis_Configuration_Bonus.md) | In-memory cache bonus service configuration. | Alpine base image, Redis server configurations, protected mode disablement, and LRU memory eviction policy. |
| **6** | [06_Evaluation_Questions_and_Answers.md](./06_Evaluation_Questions_and_Answers.md) | Viva defense cheat sheet for evaluations. | Process isolation details, volume behaviors, network structures, PID 1 signaling, and common evaluator questions. |

---

## 🛠️ How to Use These Materials

1. **Read in Order:** If you are new to Docker or network administration, begin with **Chapter 0** to establish a solid conceptual framework.
2. **Follow Code References:** Files and scripts are linked (e.g. `[entrypoint.sh]`) to let you jump straight to the source files on your system.
3. **Review the Cheat Sheet:** Use **Chapter 6** as a revision checklist before your defense to align your answers with what evaluators look for in this project.
