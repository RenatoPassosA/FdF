#include "mlx/mlx.h"
#include "fdf.h"



void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int absolute(int a)
{
    if (a < 0)
        return (a * -1);
    return (a);
}
int bigger(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

void bresenham(float x, float y, float x1, float y1, t_data *img)
{
    float x_step;
    float y_step;
    int max;

    x *= ZOOM;
    y *= ZOOM;
    x1 *= ZOOM;
    y1 *= ZOOM;

    x_step = x1 - x;
    y_step = y1 - y;
    max = bigger(absolute(x_step), absolute(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(x - x1) || (int)(y - y1))
    {
        my_mlx_pixel_put(img, x, y, 0xffffff);
        x += x_step;
        y += y_step;
    }
}

void    draw(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < data->height)
    {
        x = 0;
        while (x < data->width)
        {
            bresenham(x, y, x + 1, y, data);
            bresenham(x, y, x, y + 1, data);
            x++;
        }
        y++;
    }
}

int	display(t_data *data, fdf *map)
{
	void	*mlx;
	void	*mlx_win;
	

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF!");
	data->img = mlx_new_image(mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
								&data->endian);                        
  	draw(data);
	mlx_put_image_to_window(mlx, mlx_win, data->img, 0, 0);
	mlx_loop(mlx);
    return (0);
}

