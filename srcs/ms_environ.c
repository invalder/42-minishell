/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:28:26 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 21:45:58 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

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
		ft_putstr_fd(environ[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}

void	init_list(t_cmd *lst)
{
	lst->tmp_envp = environ;
	lst->new_envp = dup_environ(environ);
	environ = lst->new_envp;
	lst->cmd = NULL;
}

// This part is for printing the env after sorting USED FOR `export` command
// before using this part, dup with dup_str_arra first!!
// sort_str(lst->new_envp);
// for (int i = 0; lst->new_envp[i]; i++)
// 	printf("%s\n", lst->new_envp[i]);
