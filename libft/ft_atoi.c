/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:31:47 by desausag          #+#    #+#             */
/*   Updated: 2020/11/06 21:43:12 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int minus;
	int num;

	minus = 1;
	num = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
	|| *str == '\f' || *str == ' ' || *str == '\r')
		str++;
	if (*str == '-')
		minus = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + *str - '0';
		str++;
	}
	return (num * minus);
}
