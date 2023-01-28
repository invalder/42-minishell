/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_prep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:13:37 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 13:36:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	**rd_in_mark(t_cmd_lst *cmd, char **rd_in, int i, char *meta)
{
	int		rd_size;
	char	**new_rd;

	rd_size = arr2dsize(rd_in);
	cmd->markout[i] = 1;
	cmd->markout[i + 1] = 1;
	new_rd = ft_realloc_dstr(rd_in, rd_size + 1);
	new_rd[rd_size] = meta;
	new_rd[rd_size + 1] = NULL;
	return (new_rd);
}


// if ((!ft_strncmp(lst->cmd[idx][i], "<<", 2) && lst->cmd[idx][i + 1]) \
// 	|| (!ft_strncmp(lst->cmd[idx][i], "<", 1) && lst->cmd[idx][i + 1]))
// {
// 	rd_in = rd_in_mark(cmd, &rd_in, &i, lst->cmd[idx][i + 1]);
// 	if (!ft_strncmp(lst->cmd[idx][i], "<<", 2))
// 		cmd->is_heredoc[rd_size] = 1;
// 	else
// 		cmd->is_heredoc[rd_size] = 0;
// }

char	**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**rd_in;
	int		rd_size;
	int		i;

	rd_in = NULL;
	i = 0;
	while (lst->cmd[idx][i])
	{
		rd_size = arr2dsize(rd_in);
		if ((!ft_strncmp(lst->cmd[idx][i], "<<", 2) && lst->cmd[idx][i + 1]) \
			|| (!ft_strncmp(lst->cmd[idx][i], "<", 1) && lst->cmd[idx][i + 1]))
		{
			rd_in = rd_in_mark(cmd, rd_in, i, lst->cmd[idx][i + 1]);
			if (!ft_strncmp(lst->cmd[idx][i], "<<", 2))
				cmd->is_heredoc[rd_size] = 1;
			else
				cmd->is_heredoc[rd_size] = 0;
			i++;
		}
		i++;
	}
	cmd->in_fd = malloc(sizeof(int) * i);
	ft_bzero(cmd->in_fd, sizeof(int) * i);
	cmd->infile = rd_in;
	return (rd_in);
}

char	**get_rd_out(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**rd_out;
	int		rd_size;
	int		i;

	rd_out = NULL;
	i = 0;
	while (lst->cmd[idx][i])
	{
		rd_size = arr2dsize(rd_out);
		if ((!ft_strncmp(lst->cmd[idx][i], ">", 1) || \
			!ft_strncmp(lst->cmd[idx][i], ">>", 2)) && lst->cmd[idx][i + 1])
		{
			cmd->markout[i] = 1;
			cmd->markout[i + 1] = 1;
			rd_out = ft_realloc_dstr(rd_out, rd_size + 1);
			if (!ft_strncmp(lst->cmd[idx][i], ">>", 2))
				cmd->o_mode[rd_size] = O_CREAT | O_RDWR | O_APPEND;
			else if (!ft_strncmp(lst->cmd[idx][i], ">", 1))
				cmd->o_mode[rd_size] = O_CREAT | O_RDWR | O_TRUNC;
			rd_out[rd_size] = lst->cmd[idx][i + 1];
			rd_out[rd_size + 1] = NULL;
			i++;
		}
		i++;
	}
	cmd->out_fd = malloc(sizeof(int) * i);
	ft_bzero(cmd->out_fd, sizeof(int) * i);
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
	cmd->type = EXEC;
	if (!ft_strncmp(lst->cmd[idx][i], "(null)", 6))
	{
		cmd->type = EXEC;
		i++;
	}
	else if (!ft_strncmp(lst->cmd[idx][i], "||", 2))
	{
		cmd->type = OR;
		i++;
	}
	else if (!ft_strncmp(lst->cmd[idx][i], "&&", 2))
	{
		cmd->type = AND;
		i++;
	}
	else if (!ft_strncmp(lst->cmd[idx][i], "|", 1))
	{
		cmd->type = PIPE;
		i++;
	}
	while (lst->cmd[idx][i])
	{
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

void	get_cmd_pipe(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	(void) lst;
	(void) idx;
	pipe(cmd->pfd);
}

void	get_cmd_envp(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	(void) lst;
	(void) idx;
	if (cmd->argv && cmd->argv[0])
		cmd->path = check_envp(list_envp(environ, cmd->argv[0]), cmd->argv[0]);
}
