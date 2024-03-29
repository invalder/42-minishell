/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 01:02:12 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 22:33:13 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	cmd_bltn_export_env(t_cmd_lst *cmd)
{
	int		i;
	char	*tmp;
	char	*env;

	i = 1;
	while (cmd->bargv[i])
	{
		if (cmd->bargv[i] && !ft_strncmp(cmd->bargv[i + 1], "=\0", 2) \
			&& cmd->bargv[i + 2])
		{
			tmp = ft_strjoin(cmd->bargv[i], cmd->bargv[i + 1]);
			env = ft_strjoin(tmp, cmd->bargv[i + 2]);
			export_env(env);
			free(tmp);
			free(env);
			i += 3;
		}
		else
			i++;
	}
	return (0);
}

int	cmd_bltn_parent_exec(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->bargv[0], "cd\0", 3))
		return (cmd_bltn_cd(cmd));
	if (!ft_strncmp(cmd->bargv[0], "exit\0", 5))
		return (cmd_bltn_exit(cmd));
	if (!ft_strncmp(cmd->bargv[0], "unset\0", 6))
		return (cmd_bltn_unset(cmd));
	if (!ft_strncmp(cmd->bargv[0], "export\0", 7))
	{
		if (!cmd->bargv[1])
			return (cmd_bltn_export(cmd));
		else
			return (cmd_bltn_export_env(cmd));
	}
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
