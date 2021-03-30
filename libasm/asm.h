#ifndef ASM_H
# define ASM_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_strlen(char *);
char	*ft_strcpy(char *, char *);
int		ft_strcmp(char *, char *);
int		ft_write(int, char *, int);
int		ft_read(int, void *, size_t);
char	*ft_strdup(char *);

#endif