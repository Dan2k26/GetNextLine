/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/05 21:43:08 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
* Junta las dos cadenas y crea un nuevo espacio con el tamaño de
* la cadena concatenada y la devuelve para poder devolverla.
*/
static char	*join_chars(char *buff, char *str)
{
	char	*concat;

	concat = ft_strjoin(str, buff);
	free(str);
	return (concat);
}

/*static char *till_newline(char *buff)
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
}*/

/*
* buff -> string que acaba de leer del fichero
* str -> string anterior a buff actual
* concat -> union de str y buff
* str_fnl -> la ultima concat
* size -> el numero de caracteres que ha leido (puede ser distinto a BUFFER_SIZE)
*/
char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	char		*str_fnl;
	static char	*temp;
	ssize_t	size;
	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0)
		return (NULL);
	buff[size] = '\0';
	//depende si es la primera vez qeu pasa o no  
	if (temp)
		str = ft_strjoin(temp, buff);
	else
		str = ft_strdup("");
	while (size > 0)
	{
		//encuentra la posicion de salto de linea
		temp = ft_strchr(buff, '\n');
		//le añado uno para que parta del siguiente
		temp++;
		//si hay un salto de linea
		if (temp != NULL)
		{
			str_fnl = str;
			str = join_chars(buff, str);
			//free(str_fnl); //libera cuando no hay nada
			return (str);
		}
		str_fnl = str;
		str = join_chars(buff, str);
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (str);
}
