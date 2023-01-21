/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:43:49 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 23:58:21 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

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
