/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 23:05:42 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/23 23:30:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst);

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*p_lst;

	len = 0;
	p_lst = lst;
	while (p_lst)
	{
		len++;
		if (p_lst->next)
			p_lst = p_lst->next;
		else
			break ;
	}
	return (len);
}
