/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:45:11 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 00:56:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	expander(t_cmd *lst, int idx, int is_pipe)
{
	t_cmd_lst	*new_lst;

	(void) is_pipe;
	while (idx < lst->cmd_len)
	{
		new_lst = cmd_lst_new(lst, idx);
		get_rd_in(lst, new_lst, idx);
		get_rd_out(lst, new_lst, idx);
		get_cmd_bltn(lst, new_lst, idx);
		get_cmd_argv(lst, new_lst, idx);
		get_cmd_envp(lst, new_lst, idx);
		get_cmd_pipe(lst, new_lst, idx);
		lst->cmd_lst = cmd_lst_add_back(lst->cmd_lst, new_lst);
		idx++;
	}
}
