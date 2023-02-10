/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_implement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:12:53 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/10 23:55:47 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	unset_env(char *name)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name, ft_strlen(name)))
			ft_bzero(environ[i], ft_strlen(environ[i]));
		i++;
	}
}

void	export_env(char *exp)
{
	char	**arr;
	char	**new;
	char	**tmp;
	int		i;

	i = 0;
	arr = ft_split(exp, '=');
	tmp = environ;
	while (environ[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (environ[i])
	{
		new[i] = ft_strdup(environ[i]);
		i++;
	}
	new[i++] = ft_strdup(exp);
	new[i] = NULL;
	environ = new;
	free_split(arr);
	free_split(tmp);
}

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

char	*get_pwd(void)
{
	return (getcwd(NULL, MAXPATHLEN));
}

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
