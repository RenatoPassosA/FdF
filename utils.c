#include "fdf.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str && str[counter] != '\0')
		counter++;
	return (counter);
}

fdf	*lst_new(int z_value, int total_index, char *color)
{
	fdf	*node;

	node = (fdf *)malloc(sizeof(fdf));
	if (!node)
		return (NULL);
	node->z = z_value;
    node->index = total_index;
    node->color = color;
	node->next = NULL;
	return (node);
}

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	a;
	unsigned char	*ptr;
	size_t			index;

	index = 0;
	a = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (index < n)
	{
		ptr[index] = a;
		index++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((nmemb * size) % nmemb)
		return (NULL);
	arr = (void *)malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_memset(arr, 0, nmemb * size);
	return (arr);
}



long	ft_atol(char *s)
{
	int			minus_sign;
	long int	result;

	minus_sign = 0;
	result = 0;
	while (*s)
	{
		while (*s == 32 || (*s >= 9 && *s <= 13))
			s++;
		if (*s == '+' || *s == '-')
		{
			if (*s == '-')
				minus_sign = 1;
			s++;
		}
		while (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
			s++;
		}
		if (minus_sign)
			return (result * -1);
		return (result);
	}
	return (0);
}