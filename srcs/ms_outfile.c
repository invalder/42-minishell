/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:44:07 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 14:01:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

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
		// printf("here\n");
		// printf("%d %d\n", cmd->pfd[1], fd);
		dup2(fd, STDOUT_FILENO);
		close(cmd->pfd[1]);
	}
}
