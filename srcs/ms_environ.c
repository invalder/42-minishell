/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:28:26 by sthitiku          #+#    #+#             */
/*   Updated: 2022/12/24 23:05:09 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

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
	printf("split = %s\n", arr[1]);
	while (environ[i])
		i++;
	new = malloc(sizeof(char *) * i + 2);
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

char	**dup_environ(char **environ)
{
	int		i;
	char	**new;

	i = 0;
	while (environ[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		new[i] = ft_strdup(environ[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	print_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	init_list(t_cmd *lst)
{
	lst->tmp_envp = environ;
	lst->new_envp = dup_environ(environ);
	environ = lst->new_envp;
	lst->cmd = NULL;
	// printf("%s\n", getenv("LOGNAME"));
	// unset_env("LOGNAME");
	// printf("%s\n", getenv("LOGNAME"));
	// export_env("LOGNAME=hello");
	// printf("%s\n", getenv("LOGNAME"));
}
