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
	(void) cmd;
	if (!ft_strncmp(cmd->bargv[0], "pwd\0", 4))
	{
		char	*pwd;

		pwd = get_pwd();
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(cmd->bargv[0], "echo\0", 5))
	{
		int		i;

		i = 0;
		if (cmd->bargv[1] && !ft_strncmp(cmd->bargv[1], "-n\0", 3))
		{
			i += 2;
			while (i < cmd->blen)
				ft_putstr_fd(cmd->bargv[i++], 1);
		}
		else
		{
			i += 1;
			while (i < cmd->blen)
				ft_putstr_fd(cmd->bargv[i++], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	return (0);
}
