#include "fdf.h"
#include "get_next_line.h"

char *check_color(char *z)
{
    char *color;
    int index;

    index = 0;
    color = "0xffffff";
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

fdf *set_node(int *index, char *z_content, int *total_index, int *yaxis)
{
    fdf *node;
    char *color;

    color = check_color(z_content);
    node = lst_new(*index, ft_atol(z_content), *total_index, color);
    node->y = *yaxis;
    (*total_index)++;
    (*index)++;
    return (node);
}

fdf *parse_line(char *line, fdf *data, int yaxis, int *total_index)
{
    char **z_content;
    int index;
    fdf *current;
    fdf *new_node;
    
    index = 0;
    z_content = ft_split(line, ' ');
    if (!data)
        data = set_node(&index, z_content[index], total_index, &yaxis);
    current = data;
    while (current->next != NULL)
        current = current->next;
    while (z_content[index] != NULL)
    {
        new_node = set_node(&index, z_content[index], total_index, &yaxis);
        current->next = new_node;
        current = current->next;
    }
    free(z_content);
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
        yaxis++; //aqui tenho o y maximo
    }
    close(fd);
    return (data);
}

int main(int ac, char **av)
{
    fdf *data;
    fdf *current;
    int width;
    int height;

    data = NULL;
    if (ac != 2)
    {
        printf("Error");
        return (0);
    }
    data = read_map(av[1], data);
    current = data;
    while(current->next != NULL)
        current = current->next;
    width = current->y;
    height = current->x;
    display(width, height);
  
   

    
   return (0);

}

/* while(data)
    {
        printf("%3d", data->z);
        if (data->next && data->next->y > data->y)
            printf("\n");
        data = data->next;  
    }
	while(data)
	{
		printf("x: %d\n", data->x);
		printf("y: %d\n", data->y);
		printf("z: %d\n", data->z);
		printf("index: %d\n", data->index);
		printf("color: %s\n", data->color);
		printf("----------------------\n");
		data = data->next;
	}*/