/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_prep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:13:37 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 15:29:18 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

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
				exit(1);
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
	cmd->type = EXEC;
	if (!ft_strncmp(lst->cmd[idx][i], "(null)", 6))
	{
		cmd->type = EXEC;
		i++;
	}
	else if (!ft_strncmp(lst->cmd[idx][i], "||", 2))
		cmd->type = OR;
	else if (!ft_strncmp(lst->cmd[idx][i], "&&", 2))
		cmd->type = AND;
	else if (!ft_strncmp(lst->cmd[idx][i], "|", 1))
		cmd->type = PIPE;
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
