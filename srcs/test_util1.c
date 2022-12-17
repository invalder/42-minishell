/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:10:00 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/17 01:13:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

extern t_main_meta	g_meta;

void	ft_dealloc_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*ft_read_line(char **ptr, char *pmt)
{
	*ptr = readline(pmt);
	return (*ptr);
}

int	is_comment_line(char *line)
{
	if (ft_strncmp(line, "#", 1))
		return (0);
	ft_dealloc_ptr((void **)&line);
	return (1);
}

int	is_heredoc(char **line, char **input)
{
	if ((size_t)(ft_strrchr(*line, '\\') - *line) != ft_strlen(*line) - 1)
	{
		*input = ft_mystrjoin(*input, *line, ft_strlen(*input), \
			ft_strlen(*line));
		*line = NULL;
		return (0);
	}
	return (1);
}

void	exit_eof(t_main_meta *meta)
{
	rl_clear_history();
	meta_dealloc_input(meta);
	exit(0);
}
