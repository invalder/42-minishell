/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:51:17 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 13:53:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern t_global g_globe;

void	close_other_pipes(t_cmd_lst *cmd)
{
	t_cmd_lst	*p_cmd;

	p_cmd = cmd;
	while (p_cmd)
	{
		close(p_cmd->pfd[0]);
		close(p_cmd->pfd[1]);
		p_cmd = p_cmd->left;
	}
	p_cmd = cmd;
	while (p_cmd)
	{
		close(p_cmd->pfd[0]);
		close(p_cmd->pfd[1]);
		p_cmd = p_cmd->right;
	}
}

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
		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		close_other_pipes(cmd);
	}
	else
	{
		if (cmd->right)
		{
			dup2(cmd->pfd[1], STDOUT_FILENO);
			close(cmd->pfd[0]);
			close(cmd->pfd[1]);
			close_other_pipes(cmd);
		}
		else
		{
			dup2(*fd, STDOUT_FILENO);
			close(cmd->pfd[1]);
			close(cmd->pfd[0]);
			close_other_pipes(cmd);
		}
	}
}

void	parent_piping(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	if (cmd->pid)
	{
		if (cmd->bargv)
		{
			if (cmd->btype)
				g_globe.status = cmd_bltn_exec(cmd);
		}
		if (cmd->left)
		{
			close(cmd->left->pfd[0]);
			close(cmd->left->pfd[1]);
		}
	}
}

void	child(t_cmd_lst *cmd, int *fd)
{
	if (!cmd->pid)
	{
		child_pipe_in(cmd, fd);
		infile(cmd);
		child_before_out(cmd, fd);
		if (cmd->bargv)
		{
			if (!cmd->btype)
				cmd->status = cmd_bltn_exec(cmd);
			close(cmd->pfd[0]);
			close(cmd->pfd[1]);
			close_other_pipes(cmd);
			exit(cmd->status);
		}
		else
		{
			if (cmd->path)
				execve(cmd->path, cmd->argv, cmd->envp);
			else if (*cmd->argv)
				execve(*cmd->argv, cmd->argv, cmd->envp);
			err_eexec(*cmd->argv, 1);
		}
	}
	else
		parent_piping(cmd, fd);
}
