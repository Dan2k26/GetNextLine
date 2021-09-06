/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/06 18:21:52 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*COpia hasta un salto de linea, con este incluido*/
static char *till_newline(char *buff)
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
	char		*aux_temp;
	static char	*temp;
	ssize_t		size;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0)
		return (NULL);
	buff[size] = '\0';
	//depende si es la primera vez qeu pasa o no  
	if (temp)
		str = ft_strdup(temp);
	else
		str = ft_strdup("");
	while (size > 0)
	{
		//encuentra la posicion de salto de linea
		aux_temp = ft_strchr(buff, '\n');
		//si hay un salto de linea
		if (aux_temp != NULL)
		{
		//le añado uno para que parta del siguiente
			aux_temp++;
			temp = ft_strdup(aux_temp);
			aux = str;
			str = ft_strjoin(str, till_newline(buff));
			free(aux);
			return (str);
		}
		aux = str;
		str = ft_strjoin(str, till_newline(buff));
		free(aux);
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (str);
}
