/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:28:26 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 22:02:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern t_global	g_globe;

char	**dup_environ(char **envp)
{
	int		i;
	char	**new;
	int		size;

	i = 0;
	size = arr2dsize(envp);
	new = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**dup_str_array(char **env)
{
	int		i;
	char	**new;

	i = 0;
	while (env[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	sort_str(char **str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			len = ft_strlen(str[i]);
			if ((int)ft_strlen(str[j]) < len)
				len = ft_strlen(str[j]);
			if (ft_strncmp(str[i], str[j], len) > 0)
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "\0", 1))
		{
			ft_putstr_fd(environ[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (0);
}

void	init_list(t_cmd *lst)
{
	lst->env_addr = &environ;
	g_globe.env_addr = lst->env_addr;
	environ = dup_environ(environ);
	lst->cmd = NULL;
	lst->cmd_len = 0;
	lst->cmd_lst = NULL;
	lst->cwd = NULL;
	lst->status = 0;
}

// This part is for printing the env after sorting USED FOR `export` command
// before using this part, dup with dup_str_arra first!!
// sort_str(lst->new_envp);
// for (int i = 0; lst->new_envp[i]; i++)
// 	printf("%s\n", lst->new_envp[i]);
