/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:19:39 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/06 00:45:55 by sthitiku         ###   ########.fr       */
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

char	*get_env_from_string(char *env)
{
	int		start;
	int		stop;
	char	sep;
	char	*ret;

	ret = malloc(1);
	start = -1;
	sep = 0;
	while (env[++start])
	{
		stop = start;
		if (env[start] != '$')
		{
			ret = ms_join_char(ret, env[start]);
			continue ;
		}
		sep = find_sep(&env[start]);
		stop = start + find_sep_index(&env[start], sep);
		ret = ms_join_str(ret, expand_env(ft_substr(env, start + 1, stop - start - 1)));
		start = stop - 1;
	}
	free(env);
	return (ret);
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
		p.env = get_env_from_string(p.sub);
		new = malloc(sizeof(char) * ft_strlen(p.env) + 3);
		ft_strlcpy(new, "\'", 2);
		new = ms_join_str(new, p.env);
		ft_strlcpy(&new[ft_strlen(p.env) + 1], "\'", 2);
	}
	else
	{
		p.sub = ft_substr(str, p.start, str_len - p.start);
		p.env = get_env_from_string(p.sub);
		new = malloc(sizeof(char) * ft_strlen(p.env) + 1);
		new = ms_join_str(new, p.env);
	}
	return (new);
}
