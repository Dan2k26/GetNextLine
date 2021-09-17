/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/17 19:28:30 by dlerma-c         ###   ########.fr       */
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
	str = calloc(sizeof(char), i);
	ft_memcpy(str, aux, i + 1);
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

static char	*read_line(int fd, char *buff, char **str)
{
	char	*aux;
	ssize_t	size;

	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0 && buff == NULL)
		return (NULL);
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
	static char	*buff;
	char		*str;
	char		*aux;

	if (!buff)
	{
		buff = calloc(sizeof(char), BUFFER_SIZE + 1);
		if (buff == NULL)
			return (NULL);
		buff[BUFFER_SIZE] = '\0';
	}
	if (read(fd, buff, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
	if (ft_strchr(buff, '\n') != NULL)
	{
		str = assign_chars(buff);
		buff = ft_strchr(buff, '\n') + 1;
		return(str);
	}
	str = ft_strdup(buff);
	str = read_line(fd, buff, &str);
	if (str != NULL)
	{
		aux = str;
		str = assign_chars(aux);
		//free(aux);
		buff = ft_strchr(buff, '\n') + 1;
		return(str);
	}



	/*if (size == 0 && remainder[0] == '\0')
		return (NULL);
	buff[size] = '\0';
	str = ft_strdup((char *)remainder);
	clean_chr(remainder, sizeof(remainder));
	if (ft_strchr(str, '\n') != NULL)
		ft_memcpy((char *)remainder, ft_strchr(str, '\n') + 1,
			ft_strlen(ft_strchr(str, '\n')));
	aux = str;
	str = assign_chars(aux);
	free(aux);*/
	return (NULL);
}