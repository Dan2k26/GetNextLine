/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:58:04 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/08/25 19:14:05 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buff;
	char	*str;

	if (!(buff = malloc(BUFFER_SIZE * sizeof(char))))
		return (NULL);
	if (!(str = malloc(BUFFER_SIZE * sizeof(char))))
		return (NULL);
	while (read(fd, buff, BUFFER_SIZE))
	{
		str = ft_strjoin(str, buff);
	}
	return (str);
}
