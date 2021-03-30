/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppunzo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:22:55 by ppunzo            #+#    #+#             */
/*   Updated: 2021/03/16 18:22:56 by ppunzo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char *rand_string(char *str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...\0";
    if (size) {
        --size;
			srand(time(0));
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return (str);
}

static	void print_line(int len, char c, char color)
{
	int index;
	index = 0;

	if (color == 'b')
		printf("\033[0;30m");
	if (color == 'r')
		printf("\033[0;31m");
	if (color == 'g')
		printf("\033[0;32m");
	if (color == 'y')
		printf("\033[0;33m");
	if (color == 'b')
		printf("\033[0;34m");
	if (color == 'p')
		printf("\033[0;35m");
	if (color == 'c')
		printf("\033[0;36m");
	while (index < len)
	{
		printf("%c", c);
		index++;
	}
	printf("\033[0m\n");
}

static	void print_string(char *str, int width, char color)
{
	if (color == 'b')
		printf("\033[0;30m");
	if (color == 'r')
		printf("\033[0;31m");
	if (color == 'g')
		printf("\033[0;32m");
	if (color == 'y')
		printf("\033[0;33m");
	if (color == 'm')
		printf("\033[0;34m");
	if (color == 'p')
		printf("\033[0;35m");
	if (color == 'c')
		printf("\033[0;36m");
	printf("%*s",width, str);
	printf("\033[0m\n");
}

int		main(void)
{
	char	string[50];
	char	dest[50];
	int		var[10];
	int		fd_s[10];
	char	buffer[100];

	system("clear");
	//header
	print_line(210, '-', 'y');
	printf("\033[0;36m%-20s%-50s\033[0;35m%-50s\n\033[0m", "", "system", "mine");
	rand_string(string, 49);
	//strlen
	printf("\033[0;34m%-20s\033[0m|%-50lu|%-50i|", "strlen", strlen(string), ft_strlen(string));
	printf("actual_string = |%-50s|\n", string);
	printf("%-20s|%-50lu|%-50i|", "", strlen("ciao"), ft_strlen("ciao"));
	printf("actual_string = |%-50s|\n\n", "ciao");
	//strcpy
	printf("\033[0;34m%-20s\033[0m|%-50s|%-50s|", "strcpy", strcpy(dest, string), strcpy(dest, string));
	printf("actual_string = |%-50s|", string);
	printf("\033[0;32mdiff : %i\n\033[0m", strcmp(dest, string));
	printf("%-20s|%-50s|%-50s|", "", strcpy(dest, "ciao"), strcpy(dest, "ciao"));
	printf("actual_string = |%-50s|", "ciao");
	printf("\033[0;32mdiff : %i\n\033[0m\n", strcmp(dest, "ciao"));
	//strcmp
	printf("\033[0;34m%-20s\033[0m|%-50i|%-50i|", "strcmp", strcmp(dest, string), ft_strcmp(dest, string));
	printf("actual_string = |%-50s|", string);
	printf("second : %s\n", dest);
	printf("%-20s|%-50i|%-50i|", "", strcmp(string, string), ft_strcmp(string, string));
	printf("actual_string = |%-50s|", string);
	printf("second : %s\n\n", "<-same");
	print_line(210, '-', 'y');
	//write
	print_string("Write\n", 0, 'm');
	print_string("system:", 0, 'c');
	var[0] = write(1," - ", 3);
	var[1] = write(1, string, strlen(string));
	var[2] = write(1, "\n - |        a_lot_of_spaces       |",36);
	var[3] = write(1, "\n - newline", 11);
	var[4] = write(-1, "error",5);
	printf("\n\033[0;32mres1: %i, res2: %i, res3: %i, res4: %i, res_err: %i\033[0m", var[0], var[1], var[2], var[3], var[4]);
	printf("\n\n");
	print_string("mine:", 0, 'p');
	var[0] = ft_write(1, " - ",3);
	var[1] = ft_write(1, string, strlen(string));
	var[2] = ft_write(1, "\n - |        a_lot_of_spaces       |",36);
	var[3] = ft_write(1, "\n - newline", 11);
	var[4] = ft_write(-1, "error",5);
	printf("\n\033[0;32mres1: %i, res2: %i, res3: %i, res4: %i, res_err: %i\033[0m", var[0], var[1], var[2], var[3], var[4]);
	printf("\n\n");
	print_line(210, '-', 'y');
	//read
	print_string("Read:\n", 0, 'm');
	print_string("system:", 0, 'c');
	fd_s[0] = open("files_for_testing/banana.txt", 00);
	fd_s[1] = open("files_for_testing/ciao.txt", 00);
	fd_s[2] = open("files_for_testing/banana.txt", 00);
	var[0] = read(fd_s[0], buffer, 10);
	var[1] = read(fd_s[1], buffer, 15);
	var[2] = read(fd_s[2], buffer, 10);
	var[3] = read(-1, buffer, 10);
	close(fd_s[0]);
	close(fd_s[1]);
	close(fd_s[2]);
	printf("\033[0;32mres1: %i, res2: %i, res3: %i, res_err: %i\n\033[0m", var[0], var[1], var[2], var[3]);
	print_string("mine:", 0, 'p');
	fd_s[0] = open("files_for_testing/banana.txt", 00);
	fd_s[1] = open("files_for_testing/ciao.txt", 00);
	fd_s[2] = open("files_for_testing/banana.txt", 00);
	var[0] = ft_read(fd_s[0], buffer, 10);
	var[1] = ft_read(fd_s[1], buffer, 15);
	var[2] = ft_read(fd_s[2], buffer, 10);
	var[3] = ft_read(-1, buffer, 10);
	printf("\033[0;32mres1: %i, res2: %i, res3: %i, res_err: %i\n\033[0m", var[0], var[1], var[2], var[3]);
	close(fd_s[0]);
	close(fd_s[1]);
	close(fd_s[2]);
	print_line(210, '-', 'y');
	//strduup
	print_string("Strdup:\n", 0, 'm');
	print_string("system:", 0, 'c');
	printf("origin: %-50s | dest: %-50s", "ciao_come_va", strdup("ciao_come_va"));
	printf("\033[0;32mdiff : %i\n\033[0m", strcmp("ciao_come_va", strdup("ciao_come_va")));
	printf("origin: %-50s | dest: %-50s", string, strdup(string));
	printf("\033[0;32mdiff : %i\n\033[0m", strcmp(string, strdup(string)));
	print_string("mine:", 0, 'p');
	printf("origin: %-50s | dest: %-50s", "ciao_come_va", ft_strdup("ciao_come_va"));
	printf("\033[0;32mdiff : %i\n\033[0m", strcmp("ciao come va", ft_strdup("ciao come va")));
	printf("origin: %-50s | dest: %-50s", string, ft_strdup(string));
	printf("\033[0;32mdiff : %i\n\033[0m", strcmp(string, ft_strdup(string)));
	print_line(210, '-', 'y');
}
