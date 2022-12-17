/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:17:37 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/17 10:50:24 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

t_main_meta	g_meta;

int	cmd_loop(t_main_meta *meta, char **envp)
{
	while (1)
	{
		while (ft_read_line(&meta->line, meta->pmt))
		{
			if (is_comment_line(meta->line))
				break ;
			if (!is_heredoc(&meta->line, &meta->input))
				break ;
			else
				ft_multiline_cmd(meta);
		}
		if (!meta->input)
			exit_eof(meta);
		add_history(meta->input);
		meta->tinput = ft_strtrim(meta->input, WHTSP);
		printf("debug:%s:\n", meta->tinput);

		meta_dealloc_input(meta);
		meta->pmt = PROMPT;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_meta.parent.pid = getpid();
	sa_initialize();
	meta_init(&g_meta);
	cmd_loop(&g_meta, envp);
}
