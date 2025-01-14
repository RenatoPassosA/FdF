#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>

typedef struct fdf
{
    int x;
    int y;
    int z;
    int index;
    char color;
    struct fdf *next;    
} fdf;

char		**ft_split(char const *s, char c);
long	ft_atol(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
fdf	*lst_new(int xaxis, int z_value, int total_index, char color);
size_t	ft_strlen(const char *str);


#endif