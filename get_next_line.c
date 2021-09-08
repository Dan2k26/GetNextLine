/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/08 20:32:32 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*assign_chars(char *aux)
{
	int		i;
	char	*str;
	
	i = 0;
	//da los valores hasta el salto de linea
	while (aux[i] != '\n' && aux[i])
		i++;
	str = malloc(sizeof(char) * i + 1);
	ft_memcpy(str, aux, i + 1);
	str[i + 1] = '\0';
	return (str);
}

static char	*read_line(int size, int fd, char *buff, char **str)
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

static void	ft_bzero(void *s, size_t n)
{
	unsigned int		i;
	char				*str;

	i = -1;
	str = (char *) s;
	while (++i < n)
		str[i] = 0;
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
	static char	remainder[BUFFER_SIZE + 1];
	char		*aux;
	ssize_t		size;
//1- Comprobar errores de fichero
	if (read(fd, buff, 0) == -1 || BUFFER_SIZE < 1)
		return (NULL);
//2- Leer y comprobar que no da error 
	size = read(fd, buff, BUFFER_SIZE);
	if (size == 0 && remainder[0] == '\0')
		return (NULL);
	buff[size] = '\0';
//3- La estatica ya esta inicializada
	str = ft_strdup((char *)remainder);
	ft_bzero(remainder, sizeof(remainder));
//4- Bucle de lectura
	//paso por referencia str, que es la que puede tener un resultado u otro
	str = read_line(size, fd, buff, &str);
//5- Si tiene salto de linea guardar el temp lo sobrante
	// LEAKS
	if (ft_strchr(str, '\n') != NULL)
	{
		ft_memcpy((char *)remainder, ft_strchr(str, '\n') + 1,
			ft_strlen(ft_strchr(str, '\n') + 1));
		remainder[ft_strlen(remainder) ] = '\0';
	}
//6- Si existe str, se le asignan os caracteres antes del salto de linea
	if (str)
	{
		aux = str;
		str = assign_chars(aux);
		free(aux);
	}
	///NO ENTRA
	else
	{
		aux = str;
		str = ft_strdup((char *)remainder);
		free(aux);
		ft_bzero(remainder, sizeof(remainder));
	}
	return (str);
}
