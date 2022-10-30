/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:16:44 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/30 19:16:53 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_exec_parent(int argc, char **argv, char **envp, t_meta *meta)
{
	(void) argc;
	(void) argv;
	(void) envp;
	wait(NULL);
	dup2(meta->pipe_fd[0], 0);
	close(meta->pipe_fd[1]);
}

void	pipex_exec_child(int argc, char **argv, char **envp, t_meta *meta)
{
	char	*cmd_path;
	char	**cmd_arg;
	int		fd_out;

	fd_out = 0;
	cmd_path = check_envp(list_envp(envp, argv[meta->cnt]), argv[meta->cnt]);
	if (!cmd_path)
	{
		err_message("pipex: command not found: ");
		err_message(argv[meta->cnt]);
		err_message("\n");
	}
	else
	{
		if (meta->cnt == argc - 2)
		{
			fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0755);
			dup2(fd_out, 1);
		}
		else
			dup2(meta->pipe_fd[1], 1);
		cmd_arg = ft_split(argv[meta->cnt], ' ');
		execve(cmd_path, cmd_arg, envp);
		if (fd_out)
			close(fd_out);
	}
}

void	pipex_execution(int argc, char **argv, char **envp, int fd)
{
	int		cnt;
	int		pid;
	int		fd_pipe[2];
	t_meta	meta;

	dup2(fd, 0);
	cnt = 2;
	pid = 1;
	if (!ft_strncmp("here_doc", argv[1], 9))
		cnt += 2;
	while (cnt < argc - 1)
	{
		meta.cnt = cnt;
		meta.pipe_fd = fd_pipe;
		if (pipe(fd_pipe) != 0)
			exit_message("Can not open pipe!!!\n");
		if (pid)
			pid = fork();
		if (pid == 0)
		{
			pipex_exec_child(argc, argv, envp, &meta);
		}
		else
		{
			pipex_exec_parent(argc, argv, envp, &meta);
		}
		cnt++;
	}
}
