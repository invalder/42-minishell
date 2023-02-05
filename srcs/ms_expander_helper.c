/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:17:59 by sthitiku          #+#    #+#             */
/*   Updated: 2023/02/06 00:44:42 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ms_input.h"

char	find_sep(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (ft_isalnum(str[i]) || str[i] == '$')
			continue ;
		else
			break ;
		i++;
	}
	return (str[i]);
}

int	find_sep_index(char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == sep)
			break ;
		i++;
	}
	return (i);
}

char	*ms_join_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) + 2);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	if (str)
		free(str);
	return (new);
}

char	*ms_join_str(char *str1, char *str2)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (str1)
	{
		while (str1[i])
			new[i++] = str1[j++];
	}
	j = 0;
	if (str2)
	{
		while (str2[j])
			new[i++] = str2[j++];
	}
	new[i] = '\0';
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (new);
}

char	*expand_env(char *env)
{
	char	*ret;

	ret = NULL;
	if (getenv(env))
		ret = strdup(getenv(env));
	free(env);
	return (ret);
}
