/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:04:35 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/05 17:45:48 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

extern int	g_status;

static char	*cut_quote(char *str, char quote)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] != quote)
			len++;
		i++;
	}
	new = malloc(sizeof(char) * len + 1);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != quote)
			new[len++] = str[i];
		i++;
	}
	new[len] = '\0';
	free(str);
	return (new);
}

static char	*parse_env_get_env(char *str, int str_len, char first, char last)
{
	char	*new;
	t_parse	p;

	p.start = 0;
	p.end = 0;
	if (first == '\'' && last == '\'')
	{
		p.start = 2;
		p.end = str_len - 2;
		p.sub = ft_substr(str, p.start, p.end - p.start + 1);
		p.env = getenv(p.sub);
		new = malloc(sizeof(char) * (ft_strlen(p.env) + 3));
		ft_strlcpy(new, "\'", 2);
		ft_strlcpy(&new[1], p.env, ft_strlen(p.env) + 1);
		ft_strlcpy(&new[ft_strlen(p.env) + 1], "\'", 2);
	}
	else
	{
		p.sub = ft_substr(str, p.start + 1, str_len - p.start - 1);
		parse_env_exit_status(&p, str_len);
		new = malloc(sizeof(char) * (ft_strlen(p.env) + 1));
		ft_strlcpy(new, p.env, ft_strlen(p.env) + 1);
	}
	free(p.sub);
	return (new);
}

static char	*parse_env(char *str)
{
	int		str_len;
	char	*new;

	str_len = ft_strlen(str);
	new = NULL;
	if (str[0] == '\"' && str[str_len - 1] == '\"')
	{
		new = malloc(sizeof(char) * str_len + 1);
		ft_strlcpy(new, str, str_len + 1);
	}
	else
		new = parse_env_get_env(str, str_len, str[0], str[str_len - 1]);
	free(str);
	return (new);
}

static void	parse_cmd_one_pair(char ***cmd, int i, int j, char first_char)
{
	if (first_char == '\"' || first_char == '\'')
		cmd[i][j] = cut_quote(cmd[i][j], first_char);
	if (first_char == '\'')
		return ;
	if (ft_strchr(cmd[i][j], '$') && cmd[i][j][0] != '\"')
		cmd[i][j] = parse_env(cmd[i][j]);
}

void	parse_cmd(char ***cmd)
{
	int		i;
	int		j;
	char	first_char;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][++j])
		{
			first_char = cmd[i][j][0];
			if (cmd[i][j][1] == '\'' || cmd[i][j][1] == '\"')
			{
				if ((first_char == '\'' || first_char == '\"'))
					cmd[i][j] = cut_quote(cmd[i][j], first_char);
				if (ft_strchr(cmd[i][j], '$') && cmd[i][j][0] != '\"')
					cmd[i][j] = parse_env(cmd[i][j]);
			}
			else
				parse_cmd_one_pair(cmd, i, j, first_char);
		}
		i++;
	}
}
