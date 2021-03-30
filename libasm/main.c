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

int		main(void)
{
	char	string[50];
	char	dest[50];
	int		var[10];
	int		fd_s[10];
	char	buffer[100];

	system("clear");
	//header
	printf("%.210d\n",0);
	printf("%-20s%-50s%-50s\n", "", "system", "mine");
	rand_string(string, 49);
	//strlen
	printf("%-20s|%-50lu|%-50i|", "strlen", strlen(string), ft_strlen(string));
	printf("actual_string = |%-50s|\n", string);
	printf("%-20s|%-50lu|%-50i|", "", strlen("ciao"), ft_strlen("ciao"));
	printf("actual_string = |%-50s|\n\n", "ciao");
	//strcpy
	printf("%-20s|%-50s|%-50s|", "strcpy", strcpy(dest, string), strcpy(dest, string));
	printf("actual_string = |%-50s|", string);
	printf("diff : %i\n", strcmp(dest, string));
	printf("%-20s|%-50s|%-50s|", "", strcpy(dest, "ciao"), strcpy(dest, "ciao"));
	printf("actual_string = |%-50s|", "ciao");
	printf("diff : %i\n\n", strcmp(dest, "ciao"));
	//strcmp
	printf("%-20s|%-50i|%-50i|", "strcmp", strcmp(dest, string), ft_strcmp(dest, string));
	printf("actual_string = |%-50s|", string);
	printf("second : %s\n", dest);
	printf("%-20s|%-50i|%-50i|", "", strcmp(string, string), ft_strcmp(string, string));
	printf("actual_string = |%-50s|", string);
	printf("second : %s\n\n", "<-same");
	printf("%.210d\n",0);
	//write
	printf("%s\n", "Write:");
	printf("%-20s\n", "system:");
	var[0] = write(1," - ", 3);
	var[1] = write(1, string, strlen(string));
	var[2] = write(1, "\n - |        a_lot_of_spaces       |",36);
	var[3] = write(1, "\n - newline", 11);
	var[4] = write(-1, "error",5);
	printf("\nres1: %i, res2: %i, res3: %i, res4: %i, res_err: %i", var[0], var[1], var[2], var[3], var[4]);
	printf("\n\n");
	printf("%-20s\n", "mine:");
	var[0] = ft_write(1, " - ",3);
	var[1] = ft_write(1, string, strlen(string));
	var[2] = ft_write(1, "\n - |        a_lot_of_spaces       |",36);
	var[3] = ft_write(1, "\n - newline", 11);
	var[4] = ft_write(-1, "error",5);
	printf("\nres1: %i, res2: %i, res3: %i, res4: %i, res_err: %i", var[0], var[1], var[2], var[3], var[4]);
	printf("\n\n");
	printf("%.210d\n",0);
	printf("%s\n", "Read:");
	printf("%-20s\n", "system:");
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
	printf("res1: %i, res2: %i, res3: %i, res_err: %i\n", var[0], var[1], var[2], var[3]);
	printf("%-20s\n", "mine:");
	fd_s[0] = open("files_for_testing/banana.txt", 00);
	fd_s[1] = open("files_for_testing/ciao.txt", 00);
	fd_s[2] = open("files_for_testing/banana.txt", 00);
	var[0] = ft_read(fd_s[0], buffer, 10);
	var[1] = ft_read(fd_s[1], buffer, 15);
	var[2] = ft_read(fd_s[2], buffer, 10);
	var[3] = ft_read(-1, buffer, 10);
	printf("res1: %i, res2: %i, res3: %i, res_err: %i\n", var[0], var[1], var[2], var[3]);
	close(fd_s[0]);
	close(fd_s[1]);
	close(fd_s[2]);
	printf("\n%.210d\n",0);
	printf("%s\n", "Strdup:");
	printf("%-20s\n", "system:");
	printf("origin: %-50s | dest: %-50s", "ciao_come_va", strdup("ciao_come_va"));
	printf("diff : %i\n", strcmp("ciao_come_va", strdup("ciao_come_va")));
	printf("origin: %-50s | dest: %-50s", string, strdup(string));
	printf("diff : %i\n", strcmp(string, strdup(string)));
	printf("%-20s\n", "mine:");
	printf("origin: %-50s | dest: %-50s", "ciao_come_va", ft_strdup("ciao_come_va"));
	printf("diff : %i\n", strcmp("ciao come va", ft_strdup("ciao come va")));
	printf("origin: %-50s | dest: %-50s", string, ft_strdup(string));
	printf("diff : %i\n", strcmp(string, ft_strdup(string)));
	printf("\n%.210d\n",0);
}
