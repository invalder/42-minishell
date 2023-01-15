/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:04:35 by sthitiku          #+#    #+#             */
/*   Updated: 2023/01/08 01:50:26 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

// static char	*cut_quote(char *str)
// {
// 	int		start;
// 	int		end;
// 	char	*new;
// 	char	tmp;

// 	start = 0;
// 	end = 0;
// 	while (str[end])
// 	{
// 		if (str[end] == '\'' || str[end] == '\"')
// 		{
// 			tmp = str[end];
// 			start = end + 1;
// 			while (str[++end] != tmp);
// 			break ;
// 		}
// 		end++;
// 	}
// 	new = malloc(sizeof(char) * end - start + 1);
// 	ft_strlcpy(new, &str[start], end - start + 1);
// 	free(str);
// 	return (new);
// }

static char	*cut_quote(char *str, char quote)
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

// static char	*parse_env(char *str)
// {
// 	int		tmp_len;
// 	int		str_len;
// 	int		i;
// 	char	*new;
// 	char	*tmp;

// 	i = 0;
// 	while (str[i] && (str[i] == '\'' || str[i] == '\"'))
// 		i++;
// 	printf("str = %s\n", &str[i + 1]);
// 	printf("%d\n", i);
// 	tmp = getenv(&str[i + 1]);
// 	tmp_len = ft_strlen(tmp);
// 	str_len = ft_strlen(str);
// 	if (str[0] == '\"' && str[str_len - 1] == '\"')
// 		new = malloc(sizeof(char) * str_len + 1);
// 	else
// 		new = malloc(sizeof(char) * tmp_len + 3);
// 	if (str[0] == '\'' && str[str_len - 1] == '\'')
// 	{
// 		ft_strlcpy(new, "\'", 2);
// 		printf("1 new = %s\n", new);
// 		printf("tmp = %s\n", tmp);
// 		ft_strlcpy(&new[1], tmp, tmp_len + 1);
// 		printf("2 new = %s\n", new);
// 		ft_strlcpy(&new[tmp_len + 1], "\'", 2);
// 		printf("3 new = %s\n", new);
// 	}
// 	else if (str[0] == '\"' && str[str_len - 1] == '\"')
// 	{
// 	// 	ft_strlcpy(new, "\"", 2);
// 		ft_strlcpy(new, str, str_len + 1);
// 	// 	ft_strlcpy(&new[str_len + 1], "\"", 2);
// 	}
// 	else
// 		ft_strlcpy(new, tmp, tmp_len + 1);
// 	free(str);
// 	return (new);
// }

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
		new = malloc(sizeof(char) * ft_strlen(p.env) + 3);
		ft_strlcpy(new, "\'", 2);
		ft_strlcpy(&new[1], p.env, ft_strlen(p.env) + 1);
		ft_strlcpy(&new[ft_strlen(p.env) + 1], "\'", 2);
	}
	else
	{
		p.sub = ft_substr(str, p.start + 1, str_len - p.start - 1);
		p.env = getenv(p.sub);
		new = malloc(sizeof(char) * ft_strlen(p.env) + 1);
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

void	parse_cmd(char ***cmd)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			tmp = cmd[i][j][0];
			if (tmp == '\'' || tmp == '\"')
				cmd[i][j] = cut_quote(cmd[i][j], tmp);
			if (ft_strchr(cmd[i][j], '$'))
				cmd[i][j] = parse_env(cmd[i][j]);
			j++;
		}
		i++;
	}
}
