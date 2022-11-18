/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:41:39 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/23 23:30:18 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p_lst;
	t_list	*p_lst_new;

	p_lst_new = NULL;
	while (lst != NULL)
	{
		p_lst = ft_lstnew(f(lst->content));
		if (p_lst == NULL)
			ft_lstclear(&p_lst_new, del);
		ft_lstadd_back(&p_lst_new, p_lst);
		lst = lst->next;
	}
	return (p_lst_new);
}
