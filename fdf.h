#ifndef FDF_H
# define FDF_H

#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#define ZOOM 30

/*
#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 20   // Scale factor to size the grid on the screen
*/
typedef struct fdf
{
    int y;
    int x;
    int z;
    int index;
    char *color;
    struct fdf *next;    
} fdf;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    struct fdf *data;
}				t_data;

char		**ft_split(char const *s, char c);
int	count_words(char *s, char c);
long	ft_atol(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
fdf	*lst_new(int xaxis, int z_value, int total_index, char *color);
size_t	ft_strlen(const char *str);
int	display(int width, int height);


#endif
