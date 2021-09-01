/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 14:09:52 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/01 20:40:15 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*Cuenta los caracteres antes de un salto de linea*/
static int	till_end(const char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	return (i);
}

/*
Une las dos cadenas pero hasta la posicon que  dice size y le pone 
un final de linea o un nulll dependiendo del carracter mandado
*/
static char	*join_char(char const *s1, char const *s2, int size)
{
	char	*str;
	int		y;
	int		i;

	i = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	//sumo a largura de s1 y el size
	str = (char *)malloc(ft_strlen(s1) + size + 2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	y = -1;
	while (s2[++y] && y < size)
		str[i++] = s2[y];
	str[++i] = '\0';
	return (str);
}
/*Copia a partir del salto de linea*/
static char	*copy_rest(char *buff, int size)
{
	char	*aux;
	int		i;

	i = 0;
	//avanza buffer hasta la posicion de sato de linea incluida
	while (i <= size)
	{
		buff++;
		i++;
	}
	i = 0;
	aux = malloc(ft_strlen(buff) + 1 * sizeof(char));
	while (buff[i])
	{
		aux[i] = buff[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*str;
	char		*temp;
	static char	*aux;
	ssize_t		size;

	size = read(fd, buff, BUFFER_SIZE);
	buff[size] = '\0';
	str = "";
	if (size == 0 || fd == 0)
		return (NULL);
	if (aux)
	{
		str = join_char(aux, "", 0);
		free(aux);
	}
	while (size > 0)
	{
		//si buffer tiene un salto de linea
		if (ft_strchr(buff, '\n') != NULL)
		{
			size = till_end(buff);
			aux = copy_rest(buff, size );
			//si aux vale \n se incuye dos veces
			temp = join_char(str, buff, size + 1);
			str = ft_strdup(temp);
			free(temp);
			return (str);
		}
		temp = join_char(str, buff, size);
		str = ft_strdup(temp);
		size = read(fd, buff, BUFFER_SIZE);
		free(temp);
	}
	return (str);
}
