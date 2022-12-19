/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:04:35 by sthitiku          #+#    #+#             */
/*   Updated: 2022/12/20 01:08:25 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

static char	*cut_quote(char *str)
{
	int		start;
	int		end;
	char	*new;
	char	tmp;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"')
		{
			tmp = str[end];
			start = end + 1;
			while (str[++end] != tmp);
			break ;
		}
		end++;
	}
	new = malloc(sizeof(char) * end - start + 1);
	ft_strlcpy(new, &str[start], end - start + 1);
	free(str);
	return (new);
}

static char	*parse_env(char *str)
{
	int		s_len;
	char	*new;
	char	*tmp;

	tmp = getenv("HOME");
	s_len = ft_strlen(tmp);
	new = malloc(sizeof(char) * s_len + 3);
	ft_strlcpy(new, "\'", 2);
	ft_strlcpy(&new[1], tmp, s_len + 1);
	ft_strlcpy(&new[s_len + 1], "\'", 2);
	free(str);
	return (new);
}

void	parse_cmd(char ***cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j][0] == '\'' || cmd[i][j][0] == '\"')
				cmd[i][j] = cut_quote(cmd[i][j]);
			if (cmd[i][j][0] == '\'' && ft_strchr(cmd[i][j], '$'))
				cmd[i][j] = parse_env(cmd[i][j]);
			printf("%s\n", cmd[i][j]);
			j++;
		}
		i++;
	}
}
