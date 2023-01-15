/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:00:44 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/15 19:48:29 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

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

char	*cmd_cpy(char *curr_cmd, int char_count)
{
	char	*cmd;
	int		i;

	cmd = (char *)malloc(sizeof(char) * (char_count + 1));
	i = 0;
	while (i < char_count)
	{
		cmd[i] = curr_cmd[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

/**
 * Special split function to split char* into char** by tokens.
 * 
 * @param line: char* to be split
 * @return: char** of split char*
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
		if (!check_close_quote(cmd[i]))
			return(free_split(cmd));
		i++;
		j += char_count;
	}
	cmd[i] = NULL;
	return (cmd);
}
