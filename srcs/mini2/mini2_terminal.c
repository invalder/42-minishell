/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:26:01 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/07 15:02:14 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini2.h"

extern t_main_meta	g_meta;

int	cmd_loop(t_main_meta *meta)
{
	char	**tokens;
	// char	**ptokens;

	// tokens = NULL;
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
		if (!meta->input || !ft_strncmp(meta->input, "exit\0", 5))
			exit_eof(meta);
		add_history(meta->input);
		meta->tinput = ft_strtrim(meta->input, WHTSP);
		printf("tinput:%s\n", meta->tinput);
		tokens = ft_tokenizer(meta->tinput);
		//trim
		//split


		// tokens = ft_split_input(meta->tinput);
		// ptokens = tokens;
		// while (*ptokens)
		// {
		// 	printf("token: %s\n", *ptokens);
		// 	ptokens++;
		// }
		meta_dealloc_input(meta);
		meta->pmt = PROMPT;
	}
}
