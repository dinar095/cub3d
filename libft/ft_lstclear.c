/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 11:33:55 by desausag          #+#    #+#             */
/*   Updated: 2020/12/04 12:53:50 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;

	tmp = *lst;
	if (tmp == 0)
		return ;
	while (tmp)
	{
		tmp = tmp->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
