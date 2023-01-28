/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 18:04:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 22:13:49 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	**get_bltn_child(t_cmd_lst *cmd, char **rd_in, int i, char **metas)
{
	cmd->bargv = metas;
	return (cmd->bargv);
}

char	**get_bltn_parent(t_cmd_lst *cmd, char **bltn, int i, char **metas)
{
	cmd->bargv = metas;
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
	i = 0;
	while (lst->cmd[idx][i])
	{
		bltn_size = arr2dsize(bltn);
		if ((!ft_strncmp(lst->cmd[idx][i], "export\0", 7)) || \
			(!ft_strncmp(lst->cmd[idx][i], "unset\0", 6)) || \
			(!ft_strncmp(lst->cmd[idx][i], "cd\0", 3)))
			bltn = get_bltn_parent(cmd, bltn, i, lst->cmd[idx]);
		else if ((!ft_strncmp(lst->cmd[idx][i], "env\0", 4)) || \
			(!ft_strncmp(lst->cmd[idx][i], "echo\0", 5)) || \
			(!ft_strncmp(lst->cmd[idx][i], "pwd\0", 4)))
			bltn = get_bltn_parent(cmd, bltn, i, lst->cmd[idx]);
		else
			break ;
		i++;
	}
}

// char	**rd_in_mark(t_cmd_lst *cmd, char **rd_in, int i, char *meta)
// {
// 	int		rd_size;
// 	char	**new_rd;

// 	rd_size = arr2dsize(rd_in);
// 	cmd->markout[i] = 1;
// 	cmd->markout[i + 1] = 1;
// 	new_rd = ft_realloc_dstr(rd_in, rd_size + 1);
// 	new_rd[rd_size] = meta;
// 	new_rd[rd_size + 1] = NULL;
// 	return (new_rd);
// }

// char	**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx)
// {
// 	char	**rd_in;
// 	int		rd_size;
// 	int		i;

// 	rd_in = NULL;
// 	i = 0;
// 	while (lst->cmd[idx][i])
// 	{
// 		rd_size = arr2dsize(rd_in);
// 		if ((!ft_strncmp(lst->cmd[idx][i], "<<", 2) && lst->cmd[idx][i + 1]) \
// 			|| (!ft_strncmp(lst->cmd[idx][i], "<", 1) && lst->cmd[idx][i + 1]))
// 		{
// 			rd_in = rd_in_mark(cmd, rd_in, i, lst->cmd[idx][i + 1]);
// 			if (!ft_strncmp(lst->cmd[idx][i], "<<", 2))
// 				cmd->is_heredoc[rd_size] = 1;
// 			else
// 				cmd->is_heredoc[rd_size] = 0;
// 			i++;
// 		}
// 		i++;
// 	}
// 	cmd->in_fd = malloc(sizeof(int) * i);
// 	ft_bzero(cmd->in_fd, sizeof(int) * i);
// 	cmd->infile = rd_in;
// 	return (rd_in);
// }
