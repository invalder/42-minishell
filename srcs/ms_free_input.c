/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 19:44:29 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 03:07:09 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

void	*free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		if (split[i][0] == '\0')
			free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

void	free_3star(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free(cmd[i][j]);
			j++;
		}
		free(cmd[i]);
		i++;
	}
	free(cmd);
}
