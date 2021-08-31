/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/08/31 20:50:47 by dlerma-c         ###   ########.fr       */
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

static void	assign_rest(char *buff, char *temp, int pos)
{
	int	i;

	i = 0;
	while (buff[pos])
	{
		temp[i] = buff[pos];
		pos++;
		i++;
	}
	temp[i] = '\0';
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	char		*temp;
	ssize_t		size;

	size = read(fd, buff, BUFFER_SIZE);
	str = "";
	while (size > 0)
	{
		buff[BUFFER_SIZE] = '\0';
		temp = ft_strjoin(str, buff);
		str = ft_strdup(temp);
		/*Revisar la funcion till end porque ya no cuenta hastta que hay un final
		hay que fiarse del size. Empieza a utilizar posiciones*/
		if (till_end(buff) != BUFFER_SIZE)
		{
			assign_rest(buff, temp, till_end(buff) + 1);
			return (str);
		}
		size = read(fd, buff, BUFFER_SIZE);
		free(str);
	}
//	free(str);
	getchar();
	return (str);
}
