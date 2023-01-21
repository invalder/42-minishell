/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:49:29 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 23:14:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

t_cmd_lst	*cmd_lst_new(t_cmd *lst, int idx)
{
	t_cmd_lst	*new_lst;

	new_lst = malloc(sizeof(t_cmd_lst) * 1);
	if (!new_lst)
		return (new_lst);
	new_lst->infile = NULL;
	new_lst->in_fd = NULL;
	new_lst->outfile = NULL;
	new_lst->out_fd = NULL;
	new_lst->path = NULL;
	new_lst->argv = NULL;
	new_lst->envp = environ;
	new_lst->left = NULL;
	new_lst->right = NULL;
	new_lst->ppid = getpid();
	new_lst->pid = -1;
	new_lst->type = 0;
	cmd_lst_new_2(new_lst, lst, idx);
	return (new_lst);
}

void	cmd_lst_new_2(t_cmd_lst *new_lst, t_cmd *lst, int idx)
{
	if (lst)
	{
		new_lst->argc = arr2dsize(lst->cmd[idx]);
		new_lst->markout = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->markout, sizeof(int) * new_lst->argc);
		new_lst->is_heredoc = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->is_heredoc, sizeof(int) * new_lst->argc);
		new_lst->o_mode = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->o_mode, sizeof(int) * new_lst->argc);
	}
	else
	{
		new_lst->argc = 0;
		new_lst->markout = NULL;
		new_lst->is_heredoc = NULL;
		new_lst->o_mode = NULL;
	}
}

void	cmd_lst_new_util1(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	if (lst)
	{
		cmd->argc = arr2dsize(lst->cmd[idx]);
		cmd->markout = malloc(sizeof(int) * cmd->argc);
		if (!cmd->markout)
			return (err_message(ENOMEM, 1));
	}
}

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
