/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 01:04:35 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/11 21:52:48 by sthitiku         ###   ########.fr       */
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

// return 1 if quote is not closed, 0 otherwise
int	check_close_quote(char *cmd)
{
	int		i;
	int		close;
	char	first_quote;

	close = 0;
	first_quote = 0;
	i = -1;
	if (!ft_strchr(cmd, '\'') && !ft_strchr(cmd, '\"'))
		return (1);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			first_quote = cmd[i++];
			while (cmd[i] && cmd[i] != first_quote)
			{
				i++;
			}
			if (cmd[i] == first_quote)
				close = 1;
			else
				close = 0;
		}
	}
	return (close);
}

int	check_dollar_in_sq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[i])
			{
				if (str[i] == '$')
					return (1);
				if (str[i] == '\"')
					return (0);
				i++;
			}
		}
		i++;
	}
	return (0);
}

char	*skip_quote(char *str)
{
	int		i;
	char	*new;

	i = 0;
	new = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] != '\'')
			new = ms_join_char(new, str[i]);
		i++;
	}
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
		while (cmd[i][++j])
		{
			printf("check: %d\n", check_dollar_in_sq(cmd[i][j]));
			if (check_dollar_in_sq(cmd[i][j]))
				cmd[i][j] = skip_quote(cmd[i][j]);
			else
			{
				cmd[i][j] = cut_quote(cmd[i][j], cmd[i][j][0]);
				printf("PARSE cmd[i][j]: %s\n", cmd[i][j]);
				if (ft_strchr(cmd[i][j], '$'))
					cmd[i][j] = parse_env(cmd[i][j]);
			}
		}
		i++;
	}
}
