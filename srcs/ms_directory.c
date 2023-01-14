/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:19:48 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/14 23:27:00 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

char	*get_pwd()
{
	return (getcwd(NULL, MAXPATHLEN));
}

/*
 * Change the current working directory.
 *		- If the path is a relative or absolute path, it will be used directly.
 *		- If the path is related to HOME (`cd ~` or `cd`), it will be expanded to absolute path.
 *
 * @param path_str The path to the new working directory.
*/
void	ms_cd(char *path_str)
{
	int		status_code;
	char	*new_path;

	new_path = NULL;
	if (path_str[0] == '~')
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
	exit(status_code);
}
