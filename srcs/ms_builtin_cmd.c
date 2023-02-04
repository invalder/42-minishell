/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:04:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 05:23:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int		cmd_bltn_exec(t_cmd_lst *cmd)
{
	if (!cmd->btype)
		return (cmd_bltn_child_exec(cmd));
	else
		return (cmd_bltn_parent_exec(cmd));
}

void	cmd_bltn_markout(t_cmd_lst *cmd, int i, char **metas)
{
	while(metas[i])
	{
		cmd->markout[i] = 1;
		i++;
	}
}

char	**get_bltn_child(t_cmd_lst *cmd, char **bltn, int i, char **metas)
{
	(void) bltn;
	cmd->btype = 0;
	cmd->bargv = &metas[i];
	cmd->blen = arr2dsize(&metas[i]);
	cmd_bltn_markout(cmd, i, metas);
	return (cmd->bargv);
}

char	**get_bltn_parent(t_cmd_lst *cmd, char **bltn, int i, char **metas)
{
	(void) bltn;
	cmd->btype = 1;
	cmd->bargv = &metas[i];
	cmd->blen = arr2dsize(&metas[i]);
	cmd_bltn_markout(cmd, i, metas);
	return (cmd->bargv);
}

/// @brief check for the builtins
/// echo with option -n (child)
/// cd with relative or absolute (parent)
/// pwd with no options (child)
/// export with no options (parent)
/// unset with (parent)
/// env (parent / child)
/// exit (parent)
/// @param lst
/// @param cmd
/// @param idx
void	get_cmd_bltn(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**bltn;
	int		bltn_size;
	int		i;

	bltn = NULL;
	i = 1;
	while (lst->cmd[idx][i])
	{
		bltn_size = arr2dsize(bltn);
		if ((!ft_strncmp(lst->cmd[idx][i], "export\0", 7)) || \
			(!ft_strncmp(lst->cmd[idx][i], "unset\0", 6)) || \
			(!ft_strncmp(lst->cmd[idx][i], "cd\0", 3)) || \
			(!ft_strncmp(lst->cmd[idx][i], "exit\0", 5)))
			bltn = get_bltn_parent(cmd, bltn, i, lst->cmd[idx]);
		else if ((!ft_strncmp(lst->cmd[idx][i], "env\0", 4)) || \
			(!ft_strncmp(lst->cmd[idx][i], "echo\0", 5)) || \
			(!ft_strncmp(lst->cmd[idx][i], "pwd\0", 4)))
			bltn = get_bltn_child(cmd, bltn, i, lst->cmd[idx]);
		else
			if (!cmd->markout[i])
				break;
		i++;
	}
}
