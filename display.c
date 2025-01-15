#include "mlx/mlx.h"
#include "fdf.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


void draw_line(fdf *data, t_data *img)
{
    int dx;
    int dy;
    int step;
    int stepx = 0;
    int stepy = 0;
    int i = 0;

    dx = data->next->x - data->x;
    dx = data->next->y - data->y;

    step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    if (step != 0)
    {
        stepx = dx / step;
        stepy = dy / step;
    }
    while (i != step + 1)
    {

        my_mlx_pixel_put(img, (data->x + i * stepx), (data->y + 1 * stepy), (long)data->color);
        i++;
    }
  /*
    if (data->next && data->next->x && data->y < data->next->y)
    {
        dx = data->next->x - data->x;
        dy = data->next->y - data->y;

    }*/







    //my_mlx_pixel_put(img, 5, 5, 0x00FF0000);
}

int	display(fdf *data)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

   if (data->next && data->next->x && data->y < data->next->y)
    {
        draw_line(data, &img);
        data = data->next

    }

	
    
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
    return (0);
}