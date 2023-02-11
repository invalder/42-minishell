/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_implement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:12:53 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 15:50:24 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern t_global	g_globe;

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

void	export_env_util(char **new, char **arr, char *exp, int found)
{
	int	i;

	i = -1;
	while (environ[++i])
	{
		if (!ft_strncmp(environ[i], arr[0], ft_strlen(arr[0])) \
			&& environ[i][ft_strlen(arr[0])] == '=')
		{
			new[i] = ft_strdup(exp);
			found = 1;
		}
		else
			new[i] = ft_strdup(environ[i]);
	}
	if (!found)
		new[i++] = ft_strdup(exp);
	new[i] = NULL;
	environ = new;
	free_split(arr);
}

int	export_env(char *exp)
{
	char	**arr;
	char	**new;
	char	**tmp;
	int		found;

	found = 0;
	arr = ft_split(exp, '=');
	tmp = environ;
	new = ft_calloc(arr2dsize(environ) + 2, sizeof(char *));
	export_env_util(new, arr, exp, found);
	free_split(tmp);
	return (0);
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
