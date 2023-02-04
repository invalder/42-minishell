/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 04:40:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern int	g_status;

void	parent(t_cmd_lst *cmd, int *fd)
{
	(void) fd;
	waitpid(cmd->pid, &cmd->status, 0);
	g_status = WEXITSTATUS(cmd->status);
}

void	exec(t_cmd_lst *cmd, int *fd)
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
		exec(cmd, &fd);
		cmd = cmd->right;
	}
	cmd = lst->cmd_lst;
	while (cmd)
	{
		parent(cmd, &fd);
		cmd = cmd->right;
	}
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
