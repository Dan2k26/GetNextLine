/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/08 16:51:13 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*COpia hasta un salto de linea, con este incluido*/
/*static char	*till_newline(char *buff)
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

static char	*rest_of_chars(char *aux)
{
	char	*pos;
	char	*str;

	if (ft_strchr(aux, '\n') != NULL)
	{
		pos = ft_strchr(aux, '\n') + 1;
		str = malloc(ft_strlen(pos) + 1);
		ft_memcpy(str, pos, ft_strlen(pos));
	}
	return (str);
}*/

/*static char	*assign_chars(char *aux)
{
	int		i;
	char	*str;
	
	i = 0;
	//da los valores hasta el salto de linea
	while (aux[i] != '\n' && aux[i])
		i++;
	str = malloc(sizeof(char) * i + 2);
	ft_memcpy(str, aux, i + 1);
	str[i + 2] = '\0';
	return (str);
}*/

static char *read_line(int size, int fd, char *buff, char **str)
{
	char	*aux;

	while (size > 0)
	{
		//Concatenar la linea actual con la anterior
		aux = *str;
		*str = ft_strjoin(aux, buff);
		free(aux);
		//Comprueba el salto de linea
		//Si hay salto de linea, salimos del bucle
		if (ft_strchr(*str, '\n') != NULL)
			break ;
		//Si no sigue leyendo
		size = read(fd, buff, BUFFER_SIZE);
		buff[size] = '\0';
	}
	return (*str);
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
	//char		*aux;
	static char	*remainder;
	ssize_t		size;
//1- Comprobar errores de fichero
	if (read(fd, buff, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
//2- Leer y comprobar que no da error 
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0)
		return (NULL);
	buff[size] = '\0';
//3- Si no hay temp inicializo str
	if (!remainder)
		str = ft_strdup("");
	else
	{
		str = ft_strdup(remainder);
		free(remainder);
	}
//4- Bucle de lectura
	//paso por referencia str, que es la que puede tener un resultado u otro
	str = read_line(size, fd, buff, &str);
//5- Si tiene salto de linea guardar el temp lo sobrante
	// LEAKS
	/*if (ft_strchr(str, '\n') != NULL)
		remainder = ft_strdup(ft_strchr(str, '\n') + 1);*/
//6- Si existe temp
	/*if (remainder)
	{
		aux = str;
		str = assign_chars(aux);
		free(aux);
	}
	else if (!remainder)
	{
		aux = ft_strdup(remainder);
		free(remainder);
		return (aux);
	}*/
	return (str);
}
