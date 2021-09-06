/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/06 16:50:44 by dlerma-c         ###   ########.fr       */
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
/*
* comprueba si hay un salto de linea en la primera posicion
* y si no la hay te la añade a la cadena
*/
static char *check_nextline(char *aux_temp, char *buff, char *str)
{
	char	*aux;
	char	*s;
	int 	i;

	if (buff[0] == '\n')
		return (join_chars("\n", str));
	i = ft_strlen(buff) - ft_strlen(aux_temp);
	aux = malloc(sizeof(char) * i + 1);
	s = ft_memcpy(aux, buff, i);
	str = join_chars(s, str);
	free(aux);
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
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	static char	*temp;
	char		*aux_temp;
	ssize_t		size;

	if (fd < 0 || read(fd, buff, 0) == -1)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	//depende si es la primera vez qeu pasa o no  
	if (size == 0)
			return (NULL);
	buff[size] = '\0';
	if (temp)
		str = ft_strjoin(temp, buff);
	else
	{
		str = ft_strdup("");
		str = join_chars(buff, str);
	}
	while (size > 0)
	{
		//encuentra la posicion de salto de linea
		aux_temp = ft_strchr(buff, '\n');
		//le añado uno para que parta del siguiente
		if (aux_temp != NULL)
		{
			aux_temp++;
			str = check_nextline(aux_temp, buff, str);
			temp = ft_strdup(aux_temp);
			return (str);
		}
		if (!ft_strncmp(str, "", sizeof(str)))
			str = join_chars(buff, str);
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (str);
}
