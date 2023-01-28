/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 15:49:10 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern int	g_status;

void	child(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	if (!cmd->pid)
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
		infile(cmd);
		if (cmd->outfile)
		{
			outfile(cmd);
			write(cmd->pfd[1], NULL, 1);
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

void	parent(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	// if(cmd->pid)
	// {
		waitpid(cmd->pid, &cmd->status, 0);
		// dprintf(2, "status in: %d\n", WEXITSTATUS(cmd->status));
		g_status = WEXITSTATUS(cmd->status);
	// }
}

void	exec2(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	if (cmd->pid)
		cmd->pid = fork();
	child(cmd, fd);
}

void	executor(t_cmd *lst)
{
	t_cmd_lst	*cmd;
	int			fd;

	(void) fd;
	fd = dup(0);
	cmd = lst->cmd_lst;
	while (cmd)
	{
		open_infile(cmd);
		open_outfile(cmd);
		// exec(cmd, &fd);
		exec2(cmd, &fd);
		cmd = cmd->right;
	}
	// cmd = lst->cmd_lst;
	// while (cmd)
	// {
	// 	child(cmd, &fd);
	// 	cmd = cmd->right;
	// }
	cmd = lst->cmd_lst;
	while (cmd)
	{
		parent(cmd, &fd);
		cmd = cmd->right;
	}
	while (wait(0) != -1 || errno != ECHILD) ;
	// dprintf(2, "status: %d\n",lst->status);
	// g_status = lst->status;
	dup2(0, fd);
}

void	exec_main(t_cmd *lst)
{
	unlink_heredoc();
	if (lst->cmd[0])
	{
		expander(lst, 0, 0);
		// print_cmd_lst(lst->cmd_lst);
		executor(lst);
		free_cmd_lst(lst->cmd_lst);
		lst->cmd_lst = NULL;
	}
}
