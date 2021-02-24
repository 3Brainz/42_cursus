# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 10:52:43 by ppunzo            #+#    #+#              #
#    Updated: 2021/02/23 15:13:36 by ppunzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!bin/bash

echo "Starting_all_needed_services\n"
echo "SSLKEY"
openssl req -x509 -nodes -days 365 -subj "/C=IT/ST=Italy/L=Rome/O=Sect/OU=Robk/CN=Roberto" -newkey rsa:2048 -keyout /etc/ssl/nginx-selfsigned.key -out /etc/ssl/nginx-selfsigned.crt
echo "NGINX"
service nginx restart
echo "PHP_MY_ADMIN"
service php7.3-fpm start
service php7.3-fpm status
echo "MARIADB"
service mysql restart
echo "CREATING TABLES"
bash sqlsetup.sh

bash