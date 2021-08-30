/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/08/30 16:53:55 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	till_end(const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*str;
	ssize_t		size;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	str = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	while (size > 0)
	{
/*Se podria pasar al join hasta una posicion, y no que coie todo
str lo tiene que tener guaradado para el resto de veces que entre en el bucle
llamadoo por el main*/
		str = ft_strjoin(str, buff);
		if (till_end(buff) != BUFFER_SIZE)
		{
			free(buff);
			return (str);
		}
		size = read(fd, buff, BUFFER_SIZE);
		free(str);
	}
	free(buff);
	return (str);
}
