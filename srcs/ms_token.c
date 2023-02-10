/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:46 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/10 23:55:14 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

// return 1 if quote is not closed, 0 otherwise
// int check_close_quote(char *cmd)
// {
// 	int		i;
// 	int		close;
// 	char	first_quote;

// 	close = 0;
// 	first_quote = cmd[0];
// 	i = 1;
// 	if (first_quote != '\'' && first_quote != '\"')
// 		return (-1);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == first_quote)
// 			close = 1;
// 		i++;
// 	}
// 	return (close);
// }
static void skip_token_3(char *line, int *i, char tmp)
{
	char	tmp_quote;

	tmp_quote = tmp;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
			line[*i] != '<' && line[*i] != '>' && line[*i] != '&')
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

static void	skip_token_2(char *line, int *i, char tmp)
{
	// printf("line: %s, i: %d, mode: %d, tmp: %c\n", line, *i, mode, tmp);
	// if (mode == 2)
	// {
	(*i)++;
	// printf("IF line: %s, i: %d, mode: %d, tmp: %c\n", line, *i, mode, tmp);
	while (line[*i] && line[*i] != tmp)
	{
		if (line[*i + 1] == '\'' || line[*i + 1] == '\"')
			(*i) += 2;
		(*i)++;
	}
	if (line[*i])
		(*i)++;
	// }
	// else if (mode == 3)
	// {
	// 	printf("MODE 3 line[%d]: %c, tmp: %c\n", *i, line[*i], tmp);
	// 	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
	// 			line[*i] != '<' && line[*i] != '>' && line[*i] != '&')
	// 	{
	// 		if (line[*i + 1] == '\'' || line[*i + 1] == '\"')
	// 		{
	// 			while ()
	// 		}
	// 		(*i)++;
	// 	}
	// }
}

void	skip_token(char *line, int *i, int mode)
{
	char	tmp;

	// printf("line: %s, i: %d, mode: %d\n", line, *i, mode);
	tmp = line[*i];
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
