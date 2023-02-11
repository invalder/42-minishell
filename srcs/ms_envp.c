/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:03:07 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 11:21:23 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	*check_envp(char **list_envp, char *cmd)
{
	char	**lst_tmp;

	if (list_envp)
	{
		lst_tmp = list_envp;
		while (*lst_tmp)
		{
			if (access(*lst_tmp, R_OK | F_OK | X_OK) == 0)
				return (ft_strdup(*lst_tmp));
			lst_tmp++;
		}
		if (access(cmd, R_OK | F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	**list_envp(char **envp, char *cmd)
{
	char	**lst_envp;
	char	**lst_tmp;
	char	**cmd_lst;
	char	*ptr;
	char	*ptr2;

	ptr = NULL;
	ptr2 = NULL;
	cmd_lst = ft_split(cmd, ' ');
	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!(*envp))
		return (NULL);
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
