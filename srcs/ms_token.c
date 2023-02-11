/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:46 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 21:43:48 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

static void	skip_token_3(char *line, int *i, char tmp)
{
	char	tmp_quote;

	tmp_quote = tmp;
	printf("3 line = %s\n", line);
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
			line[*i] != '<' && line[*i] != '>' && line[*i] != '&' && \
			line[*i] != '=')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			tmp_quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != tmp_quote)
				(*i)++;
		}
		(*i)++;
	}
}

static void	skip_token_2(char *ln, int *i, char tmp)
{
	char	qte;
	int		close;

	qte = 0;
	close = 0;
	(*i)++;
	while (ln[*i])
	{
		if (ln[*i] == '\'' || ln[*i] == '\"')
		{
			tmp = ln[*i];
			while (ln[*i] && ln[*i] != tmp && ln[*i] != '|')
				(*i)++;
			if (ln[*i] == tmp)
				close = 1;
			else
				close = 0;
		}
		(*i)++;
	}
}

void	skip_token(char *line, int *i, int mode)
{
	char	tmp;

	tmp = line[*i];
	printf("line = %s\tmode = %d\n", line, mode);
	printf("tmp: %c\n", tmp);
	if (mode == 1)
	{
		if (line[*i + 1] == tmp)
			*i += 2;
		else
			(*i)++;
	}
	else if (mode == 2)
		skip_token_2(line, i, tmp);
	else
		skip_token_3(line, i, tmp);
}
