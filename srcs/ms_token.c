/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 23:44:46 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/07 00:34:10 by sthitiku         ###   ########.fr       */
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

static void	skip_token_2(char *line, int *i, int mode, char tmp)
{
	if (mode == 2)
	{
		// printf("mode 2 line[%d] = %s\n", *i, &line[*i]);
		(*i)++;
		while (line[*i] && line[*i] != tmp)
		{
			// printf("line[%d] = %c\ttmp = %c\n", *i, line[*i], tmp);
			// if (line[*i] == tmp && (line[*i + 1] == '\'' || line[*i + 1] == '\"'))
			if (line[*i + 1] == '\'' || line[*i + 1] == '\"')
				(*i) += 2;
			// printf("SECOND IF line[%d] = %c\n", *i, line[*i]);
			(*i)++;
			// if (line[*i] == tmp)
			// 	(*i)++;
			// if (line[*i] == tmp && line[*i + 1] != ' ')
			// 	break ;
		}
		if (line[*i])
			(*i)++;
	}
	else if (mode == 3)
	{
		// if ((line[*i] == '\"' || line[*i] == '\'') && line[*i - 1] == ' ')
		// 	(*i)++;
		while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
				line[*i] != '<' && line[*i] != '>' && line[*i] != '&')
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
