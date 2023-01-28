/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:51:17 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 17:54:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern int	g_status;

void	child_pipe_in(t_cmd_lst *cmd, int *fd)
{
	if (!cmd->left)
	{
		dup2(*fd, STDIN_FILENO);
		close(*fd);
	}
	if (cmd->left)
	{
		dup2(cmd->left->pfd[0], STDIN_FILENO);
		close(cmd->left->pfd[0]);
		close(cmd->left->pfd[1]);
	}
}

void	child_before_out(t_cmd_lst *cmd, int *fd)
{
	if (cmd->outfile)
	{
		outfile(cmd);
		write(cmd->pfd[1], "", 1);
	}
	else
	{
		if (cmd->right)
		{
			dup2(cmd->pfd[1], STDOUT_FILENO);
			close(cmd->pfd[0]);
		}
		else
			dup2(cmd->pfd[1], *fd);
	}
	close(cmd->pfd[1]);
}

void	child(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	if (!cmd->pid)
	{
		child_pipe_in(cmd, fd);
		infile(cmd);
		child_before_out(cmd, fd);
		if (cmd->path)
			execve(cmd->path, cmd->argv, cmd->envp);
		execve(*cmd->argv, cmd->argv, cmd->envp);
		err_eexec(*cmd->argv, 1);
	}
	else
	{
		if (cmd->left)
			close(cmd->left->pfd[0]);
		if (cmd->right)
			close(cmd->pfd[1]);
	}
}
