/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 20:58:58 by desausag          #+#    #+#             */
/*   Updated: 2021/01/23 22:24:51 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		ft_hex(int n)
{
	if (n == 10)
		return ('a');
	else if (n == 11)
		return ('b');
	else if (n == 12)
		return ('c');
	else if (n == 13)
		return ('d');
	else if (n == 14)
		return ('e');
	else if (n == 15)
		return ('f');
	else
		return (n + '0');
}

static size_t	count_len(long unsigned int n)
{
	if (n < 16)
		return (1);
	return (count_len(n / 16) + 1);
}

char			*ft_itoa_uhex(long unsigned int n)
{
	int		i;
	char	*z;

	i = count_len(n);
	z = (char *)malloc(sizeof(char) * (i + 1));
	if (!z)
		return (NULL);
	z[i--] = '\0';
	z[0] = '0';
	while (n)
	{
		z[i] = ft_hex(n % 16);
		n = n / 16;
		i--;
	}
	return (z);
}
