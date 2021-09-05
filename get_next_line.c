/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/05 17:57:20 by dlerma-c         ###   ########.fr       */
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
	//free(str);
	return (concat);
}


/*
* devuelve la linea con el salto de linea
* str = la copia hasta el salto de linea con ese incluido 
* aux = lo que devuelve
*/
static char	*char_nextline(char *buff)
{
	int		i;
	char	*str;
	char	*aux;

	i = 0;
	//cuenta en que posicion esta el salto de linea
	while (buff[i] && buff[i] != '\n')
		i++;
	str = malloc(i + 1 * sizeof(char));
	aux = str;
	str = ft_memcpy(str, buff, i + 1);
	free (str);
	return (aux);
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
	static char	buff[BUFFER_SIZE + 1];
	char		*str;
	char		*aux;
	static char	*temp;
	ssize_t		size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0)
		return (NULL);
	buff[size] = '\0';
	str = NULL;
	aux = str;
	str = ft_strdup(buff);
	free(str);
	while (size > 0)
	{
		//si el primer elemento de la cadena es una salto de linea
		if (str[0] == '\n')
			return ("\n");
		//unir temp con  str o buff con str
		if (temp)
		{
			aux = str;
			//unimos str detras de temp
			str = join_chars(aux, temp + 1);
			free(str);
		}
		//si en la linea hay un salto de linea 
		if (ft_strchr(str, '\n') != NULL)
		{
			temp = ft_strchr(str, '\n');
			return (char_nextline(str));
		}
		else if(!temp)
		{
			aux = str;
			//unimos buff detras de str
			str = join_chars(buff, aux);
			free(str);
		}
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (aux);
}
