/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 20:51:37 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/19 23:42:35 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_cleanlen(const char *c, int num, void *s, size_t n)
{
	size_t			i;
	unsigned int	y;
	char			*str;

	i = 0;
	y = -1;
	if (num == 0)
	{
		if (c)
		{
			while (c[i] != '\0')
				i++;
		}
	}
	else
	{
		str = (char *) s;
		while (++y < n)
			str[y] = 0;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		size;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_cleanlen(s1, 0, 0, 0) + ft_cleanlen(s2, 0, 0, 0);
	str = (char *)malloc(size + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	size = 0;
	while (s2[size])
	{
		str[i] = s2[size];
		i++;
		size++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		num;
	int		i;

	i = -1;
	num = ft_cleanlen((char *)s1, 0, 0, 0);
	str = malloc(num + 1);
	if (str == NULL)
		return (NULL);
	if (str == NULL && s1 == NULL)
		return (NULL);
	while (++i < (int)(num * sizeof(char) + 1))
		str[i] = s1[i];
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_cleanlen(s + start, 0, 0, 0) < len)
		len = ft_cleanlen(s + start, 0, 0, 0);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_cleanlen("\0", 1, str, len + 1);
	if (start >= (unsigned int)ft_cleanlen(s, 0, 0, 0))
		return (str);
	while (i < len && s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
