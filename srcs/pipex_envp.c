/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:02:57 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/15 02:28:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**list_envp(char **envp, char *cmd)
{
	char	**lst_envp;
	char	**lst_tmp;
	char	*ptr;

	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	lst_envp = ft_split(*envp+5, ':');
	lst_tmp = lst_envp;
	while (*lst_tmp)
	{
		ptr = *lst_tmp;
		*lst_tmp = ft_strjoin(ptr, cmd);
		free(ptr);
		lst_tmp++;
	}
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
