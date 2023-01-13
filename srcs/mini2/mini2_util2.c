/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:06:12 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 15:29:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini2.h"

extern t_main_meta	g_meta;

void	ft_multiline_cmd(t_main_meta *meta)
{
	meta->subline = ft_substr(meta->line, 0, ft_strlen(meta->line) - 1);
	meta->input = ft_mystrjoin(meta->input, meta->subline, \
		ft_strlen(meta->input), ft_strlen(meta->subline));
	ft_dealloc_ptr((void **) &meta->line);
	meta->pmt = SPROMPT;
}
