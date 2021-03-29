#ifndef ASM_H
# define ASM_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

extern	int		ft_strlen(char *);
extern	char	*ft_strcpy(char *, char *);
extern	int		ft_strcmp(char *, char *);
extern	int		ft_write(int, char *, int);
extern	int		ft_read(int, void *, size_t);

#endif