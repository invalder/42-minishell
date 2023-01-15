/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:01:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 15:14:20 by nnakarac         ###   ########.fr       */
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
			if (last->out_mode)
				free(last->out_mode);
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
		get_cmd_pipe(lst, new_lst, idx);
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
