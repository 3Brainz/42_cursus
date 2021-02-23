# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 10:24:52 by ppunzo            #+#    #+#              #
#    Updated: 2021/02/23 15:14:11 by ppunzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

RUN apt update\
	&&  apt-get upgrade -y\
	&& apt-get -y install wget\	
	&& apt install nginx -y\
	&& apt install -y mariadb-server\
	&& apt-get -y install php7.3 php-mysql php-fpm php-pdo php-gd php-cli php-mbstring\
	&& rm -f /etc/nginx/sites-available/default\
	&& wget https://files.phpmyadmin.net/phpMyAdmin/5.0.1/phpMyAdmin-5.0.1-all-languages.tar.gz && tar -zxvf phpMyAdmin-5.0.1-all-languages.tar.gz && mv phpMyAdmin-5.0.1-all-languages /var/www/html/phpmyadmin

COPY srcs/start.sh .
COPY srcs/autoindex ./bin
COPY srcs/univers/* var/www/html/
COPY srcs/default /etc/nginx/sites-available

RUN chmod 777 bin/autoindex

CMD ./start.shcd 
