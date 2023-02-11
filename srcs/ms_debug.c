/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:47:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 01:00:55 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	print_cmd_lst(t_cmd_lst *cmd)
{
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->right;
	}
}

void	print_cmd(t_cmd_lst *cmd)
{
	dprintf(2, "==========\n");
	dprintf(2, "type: %d\n", cmd->type);
	dprintf(2, "pid: %d\n", cmd->pid);
	dprintf(2, "ppid: %d\n", cmd->ppid);
	dprintf(2, "infile: \n");
	print2d(cmd->infile);
	dprintf(2, ":::::\n");
	dprintf(2, "outfile: \n");
	print2d(cmd->outfile);
	dprintf(2, ":::::\n");
	dprintf(2, "path: %s\n", cmd->path);
	dprintf(2, "argv: \n");
	print2d(cmd->argv);
	dprintf(2, ":::::\n");
	dprintf(2, "bargv: \n");
	print2d(cmd->bargv);
	dprintf(2, ":::::\n");
	dprintf(2, "==========\n");
}

void	print2d(char **ptr)
{
	int	cnt;

	cnt = 0;
	if (ptr)
	{
		while (ptr[cnt])
		{
			dprintf(2, ">>>|%s|<<<\n", ptr[cnt]);
			cnt++;
		}
	}
}

void	print_form_begin(t_cmd_lst *cmd)
{
	t_cmd_lst	*p_cmd;

	p_cmd = cmd;
	while (p_cmd)
	{
		if (p_cmd->left)
			p_cmd = p_cmd->left;
		else
			break ;
	}
	while (p_cmd)
	{
		print2d(p_cmd->argv);
		p_cmd = p_cmd->right;
	}
}

void	print_3star(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			dprintf(2, "cmd[%d][%d] = %s\n", i, j, cmd[i][j]);
			j++;
		}
		dprintf(2, "cmd[%d][%d] = %s\n", i, j, cmd[i][j]);
		i++;
		dprintf(2, "==========\n");
	}
	dprintf(2, "%p\n", cmd[i]);
}
