/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/08/30 15:20:57 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	till_end(const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		/*if (buf[i] == '\n' && buf[i] == '\0')
			return (0);*/
		i++;
	}
	return (i);
}

char	*get_next_line(int fd)
{
	char	*buff;
	char	*str;
	ssize_t	size;

	buff = malloc(BUFFER_SIZE * sizeof(char));
	if (buff == NULL)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	str = malloc(BUFFER_SIZE * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (size > 0)
	{
		if (till_end(buff) != BUFFER_SIZE)
			return (str);
		str = ft_strjoin(str, buff);
		size = read(fd, buff, BUFFER_SIZE);
	}
	return (str);
}
