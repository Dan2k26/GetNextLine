/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 20:51:37 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/01 16:27:59 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		num;
	size_t		i;
	char		*str;
	const char	*s;

	i = -1;
	num = sizeof(dst);
	str = dst;
	s = src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (++i < n)
		str[i] = s[i];
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		num;

	num = ft_strlen((char *)s1);
	str = malloc(num + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, num * sizeof(char) + 1);
	str[num] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (c == '\0')
		return (&str[i]);
	return (NULL);
}
