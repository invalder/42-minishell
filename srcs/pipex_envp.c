/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:02:57 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/30 18:33:57 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_envp(char **list_envp, char *cmd)
{
	char	**lst_tmp;

	lst_tmp = list_envp;
	while (*lst_tmp)
	{
		if (access(*lst_tmp, R_OK | F_OK | X_OK) == 0)
			return (*lst_tmp);
		lst_tmp++;
	}
	if (access(cmd, R_OK | F_OK | X_OK) == 0)
		return (cmd);
	return (NULL);
}

char	**list_envp(char **envp, char *cmd)
{
	char	**lst_envp;
	char	**lst_tmp;
	char	**cmd_lst;
	char	*ptr;
	char	*ptr2;

	cmd_lst = ft_split(cmd, ' ');
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	lst_envp = ft_split((*envp) + 5, ':');
	lst_tmp = lst_envp;
	while (*lst_tmp != NULL)
	{
		ptr = *lst_tmp;
		ptr2 = ft_strjoin("/", cmd_lst[0]);
		*lst_tmp = ft_strjoin(ptr, ptr2);
		free(ptr);
		free(ptr2);
		lst_tmp++;
	}
	free_lst(cmd_lst);
	return (lst_envp);
}

void	free_lst(char **lst)
{
	char	**lst_ptr;

	lst_ptr = lst;
	while (*lst)
	{
		if (*lst != NULL)
			free(*lst);
		lst++;
	}
	free(lst_ptr);
}
