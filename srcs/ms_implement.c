/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_implement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:12:53 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/15 19:35:36 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

int	echo(char **args, int newline)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "echo\0", 5))
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline == 1)
		ft_putchar_fd('\n', 1);
	return (1);
}

char	*get_pwd()
{
	return (getcwd(NULL, MAXPATHLEN));
}

/**
 * Change the current working directory.
 *	- If the path is a relative or absolute path, it will be used directly.
 *	- If the path is related to HOME (`cd ~` or `cd`), it will be expanded to absolute path.
 *
 * @param path_str: The path to the new working directory.
 * @return 0 if the path is valid, -1 otherwise.
 */
int	ms_cd(char *path_str)
{
	int		status_code;
	char	*new_path;

	new_path = NULL;
	if (path_str[0] == '~' || path_str[0] == '\0')
	{
		new_path = malloc(sizeof(char) * (ft_strlen(getenv("HOME")) + 1 + ft_strlen(path_str) - 1));
		ft_strlcpy(new_path, getenv("HOME"), ft_strlen(getenv("HOME")) + 1);
		ft_strlcpy(&new_path[ft_strlen(new_path)], &path_str[1], ft_strlen(path_str));
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
