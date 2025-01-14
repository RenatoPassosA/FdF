#include "fdf.h"
#include "get_next_line.h"


char *check_color(char *z)
{
    char *color;
    int index;

    index = 0;
    if (!ft_strchr(z, ','))
        color = "0xFFFFFF";
    else
    {
        while(z[index] != ',')
            index++;
        color = ft_substr(z, index, ft_strlen(z) - index);
    }
    return (color);


}

fdf *parse_line(char *line, fdf *data, int yaxis, int *total_index)
{
    char **z_content;
    int index;
    char *color;

    index = 0;
    z_content = ft_split(line, ' ');
    while (z_content[index] != NULL)
    {
        color = check_color(z_content[index]);
        data = lst_new(index, ft_atol(z_content[index]), &total_index, color);
        data->y = yaxis;
        total_index++;
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
    int *total_index;

    yaxis = 0;
    total_index = 0;
    fd = open(map, O_RDONLY);
    if (fd == -1)
        return ;
    while ((line = get_next_line(fd)) != NULL)
    {
        data = parse_line(line, data, yaxis, &total_index);
        printf("VISUALIZAÇÃO:%s", line);
        free(line);
        yaxis++;
    }
    close(fd);
    return (data);
}

int main(int ac, char **av)
{
    fdf *data;

    if (ac != 2)
    {
        printf("Error");
        return (0);
    }
    data = read_map(av[1], data);
    printf("%s", data->z);
    return (0);


}