/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:19:39 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/09 23:00:17 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

char	*cut_quote(char *str, char quote)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = 0;
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

static char	get_char_to_join(char *env, int *st)
{
	if (env[*st] == '\'' || env[*st] == '\"')
		(*st)++;
	return (env[*st]);
}

static char	*get_env_from_string(char *env, char *rt) 
{
	int		st;
	int		sp;
	char	sep;
	
	st = -1;
	sep = 0;
	while (env[++st])
	{
		sp = st;
		if (env[st] != '$')
		{
			rt = ms_join_char(rt, get_char_to_join(env, &st));
			continue ;
		}
		sep = find_sep(&env[st]);
		sp = st + find_sep_index(&env[st], sep);
		rt = ms_join_str(rt, expand_env(ft_substr(env, st + 1, sp - st - 1)));
		st = sp - 1;
	}
	return (rt);
}

char	*parse_env_get_env(char *str, int str_len, char first, char last)
{
	char	*new;
	t_parse	p;

	p.start = 0;
	p.end = 0;
	if (first == '\'' && last == '\'')
	{
		p.start = 1;
		p.end = str_len - 1;
		p.sub = ft_substr(str, p.start, p.end - p.start);
		p.env = get_env_from_string(p.sub, malloc(1));
		new = malloc(1);
		new = ms_join_char(new, '\'');
		new = ms_join_str(new, p.env);
		new = ms_join_char(new, '\'');
	}
	else
	{
		p.sub = ft_substr(str, p.start, str_len - p.start);
		p.env = get_env_from_string(p.sub, malloc(1));
		new = malloc(sizeof(char) * ft_strlen(p.env) + 1);
		new = ms_join_str(new, p.env);
	}
	free(p.sub);
	return (new);
}
