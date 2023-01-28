/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:49:29 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 11:14:14 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

t_cmd_lst	*cmd_lst_last(t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*p_lst;

	p_lst = cmd_lst;
	if (!p_lst)
		return (p_lst);
	while (p_lst->right)
	{
		p_lst = p_lst->right;
	}
	return (p_lst);
}

t_cmd_lst	*cmd_lst_add_front(t_cmd_lst *cmd_lst, t_cmd_lst *new)
{
	new->right = cmd_lst;
	new->left = NULL;
	cmd_lst->left = new;
	return (new);
}

t_cmd_lst	*cmd_lst_add_back(t_cmd_lst *cmd_lst, t_cmd_lst *new)
{
	t_cmd_lst	*last;

	if (cmd_lst)
	{
		last = cmd_lst_last(cmd_lst);
		new->right = NULL;
		if (last)
		{
			last->right = new;
			new->left = last;
			return (cmd_lst);
		}
		new->left = NULL;
		return (new);
	}
	return (new);
}
