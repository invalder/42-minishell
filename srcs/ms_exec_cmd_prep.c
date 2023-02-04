/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_prep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:13:37 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 11:16:08 by nnakarac         ###   ########.fr       */
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
		if ((!ft_strncmp(lst->cmd[idx][i], "<<\0", 3) && lst->cmd[idx][i + 1]) \
			|| (!ft_strncmp(lst->cmd[idx][i], "<\0", 2) && lst->cmd[idx][i + 1]))
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

char	**rd_out_mark(t_cmd_lst *cmd, char **rd_out, int i, char *meta)
{
	int		rd_size;
	char	**new_rd;

	rd_size = arr2dsize(rd_out);
	cmd->markout[i] = 1;
	cmd->markout[i + 1] = 1;
	new_rd = ft_realloc_dstr(rd_out, rd_size + 1);
	new_rd[rd_size] = meta;
	new_rd[rd_size + 1] = NULL;
	return (new_rd);
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
		if ((!ft_strncmp(lst->cmd[idx][i], ">\0", 2) || \
			!ft_strncmp(lst->cmd[idx][i], ">>\0", 3)) && lst->cmd[idx][i + 1])
		{
			rd_out = rd_out_mark(cmd, rd_out, i, lst->cmd[idx][i + 1]);
			if (!ft_strncmp(lst->cmd[idx][i], ">>\0", 3))
				cmd->o_mode[rd_size] = O_CREAT | O_RDWR | O_APPEND;
			else if (!ft_strncmp(lst->cmd[idx][i], ">\0", 2))
				cmd->o_mode[rd_size] = O_CREAT | O_RDWR | O_TRUNC;
			i++;
		}
		i++;
	}
	cmd->out_fd = malloc(sizeof(int) * i);
	ft_bzero(cmd->out_fd, sizeof(int) * i);
	cmd->outfile = rd_out;
	return (rd_out);
}
