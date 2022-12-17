/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:09:46 by sthitiku          #+#    #+#             */
/*   Updated: 2022/12/17 17:02:11 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

int	count_cmd(char **cmd, int *i)
{
	int		count;

	count = 0;
	if (cmd[*i][0] == '|' || cmd[*i][0] == '<' || cmd[*i][0] == '>'
		|| cmd[*i][0] == '&')
	{
		count++;
		(*i)++;
	}
	while (cmd[*i])
	{
		if (cmd[*i][0] == '|' || cmd[*i][0] == '<' || cmd[*i][0] == '>'
			|| cmd[*i][0] == '&')
			break ;
		count++;
		(*i)++;
	}
	return (count);
}

int	count_block(char **cmd)
{
	int		i;
	int		j;
	int		count;

	if (!cmd[0])
		return (0);
	i = 0;
	count = 1;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] == '|' || cmd[i][j] == '<' || cmd[i][j] == '>'
			|| cmd[i][j] == '&')
		{
			if (cmd[i][j + 1] == cmd[i][j])
				j++;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**create_blk(char **cmd, int begin, int *end)
{
	int		i;
	int		blk;
	char	**new_blk;

	blk = count_cmd(cmd, end);
	new_blk = malloc(sizeof(char *) * (blk + 1));
	i = 0;
	while (i < blk)
		new_blk[i++] = ft_strdup(cmd[begin++]);
	new_blk[i] = NULL;
	return (new_blk);
}

/**
 * Takes a splited command line and returns a 3D array of strings.
 */
char	***create_cmd(char **cmd)
{
	int		end;
	int		i;
	int		len;
	int		begin;
	char	***block;

	end = 0;
	i = 0;
	len = count_block(cmd);
	block = (char ***)malloc(sizeof(char **) * (len + 1));
	while (i < len)
	{
		begin = end;
		block[i++] = create_blk(cmd, begin, &end);
	}
	block[i] = NULL;
	return (block);
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
