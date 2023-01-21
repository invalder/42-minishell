/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/22 00:02:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int		exec(t_cmd_lst *cmd, int *fd)
{
	cmd->pid = fork();
	if (!cmd->pid)
	{
		dup2(*fd, 0);
		close(*fd);
		infile(cmd);
		if (cmd->outfile)
		{
			outfile(cmd);
		}
		else
		{
			if (cmd->right)
			{
				dup2(cmd->pfd[1], 1);
				close(cmd->pfd[0]);
				close(cmd->pfd[1]);
			}
		}
		if (cmd->path)
			execve(cmd->path, cmd->argv, cmd->envp);
		execve(*cmd->argv, cmd->argv, cmd->envp);
		err_eexec(*cmd->argv, 1);
	}
	waitpid(cmd->pid, &cmd->status, 0);
	if (!cmd->right)
	{
		dup2(0, *fd);
	}
	if (cmd->right)
	{
		dup2(cmd->pfd[0], *fd);
		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
	}
	// dprintf(2, "status in: %d\n", WEXITSTATUS(cmd->status));
	// return (WIFEXITED(cmd->status) && WEXITSTATUS(cmd->status));
	return (WEXITSTATUS(cmd->status));
}

void	executor(t_cmd *lst)
{
	t_cmd_lst	*cmd;
	int			fd;

	fd = dup(0);
	cmd = lst->cmd_lst;
	while (cmd)
	{
		open_infile(cmd);
		open_outfile(cmd);
		lst->status = exec(cmd, &fd);
		cmd = cmd->right;
	}
	while (wait(0) != -1 || errno != ECHILD) ;
	dprintf(2, "status: %d\n",lst->status);
	dup2(0, fd);
}

void	exec_main(t_cmd *lst)
{
	unlink_heredoc();
	if (lst->cmd[0])
	{
		expander(lst, 0, 0);
		executor(lst);
		free_cmd_lst(lst->cmd_lst);
		lst->cmd_lst = NULL;
	}
}
