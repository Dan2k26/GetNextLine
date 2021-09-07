/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/07 15:31:30 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*COpia hasta un salto de linea, con este incluido*/
static char	*till_newline(char *buff)
{
	char	*str;
	int		i;

	i = 0;
	while (buff[i] != '\n' && buff[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	ft_memcpy(str, buff, i + 1);
	return (str);
}

static char	*add_new_line(char *str, char *buff)
{
	char	*s;
	char	*str_newline;

	str_newline = till_newline(buff);
	s = ft_strjoin(str, str_newline);
	free(str_newline);
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
	char		*aux;
	static char	*temp;
	ssize_t		size;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0 && !temp)
		return (NULL);
	buff[size] = '\0';
	str = conditions(temp);
	while (size > 0) //si temp sigue existiendo, no entra
	{
		if (ft_strchr(buff, '\n') != NULL)
		{
			temp = ft_strdup(ft_strchr(buff, '\n') + 1);
			aux = str;
			str = add_new_line(aux, buff);
			free(aux);
			return (str);
		}
		aux = str;
		str = add_new_line(aux, buff);
		free(aux);
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	//si temp existe y el fichero ha terminado de leer
	if (buff[0] != '\0' && ((temp[0] != '\0') && size == 0))
	{
		aux = temp;
		str = till_newline(aux);
		temp = ft_strdup(ft_strchr(aux, '\n') + 1);
		free(aux);
		return (str);
	}
	else if (buff[0] != '\0' && (temp[0] == '\0' && size == 0))
		return (NULL);
	return (str);
}
