/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:04:35 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 13:52:01 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

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
	{
		cmd[i][j] = cut_quote(cmd[i][j], first_char);
		if (cmd[i][j][0] == '$')
		{
			cmd[i][j] = ft_substr(cmd[i][j], 0, ft_strlen(cmd[i][j]));
			return ;
		}
	}
	if (cmd[i][j][0] == '\'')
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
