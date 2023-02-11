/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cmd_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 19:37:18 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 15:41:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

int	ms_cd(char *path_str)
{
	int		status_code;
	char	*new_path;

	new_path = NULL;
	if (path_str[0] == '~' || path_str[0] == '\0')
	{
		new_path = malloc(sizeof(char) * (ft_strlen(getenv("HOME")) + \
			1 + ft_strlen(path_str) - 1));
		ft_strlcpy(new_path, getenv("HOME"), ft_strlen(getenv("HOME")) + 1);
		ft_strlcpy(&new_path[ft_strlen(new_path)], &path_str[1], \
			ft_strlen(path_str));
	}
	else
	{
		new_path = malloc(sizeof(char) * (ft_strlen(path_str) + 1));
		ft_strlcpy(new_path, path_str, ft_strlen(path_str) + 1);
	}
	status_code = access(new_path, F_OK);
	if (!status_code)
		chdir(new_path);
	free(new_path);
	return (status_code);
}

int	cmd_bltn_pwd(t_cmd_lst *cmd)
{
	char	*pwd;

	(void) cmd;
	pwd = get_pwd();
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	return (0);
}

int	cmd_bltn_echo(t_cmd_lst *cmd)
{
	int	i;
	int	is_newline;

	i = 1;
	is_newline = 1;
	if (cmd->bargv[1])
	{
		while (!ft_strncmp(cmd->bargv[i], "-n\0", 3))
		{
			i++;
			is_newline = 0;
		}
	}
	while (cmd->bargv[i])
	{
		ft_putstr_fd(cmd->bargv[i++], 1);
		if (cmd->bargv[i])
			ft_putstr_fd(" ", 1);
	}
	if (is_newline)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	cmd_bltn_env(t_cmd_lst *cmd)
{
	(void) cmd;
	print_env();
	return (0);
}
