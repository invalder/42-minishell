/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/14 16:53:54 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	free_cmd_lst(t_cmd_lst *cmd)
{
	t_cmd_lst *last;
	t_cmd_lst *p_last;

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
			if (last->out_mode)
				free(last->out_mode);
			if (last->markout)
				free(last->markout);
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

void	print_cmd_lst(t_cmd_lst *cmd)
{
	while (cmd)
	{
		printf("==========\n");
		printf("type: %d\n", cmd->type);
		printf("pid: %d\n", cmd->pid);
		printf("ppid: %d\n", cmd->ppid);
		printf("infile: \n");
		print2d(cmd->infile);
		printf(":::::\n");
		printf("outfile: \n");
		print2d(cmd->outfile);
		printf(":::::\n");
		printf("path: %s\n", cmd->path);
		printf("argv: \n");
		print2d(cmd->argv);
		printf(":::::\n");
		// printf("envp: \n");
		// print2d(cmd->envp);
		// printf(":::::\n");
		printf("==========\n");
		cmd = cmd->right;
	}
}

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
	if (lst)
	{
		new_lst->argc = arr2dsize(lst->cmd[idx]);
		new_lst->markout = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->markout, sizeof(int) * new_lst->argc);
		new_lst->is_heredoc = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->is_heredoc, sizeof(int) * new_lst->argc);
		new_lst->out_mode = malloc(sizeof(int) * new_lst->argc);
		ft_bzero(new_lst->out_mode, sizeof(int) * new_lst->argc);
	}
	else
	{
		new_lst->argc = 0;
		new_lst->markout = NULL;
	}
	new_lst->path = NULL;
	new_lst->argv = NULL;
	new_lst->envp = environ;
	new_lst->left = NULL;
	new_lst->right = NULL;
	new_lst->ppid = getpid();
	new_lst->pid = -1;
	new_lst->type = 0;
	return (new_lst);
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

char	**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**rd_in;
	int		rd_size;
	int 	i;

	rd_in = NULL;
	i = 0;
	while (lst->cmd[idx][i])
	{
		rd_size = arr2dsize(rd_in);
		if (!ft_strncmp(lst->cmd[idx][i], "<<", 2) && lst->cmd[idx][i + 1])
		{
			cmd->markout[i] = 1;
			cmd->markout[i + 1] = 1;
			rd_in = ft_realloc_dstr(rd_in, rd_size + 1);
			rd_in[rd_size] = ft_strjoin("","");
			rd_in[rd_size + 1] = NULL;
			cmd->is_heredoc[rd_size] = 1;
			i++;
		}
		else if (!ft_strncmp(lst->cmd[idx][i], "<", 1) && lst->cmd[idx][i + 1])
		{
			cmd->markout[i] = 1;
			if (access(lst->cmd[idx][i + 1], F_OK) == -1)
			{
				ft_putstr_fd(lst->cmd[idx][i + 1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				free_cmd_lst(lst->cmd_lst);
				// exit(1);
			}
			cmd->markout[i + 1] = 1;
			rd_in = ft_realloc_dstr(rd_in, rd_size + 1);
			rd_in[rd_size] = lst->cmd[idx][i + 1];
			rd_in[rd_size + 1] = NULL;
			cmd->is_heredoc[rd_size] = 0;
			i++;
		}
		i++;
	}
	cmd->infile = rd_in;
	return (rd_in);
}

char	**get_rd_out(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**rd_out;
	int		rd_size;
	int 	i;

	rd_out = NULL;
	i = 0;
	while (lst->cmd[idx][i])
	{
		rd_size = arr2dsize(rd_out);
		if ((!ft_strncmp(lst->cmd[idx][i], ">", 1) || \
			!ft_strncmp(lst->cmd[idx][i], ">>", 2) ) && lst->cmd[idx][i + 1])
		{
			cmd->markout[i] = 1;
			cmd->markout[i + 1] = 1;
			rd_out = ft_realloc_dstr(rd_out, rd_size + 1);
			if (!ft_strncmp(lst->cmd[idx][i], ">>", 2))
				cmd->out_mode[rd_size] = O_WRONLY | O_APPEND;
			else if (!ft_strncmp(lst->cmd[idx][i], ">", 1))
				cmd->out_mode[rd_size] = O_WRONLY | O_TRUNC;
			rd_out[rd_size] = lst->cmd[idx][i + 1];
			rd_out[rd_size + 1] = NULL;
			i++;
		}
		i++;
	}
	cmd->outfile = rd_out;
	return (rd_out);
}

void	get_cmd_argv(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	int		i;
	char	**argv;
	int		argc;

	i = 0;
	argv = NULL;
	while (lst->cmd[idx][i])
	{
		// printf("%s\n", lst->cmd[idx][i]);
		// printf("%d\n", cmd->markout[i]);
		argc = arr2dsize(argv);
		if (!cmd->markout[i])
		{
			argv = ft_realloc_dstr(argv, argc + 1);
			argv[argc] = lst->cmd[idx][i];
			argv[argc + 1] = NULL;
		}
		i++;
	}
	cmd->argv = argv;
}

void	expander(t_cmd *lst, int idx, int is_pipe)
{
	t_cmd_lst	*new_lst;
	char		**rd_in;
	char		**rd_out;
	char		**cmd;

	(void) idx;
	(void) is_pipe;
	(void) rd_in;
	(void) rd_out;
	(void) cmd;
	while (idx < lst->cmd_len)
	{
		new_lst = cmd_lst_new(lst, idx);
		get_rd_in(lst, new_lst, idx);
		get_rd_out(lst, new_lst, idx);
		get_cmd_argv(lst, new_lst, idx);
		lst->cmd_lst = cmd_lst_add_back(lst->cmd_lst, new_lst);
		idx++;
	}
	print_cmd_lst(lst->cmd_lst);
	free_cmd_lst(lst->cmd_lst);
	lst->cmd_lst = NULL;
}

void	exec_main(t_cmd *lst)
{
	if (lst->cmd[0])
	{
		expander(lst, 0, 0);
	}
}
