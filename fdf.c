#include "fdf.h"
#include "get_next_line.h"

char *check_color(char *z)
{
    char *color;
    int index;

    index = 0;
    color = "0xFFFFFF";
    if (!ft_strchr(z, ','))
        color = ft_substr(color, 0, ft_strlen(color));
    else
    {
        while(z[index] != ',')
            index++;
        color = ft_substr(z, index + 1, ft_strlen(z) - index - 1);
    }
    return (color);
}

fdf *parse_line(char *line, fdf *data, int yaxis, int *total_index) //NÃO ESTÁ RETORNANDO A LISTA CORRETAMENTE PARA A FUNÇÃO SUPERIOR
{
    char **z_content;
    int index;
    char *color;
    
    index = 0;
    z_content = ft_split(line, ' ');
    while (z_content[index] != NULL)
    {
        color = check_color(z_content[index]);
        data = lst_new(index, ft_atol(z_content[index]), *total_index, color);
        data->y = yaxis;
        (*total_index)++;
        index++;
        data = data->next;
    }
    return (data);
}


fdf *read_map(char *map, fdf *data)
{
    int fd;
    char *line;
    int yaxis;
    int total_index;

    yaxis = 0;
    total_index = 0;
    fd = open(map, O_RDONLY);
    if (fd == -1)
        return (NULL);
    while ((line = get_next_line(fd)) != NULL)
    {
        data = parse_line(line, data, yaxis, &total_index);
        free(line);
        yaxis++;
    }
    close(fd);
    return (data);
}

int main(int ac, char **av)
{
    fdf *data;

    data = NULL;
    if (ac != 2)
    {
        printf("Error");
        return (0);
    }
    data = read_map(av[1], data);

	/*while(data)
	{
		printf("x: %d\n", data->x);
		printf("y: %d\n", data->y);
		printf("z: %d\n", data->z);
		printf("index: %d\n", data->index);
		printf("color: %s\n", data->color);
		printf("----------------------");
		data = data->next;
	}*/



    return (0);


}


/*if (!data)
            data = current;
        else
            current->next = data;
        current = data;*/
