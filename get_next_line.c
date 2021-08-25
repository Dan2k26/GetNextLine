/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:58:04 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/08/25 20:49:56 by dlerma-c         ###   ########.fr       */
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
	char	*buff;
	ssize_t	size;

	if (!(buff = malloc(BUFFER_SIZE * sizeof(char))))
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	printf("SIZE: %zd", size);
	printf("SIZE: %d", till_end(buff));
	/*while (buff[BUFFER_SIZE -1] != '\n')
	{
		str = ft_strjoin(str, buff);
		read(fd, buff, BUFFER_SIZE);
	}*/
	return (buff);
}
