/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:00:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 19:51:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	free_cmd_lst_params(t_cmd_lst *cmd)
{
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->in_fd)
		free(cmd->in_fd);
	if (cmd->is_heredoc)
		free(cmd->is_heredoc);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->out_fd)
		free(cmd->out_fd);
	if (cmd->o_mode)
		free(cmd->o_mode);
	if (cmd->markout)
		free(cmd->markout);
	if (cmd->path)
		free(cmd->path);
	if (cmd->argv)
		free(cmd->argv);
	if (cmd->bargv)
		free(cmd->bargv);
}

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
			free_cmd_lst_params(last);
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
