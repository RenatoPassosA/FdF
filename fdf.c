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

fdf *set_node(int *index, char *z_content, int *total_index)
{
    fdf *node;
    char *color;

    color = check_color(z_content);
    node = lst_new(ft_atol(z_content), *total_index, color);
    (*total_index)++;
    (*index)++;
    return (node);
}

fdf *parse_line(char *line, fdf *data, int *total_index)
{
    char **z_content;
    int index;
    fdf *current;
    fdf *new_node;
    
    index = 0;
    z_content = ft_split(line, ' ');
    if (!data)
        data = set_node(&index, z_content[index], total_index);
    current = data;
    while (current->next != NULL)
        current = current->next;
    while (z_content[index] != NULL)
    {
        new_node = set_node(&index, z_content[index], total_index);
        current->next = new_node;
        current = current->next;
    }
    free(z_content);
    return (data);
}

fdf *read_map(char *file, fdf *map, t_data *data)
{
    int fd;
    char *line;
    int yaxis;
    int total_index;
    int xaxis;

    yaxis = 0;
    total_index = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (NULL);
    while ((line = get_next_line(fd)) != NULL)
    {
        map = parse_line(line, map, &total_index);
        xaxis = count_words(line, ' ');
        free(line);
        yaxis++;
    }
    close(fd);
    data->height = yaxis;
    data->width = xaxis;
    return (map);
}

int main(int ac, char **av)
{
    fdf *map;
    t_data data;

    map = NULL;
    if (ac != 2)
    {
        printf("Error");
        return (0);
    }
    map = read_map(av[1], map, &data);
    
   /* int counter = 0;
    while(map)
        {
            printf("%3d", map->z);
            counter++;
            if (counter == data.height)
                {
                    printf("\n");
                    counter = 0;
                }
                map = map->next;
        }*/
   

    display(&data, map);
  
   

    
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