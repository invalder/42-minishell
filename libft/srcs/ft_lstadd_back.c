/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:39:51 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/23 23:19:00 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*p_lst;

	p_lst = ft_lstlast(*lst);
	if (p_lst == NULL)
	{
		*lst = new;
		return ;
	}
	p_lst->next = new;
}
