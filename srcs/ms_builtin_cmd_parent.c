/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_parent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 01:02:12 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/05 03:03:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	cmd_bltn_cd(t_cmd_lst *cmd)
{
	if (cmd->bargv[1])
		return (ms_cd(cmd->bargv[1]));
	else
		return (ms_cd(""));
}

int	cmd_bltn_exit(t_cmd_lst *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->bargv[1])
	{
		if (!is_string_numeric(cmd->bargv[1]))
		{
			exit_status = ft_atoi(cmd->bargv[1]) % 256;
			exit(exit_status);
		}
		else
			err_exit(cmd->bargv[1], 1);
	}
	return (0);
}

int	cmd_bltn_parent_exec(t_cmd_lst *cmd)
{
	if (!ft_strncmp(cmd->bargv[0], "cd\0", 3))
		cmd_bltn_cd(cmd);
	if (!ft_strncmp(cmd->bargv[0], "exit\0", 5))
		cmd_bltn_exit(cmd);
	if (!ft_strncmp(cmd->bargv[0], "unset\0", 6))
	{
		if (cmd->bargv[1])
			unset_env(cmd->bargv[1]);
	}
	if (!ft_strncmp(cmd->bargv[0], "export\0", 7))
	{

	}
	return (-1);
}
