/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:37:18 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 00:53:36 by nnakarac         ###   ########.fr       */
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

int	cmd_bltn_export(t_cmd_lst *cmd)
{
	char	**tmp_env;
	int		i;

	(void) cmd;
	i = 0;
	tmp_env = dup_environ(environ);
	sort_str(tmp_env);
	while (tmp_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp_env[i], 1);
		ft_putstr_fd("\n", 1);
		free(tmp_env[i++]);
	}
	free(tmp_env);
	return (0);
}

int	cmd_bltn_unset(t_cmd_lst *cmd)
{
	if (cmd->bargv[1])
		unset_env(cmd->bargv[1]);
	return (0);
}

void	cmd_bltn_markout(t_cmd_lst *cmd, int i, char **metas)
{
	while (metas[i])
	{
		cmd->markout[i] = 1;
		i++;
	}
}
