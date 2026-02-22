#!/usr/bin/env bash
set -e

cd /var/www/html

echo "Waiting for MariaDB..."
until mysqladmin -h mariadb -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" ping --silent; do
    sleep 2
done
echo "MariaDB is ready!"

if [ ! -f ./wp-includes/version.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root
fi

if [ ! -f ./wp-config.php ]; then
    echo "Creating wp-config.php..."
    wp config create --allow-root \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="mariadb"
    
    # Redis configuration 
    echo "Adding Redis configuration..."
    sed -i "/require_once ABSPATH . 'wp-settings.php';/i \\
    define('WP_REDIS_HOST', 'redis');\\
    define('WP_REDIS_PORT', 6379);\\
    define('WP_CACHE', true);\\
    " ./wp-config.php
fi

if ! wp core is-installed --allow-root; then
    echo "Installing WordPress..."
    wp core install --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="${WP_SITE_TITLE}" \
        --admin_user="${WP_ADMIN}" \
        --admin_password="${WP_ADMIN_PASS}" \
        --admin_email="${WP_ADMIN_EMAIL}"
    
    wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASS}" \
        --allow-root
fi


if ! wp plugin is-installed redis-cache --allow-root; then
    echo "Installing Redis Object Cache plugin..."
    wp plugin install redis-cache --allow-root
fi

if ! wp plugin is-active redis-cache --allow-root; then
    echo "Activating Redis Object Cache plugin..."
    wp plugin activate redis-cache --allow-root
fi

echo "Enabling Redis object cache..."
wp redis enable --allow-root || true

echo "Starting PHP-FPM..."
exec php-fpm8.2 -F