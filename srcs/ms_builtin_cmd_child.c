/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 01:02:14 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/22 01:02:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	cmd_bltn_child_exec(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->bargv[0], "pwd\0", 4))
		return (cmd_bltn_pwd(cmd));
	if (!ft_strncmp(cmd->bargv[0], "echo\0", 5))
		return (cmd_bltn_echo(cmd));
	if (!ft_strncmp(cmd->bargv[0], "env\0", 4))
		return (cmd_bltn_env(cmd));
	return (0);
}

char	**get_bltn_child(t_cmd_lst *cmd, char **bltn, int i, char **metas)
{
	(void) bltn;
	cmd->btype = 0;
	get_cmd_bargv(cmd, i, metas);
	cmd->blen = arr2dsize(&metas[i]);
	cmd_bltn_markout(cmd, i, metas);
	return (cmd->bargv);
}
