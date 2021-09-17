/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/17 21:51:03 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*assign_chars(char *aux)
{
	int		i;
	char	*str;

	i = 0;
	while (aux[i] != '\n' && aux[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1);
	ft_memcpy(str, aux, i + 1);
	str[i + 1] = '\0';
	return (str);
}

static void	clean_chr(void *s, size_t n)
{
	unsigned int		i;
	char				*str;

	i = -1;
	str = (char *) s;
	while (++i < n)
		str[i] = 0;
}

static char	*read_line(int size, int fd, char *buff, char **str)
{
	char	*aux;

	while (size > 0)
	{
		aux = *str;
		*str = ft_strjoin(aux, buff);
		free(aux);
		if (ft_strchr(*str, '\n') != NULL)
			break ;
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (*str);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	static char	*remainder;
	char		*aux;
	ssize_t		size;

	if (read(fd, buff, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (!remainder)
		remainder = calloc(sizeof(char), BUFFER_SIZE);
	if (size == 0 && remainder[0] == '\0')
		return (NULL);
	buff[size] = '\0';
	str = ft_strdup((char *)remainder);
	clean_chr(remainder, sizeof(remainder));
	str = read_line(size, fd, buff, &str);
	if (ft_strchr(str, '\n') != NULL)
	{
		aux = remainder;
		remainder = ft_strdup(ft_strchr(str, '\n') + 1);
		free(aux);
	}
	aux = str;
	str = assign_chars(aux);
	free(aux);
	return (str);
}
