/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:14:59 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/23 23:30:05 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst);

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*p_lst;

	p_lst = lst;
	if (!p_lst)
		return (p_lst);
	while (p_lst->next)
	{
		p_lst = p_lst->next;
	}
	return (p_lst);
}
