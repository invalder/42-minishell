/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 00:09:46 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/06 01:12:20 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

// int	count_cmd(char **cmd, int *i)
// {
// 	int		count;

// 	count = 0;
// 	if (cmd[*i][0] == '|' || cmd[*i][0] == '<' || cmd[*i][0] == '>'
// 		|| cmd[*i][0] == '&')
// 	{
// 		count++;
// 		(*i)++;
// 	}
// 	while (cmd[*i])
// 	{
// 		if (cmd[*i][0] == '|' || cmd[*i][0] == '<' || cmd[*i][0] == '>'
// 			|| cmd[*i][0] == '&')
// 			break ;
// 		count++;
// 		(*i)++;
// 	}
// 	return (count);
// }

// loop through the string
// if find a open quote, loop to check for the close quote
// if close quote is open quote + 1, return 1
int	is_empty_quote(char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '\'' || str[i] == '\"')
		{
			while (str[j])
			{
				if (str[j] == str[i])
				{
					if (i == j - 1)
						return (1);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

// trying to check if there is an empty quote
// if (cmd[*i][0]== '\' )
// 	count--;
int	count_cmd(char **cmd, int *i)
{
	int		count;

	count = 0;
	if (cmd[*i][0] == '|' || cmd[*i][0] == '&')
	{
		count++;
		(*i)++;
	}
	while (cmd[*i])
	{
		if (cmd[*i][0] == '|' || cmd[*i][0] == '&')
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
	if (!ft_isalnum(cmd[0][0]) && cmd[0][0] != '\'' && cmd[0][0] != '\"' && \
		cmd[0][0] != '$' && cmd[0][0] != '|' && cmd[0][0] != '&' && \
		cmd[0][0] != '>' && cmd[0][0] != '<')
			count--;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][j] == '|' || cmd[i][j] == '&')
		{
			count++;
			if ((cmd[i][j + 1] == '|' || cmd[i][j + 1] == '&'
				|| !cmd[i][j + 1]) && i == 0)
				count--;
		}
		i++;
	}
	return (count);
}

static char	**create_blk(char **cmd, int begin, int *end, int index)
{
	int		i;
	int		blk;
	char	**new_blk;

	blk = count_cmd(cmd, end);
	if (index == 0 && (cmd[index][0] != '>' && cmd[index][0] != '<'))
		blk++;
	new_blk = malloc(sizeof(char *) * (blk + 1));
	i = 0;
	while (i < blk)
	{
		if (index == 0 && i == 0 && (cmd[index][0] != '>' && \
			cmd[index][0] != '<'))
				new_blk[i++] = ft_strdup("(null)");
		else
			new_blk[i++] = ft_strdup(cmd[begin++]);
	}
	new_blk[i] = NULL;
	return (new_blk);
}

/**
 * Takes a splited command line and returns a 3D array of strings.
 */
char	***create_cmd(char **cmd, t_cmd *lst)
{
	int		end;
	int		i;
	int		begin;
	char	***block;

	end = 0;
	i = 0;
	lst->cmd_len = count_block(cmd);
	block = (char ***)malloc(sizeof(char **) * (lst->cmd_len + 1));
	while (i < lst->cmd_len)
	{
		begin = end;
		block[i] = create_blk(cmd, begin, &end, i);
		i++;
	}
	block[i] = NULL;
	return (block);
}
