/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/06 19:07:34 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*COpia hasta un salto de linea, con este incluido*/
static char	*till_newline(char *buff)
{
	char	*str;
	char	*aux;
	int		i;

	i = 0;
	while (buff[i] != '\n' && buff[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	aux = str;
	ft_memcpy(str, buff, i + 1);
	return (str);
}

static char	*add_new_line(char *str, char *buff)
{
	char	*aux;
	char	*s;

	s = "";
	aux = s;
	s = ft_strjoin(str, till_newline(buff));
	return (s);
}

static char	*conditions(char *temp)
{
	char	*str;

	if (temp)
		str = ft_strdup(temp);
	else
		str = ft_strdup("");
	return (str);
}

/*
* buff -> string que acaba de leer del fichero
* str -> linea que tiene que devolver
* aux -> apoyo a str
* temp -> lo que sobra despues de un salto de linea
* size -> el numero de caracteres que ha leido (puede ser distinto a BUFFER_SIZE)
*/
char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	static char	*temp;
	ssize_t		size;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0)
		return (NULL);
	buff[size] = '\0';
	str = conditions(temp);
	while (size > 0)
	{
		if (ft_strchr(buff, '\n') != NULL)
		{
			temp = ft_strdup(ft_strchr(buff, '\n') + 1);
			return (add_new_line(str, buff));
		}
		str = add_new_line(str, buff);
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (str);
}
