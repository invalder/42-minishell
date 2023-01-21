/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 22:52:14 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	free_cmd_lst(t_cmd_lst *cmd)
{
	t_cmd_lst	*last;
	t_cmd_lst	*p_last;

	last = NULL;
	last = cmd_lst_last(cmd);
	if (last)
	{
		while (last)
		{
			p_last = last->left;
			if (last->infile)
				free(last->infile);
			if (last->in_fd)
				free(last->in_fd);
			if (last->is_heredoc)
				free(last->is_heredoc);
			if (last->outfile)
				free(last->outfile);
			if (last->out_fd)
				free(last->out_fd);
			if (last->o_mode)
				free(last->o_mode);
			if (last->markout)
				free(last->markout);
			if (last->path)
				free(last->path);
			if (last->argv)
				free(last->argv);
			free(last);
			last = NULL;
			if (p_last)
			{
				last = p_last;
			}
		}
		if (last)
			free(last);
	}
}

size_t	arr2dsize(char **ptr)
{
	int	cnt;

	cnt = 0;
	if (ptr)
	{
		while (ptr[cnt])
		{
			cnt++;
		}
	}
	return (cnt);
}

void	print2d(char **ptr)
{
	int	cnt;

	cnt = 0;
	if (ptr)
	{
		while (ptr[cnt])
		{
			printf(">>>%s\n", ptr[cnt]);
			cnt++;
		}
	}
}

void	expander(t_cmd *lst, int idx, int is_pipe)
{
	t_cmd_lst	*new_lst;
	char		**cmd;

	(void) is_pipe;
	(void) cmd;
	while (idx < lst->cmd_len)
	{
		new_lst = cmd_lst_new(lst, idx);
		get_rd_in(lst, new_lst, idx);
		get_rd_out(lst, new_lst, idx);
		get_cmd_argv(lst, new_lst, idx);
		get_cmd_envp(lst, new_lst, idx);
		get_cmd_pipe(lst, new_lst, idx);
		lst->cmd_lst = cmd_lst_add_back(lst->cmd_lst, new_lst);
		idx++;
	}
	// print_cmd_lst(lst->cmd_lst);
	// free_cmd_lst(lst->cmd_lst);
	// lst->cmd_lst = NULL;
}

void	infile(t_cmd_lst *cmd)
{
	int	cnt;
	int	fd;

	cnt = 0;
	fd = 0;
	if (cmd->infile)
	{
		while (cmd->infile[cnt])
		{
				fd = cmd->in_fd[cnt];
				if (fd == -1)
					err_eenoent(cmd->infile[cnt], 1);
				dup2(fd, 0);
				close(fd);
			cnt++;
		}
	}
}

void	outfile(t_cmd_lst *cmd)
{
	int	cnt;
	int	fd;

	cnt = 0;
	fd = 0;
	if (cmd->outfile)
	{
		while (cmd->outfile[cnt])
		{
			fd = cmd->out_fd[cnt];
			cnt++;
		}
		dup2(fd, 1);
		close(fd);
	}
}

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

char	*read_here_doc(void)
{
	char	pathname[20];
	char	*number;
	int		fd;
	int		i;

	i = 1;
	while (i < 65535)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/mini-", 20);
		ft_strlcat(pathname, number, 20);
		free(number);
		if (access(pathname, F_OK) == -1)
		{
			fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd != -1)
			{
				close(fd);
				return (ft_strdup(pathname));
			}
		}
		i++;
	}
	return (NULL);
}

int	heredoc(t_cmd_lst *cmd, int cnt)
{
	int		fd_tmp;
	char	*line;
	char	*line_lim;
	char	*fd_tmp_path;

	fd_tmp_path = read_here_doc();
	fd_tmp = open(fd_tmp_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	line_lim = ft_strjoin(cmd->infile[cnt], "\n");
	if (fd_tmp < 0)
		err_general("can not open file!!!\n", 1);
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, line_lim, ft_strlen(line_lim)))
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
	close(fd_tmp);
	free(line_lim);
	fd_tmp = open(fd_tmp_path, O_RDWR | O_CREAT, 0644);
	free(fd_tmp_path);
	return (fd_tmp);
}

void	open_infile(t_cmd_lst *cmd)
{
	int	cnt;
	int	fd;

	cnt = 0;
	fd = 0;
	if (cmd->infile)
	{
		while (cmd->infile[cnt])
		{
			if (!cmd->is_heredoc[cnt])
			{
				fd = open(cmd->infile[cnt], O_RDONLY, 0444);
				cmd->in_fd[cnt] = fd;
			}
			else
			{
				cmd->in_fd[cnt] = heredoc(cmd, cnt);
			}
			cnt++;
		}
	}
}

void	open_outfile(t_cmd_lst *cmd)
{
	int	cnt;

	cnt = 0;
	if (cmd->outfile)
	{
		while (cmd->outfile[cnt])
		{
			cmd->out_fd[cnt] = open(cmd->outfile[cnt], cmd->o_mode[cnt], 0644);
			cnt++;
		}
	}
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
	// dprintf(2, "err: %d\n",errno);
	dprintf(2, "status: %d\n",lst->status);
	dup2(0, fd);
}

void	unlink_heredoc(void)
{
	char	pathname[20];
	char	*number;
	int		i;

	i = 1;
	while (i < 65535)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/mini-", 20);
		ft_strlcat(pathname, number, 20);
		free(number);
		if (access(pathname, F_OK) != -1)
			unlink(pathname);
		i++;
	}
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
