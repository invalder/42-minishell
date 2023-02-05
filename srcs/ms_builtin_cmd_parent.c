/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 01:02:12 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/05 19:44:34 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	cmd_bltn_parent_exec(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->bargv[0], "cd\0", 3))
		return (cmd_bltn_cd(cmd));
	if (!ft_strncmp(cmd->bargv[0], "exit\0", 5))
		return (cmd_bltn_exit(cmd));
	if (!ft_strncmp(cmd->bargv[0], "unset\0", 6))
		return (cmd_bltn_unset(cmd));
	if (!ft_strncmp(cmd->bargv[0], "export\0", 7))
		return (cmd_bltn_unset(cmd));
	return (-1);
}

char	**get_bltn_parent(t_cmd_lst *cmd, char **bltn, int i, char **metas)
{
	(void) bltn;
	cmd->btype = 1;
	get_cmd_bargv(cmd, i, metas);
	cmd->blen = arr2dsize(&metas[i]);
	cmd_bltn_markout(cmd, i, metas);
	return (cmd->bargv);
}
