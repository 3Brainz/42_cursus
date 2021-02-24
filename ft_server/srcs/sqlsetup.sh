# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    phpmyadmin.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 10:52:43 by ppunzo            #+#    #+#              #
#    Updated: 2021/02/23 15:13:36 by ppunzo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!bin/bash

echo "CREATE DATABASE wordpress;" | mysql -uroot
echo "CREATE USER 'ppunzo'@'localhost' IDENTIFIED BY '123password';" | mysql -uroot
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'ppunzo'@'localhost' WITH GRANT OPTION;"| mysql -uroot
echo "FLUSH PRIVILEGES;"| mysql -uroot
echo "update mysql.user set plugin='' where user='ppunzo';"| mysql -uroot

bash