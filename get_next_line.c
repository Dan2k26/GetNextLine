/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/18 20:49:43 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}

static char	*assign_chars(char *aux)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = -1;
	while (aux[i] != '\n' && aux[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL && aux == NULL)
		return (NULL);
	i = i + 1;
	while (++y < i)
		str[y] = aux[y];
	str[i] = '\0';
	return (str);
}

static char	*read_line(int size, int fd, char *buff, char **str)
{
	char	*aux;

	while (size > 0)
	{
		buff[size] = '\0';
		aux = *str;
		*str = ft_strjoin(aux, buff);
		free(aux);
		if (ft_strchr(*str, '\n') != NULL)
			break ;
		size = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (*str);
}

static char	*check_next_line(char **str, char **remainder)
{
	char	*aux;

	if (ft_strchr(*str, '\n') != NULL)
	{
		aux = *remainder;
		*remainder = ft_strdup(ft_strchr(*str, '\n') + 1);
		free(aux);
	}
	aux = *str;
	*str = assign_chars(aux);
	free(aux);
	return (*str);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*str;
	static char	*remainder;
	ssize_t		size;

	buff = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (read(fd, buff, 0) == -1 || BUFFER_SIZE < 1)
	{
		free(buff);
		return (NULL);
	}
	size = read(fd, buff, BUFFER_SIZE);
	if (!remainder)
		remainder = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (size == 0 && remainder[0] == '\0')
	{
		free(remainder);
		free(buff);
		remainder = NULL;
		return (NULL);
	}
	str = ft_strdup((char *)remainder);
	ft_bzero(remainder, sizeof(remainder));
	str = read_line(size, fd, buff, &str);
	return (check_next_line(&str, &remainder));
}
