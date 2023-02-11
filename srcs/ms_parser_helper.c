/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:19:39 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 22:37:29 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

char	*cut_quote(char *str, char quote)
{
	int		i;
	int		close;
	char	*new;

	close = 1;
	i = 0;
	new = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (close)
				quote = str[i];
			if (str[i] == quote)
				close = !close;
			else
				new = ms_join_char(new, str[i]);
		}
		else
			new = ms_join_char(new, str[i]);
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

static char	get_char_to_join(char *env, int *st)
{
	if (env[*st] == '\'' || env[*st] == '\"')
		(*st)++;
	return (env[*st]);
}

static char	*get_env_str(char *env, char *rt)
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

// void	parse_env_get_env_helper(t_parse *p, char *str, int str_len, char **new)
// {
// 	p->sub = ft_substr(str, p->start, str_len - p->start);
// 	p->env = get_env_str(p->sub, ft_calloc(1, 1));
// 	parse_env_exit_status(p, str_len);
// 	*new = ft_calloc(1, ft_strlen(p->env) + 1);
// 	*new = ms_join_str(*new, p->env);
// }

char	*complicated_env(t_parse *p, char *str, int str_len)
{
	char	*new;
	char	*tmp;
	int		start;
	int		end;
	int		i;

	i = 0;
	new = ft_calloc(1, 1);
	end = str_len - 1;
	while (str[i] && str[i] != '$')
		i++;
	start = i;
	while ((end >= 0 && ft_isalnum(str[end])) || !str[end])
		end--;
	p->sub = ft_substr(str, start, end - start);
	p->env = get_env_str(p->sub, ft_calloc(1, 1));
	new = ms_join_str(new, ft_substr(str, 0, start - 0));
	new = ms_join_str(new, p->env);
	tmp = ft_substr(str, end, str_len - end);
	if (ft_strchr(tmp, '$'))
		new = ms_join_str(new, get_env_str(tmp, ft_calloc(1, 1)));
	else
		new = ms_join_str(new, tmp);
	return (new);
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
		p.env = get_env_str(p.sub, ft_calloc(1, 1));
		new = ft_calloc(1, 1);
		new = ms_join_char(new, '\'');
		new = ms_join_str(new, p.env);
		new = ms_join_char(new, '\'');
	}
	else
	{
		p.env = complicated_env(&p, str, str_len);
		parse_env_exit_status(&p, str_len, str);
		new = ft_calloc(1, 1);
		new = ms_join_str(new, p.env);
	}
	free(p.sub);
	return (new);
}
