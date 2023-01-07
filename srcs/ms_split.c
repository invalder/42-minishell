/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:00:44 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/07 18:32:34 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

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
	else if (mode == 2)
	{
		(*i)++;
		while (line[*i] && line[*i] != tmp)
		{
			(*i)++;
			// printf("line[%d] = %c\n", *i, line[*i]);
			// printf("line[%d + 1] = %c\n", *i, line[*i + 1]);
			// printf("line[%d + 2] = %c\n", *i, line[*i + 2]);
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

static int	ms_count_words(char *line)
{
	int		words;
	int		i;

	words = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue ;
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>'
			|| line[i] == '&')
			skip_token(line, &i, 1);
		else if (line[i] == '\'' || line[i] == '\"')
			skip_token(line, &i, 2);
		else
			skip_token(line, &i, 3);
		words++;
	}
	return (words);
}

static int	ms_count_chars(char *str)
{
	int		i;
	char	tmp;

	i = 0;
	tmp = str[i];
	if (str[i] == '\'' || str[i] == '\"')
		skip_token(str, &i, 2);
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&')
	{
		if (str[i + 1] == tmp)
			return (2);
		else
			return (1);
	}
	else
		skip_token(str, &i, 3);
	return (i);
}

/**
 * Special split function to split char* into char** by tokens.
 */
char	**cmd_split(char *line)
{
	int		cmd_count;
	int		char_count;
	int		i;
	int		j;
	char	**cmd;

	cmd_count = ms_count_words(line);
	cmd = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	i = 0;
	j = 0;
	while (i < cmd_count)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		char_count = ms_count_chars(&line[j]);
		cmd[i] = (char *)malloc(sizeof(char) * (char_count + 1));
		ft_strlcpy(cmd[i], &line[j], char_count + 1);
		i++;
		j += char_count;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
