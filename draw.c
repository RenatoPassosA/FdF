#include "mlx/mlx.h"
#include "fdf.h"



void	my_mlx_pixel_put(t_data data, int x, int y, int color)
{
	char	*dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
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

void bresenham(float x, float y, float x1, float y1, t_data img)
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

void    draw(t_data img, int width, int height)
{
    int x;
    int y;

    y = 0;
    while (y < width)
    {
        x = 0;
        while (x < height)
        {
            bresenham(x, y, x + 1, y, img);
            bresenham(x, y, x, y + 1, img);
            x++;
        }
        y++;
    }
}

int	display(int width, int height)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
   
                                
  	draw(img, width, height);
    
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
    return (0);
}