/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:46:59 by desausag          #+#    #+#             */
/*   Updated: 2020/12/09 13:23:51 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *src)
{
	int i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(ret = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	ft_memcpy(ret, s1, ft_strlen(s1));
	ft_memcpy(ret + ft_strlen(s1), s2, ft_strlen(s2));
	ret[--i] = '\0';
	return (ret);
}

char	*ft_strdup(const char *str)
{
	int		i;
	char	*p;

	i = (int)ft_strlen(str) + 1;
	if (!(p = (char*)malloc(sizeof(char) * (i))))
		return (NULL);
	ft_memcpy(p, str, i);
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sour;
	size_t			i;

	i = 0;
	dest = (unsigned char*)destination;
	sour = (unsigned char*)source;
	while (i != n)
	{
		dest[i] = sour[i];
		i++;
	}
	return (destination);
}
