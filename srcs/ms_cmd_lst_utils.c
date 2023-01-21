/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 00:00:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/22 00:01:33 by nnakarac         ###   ########.fr       */
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
