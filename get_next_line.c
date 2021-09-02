/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/02 19:11:53 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_chars(char *buff, char *str)
{
	char	*concat;

	concat = ft_strjoin(str, buff);
	free(str);
	str = ft_strdup(concat);
	free(concat);
	return (str);
}

/*
* buff -> string que acaba de leer del fichero
* str -> string anterior a buff actual
* concat -> union de str y buff
* str_fnl -> la ultima concat
* size -> el numero de caracteres que ha leido (puede ser distinto a BUFFER_SIZE)
*/
char	*get_next_line(int fd)
{
	char	buff[BUFFER_SIZE + 1];
	char	*str;
	char	*str_fnl;
	ssize_t	size;

	size = read(fd, buff, BUFFER_SIZE);
	buff[size] = '\0';
	if (fd == 2 || size == 0)
		return (NULL);
	str = ft_strjoin("", buff);
	while (size > 0)
	{
		size = read(fd, buff, BUFFER_SIZE);
		str = join_chars(buff, str);
	}
	str_fnl = str;
	free(str);
	return (str_fnl);
}
