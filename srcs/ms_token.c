/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:46 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/15 01:02:19 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

// return 1 if quote is not closed, 0 otherwise
int	check_quote(char **cmd)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (cmd[i])
	{
		quote = cmd[i][0];
		j = 1;
		while (cmd[i][j])
		{
			if (cmd[i][j] == quote)
				break ;
			j++;
		}
		i++;
	}
	if (quote != 0)
		return (1);
	return (0);
}

static void	skip_token_2(char *line, int *i, int mode, char tmp)
{
	if (mode == 2)
	{
		(*i)++;
		while (line[*i] && line[*i] != tmp)
		{
			(*i)++;
			if (line[*i] == tmp && (line[*i + 1] == '\'' || line[*i + 1] == '\"'))
				(*i) += 2;
			else if (line[*i] == tmp && line[*i + 1] != ' ')
				break ;
		}
		if (line[*i])
			(*i)++;
	}
	else if (mode == 3)
	{
		while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
				line[*i] != '<' && line[*i] != '>' && line[*i] != '&' && \
				line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
	}
}

void	skip_token(char *line, int *i, int mode)
{
	char	tmp;

	tmp = line[*i];
	if (mode == 1)
	{
		if (line[*i + 1] == tmp)
			*i += 2;
		else
			(*i)++;
	}
	else
		skip_token_2(line, i, mode, tmp);
}
