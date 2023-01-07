/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2_meta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:27:41 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 15:27:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini2.h"

extern t_main_meta	g_meta;

void	meta_init(t_main_meta *meta)
{
	meta->line = NULL;
	meta->input = NULL;
	meta->subline = NULL;
	meta->pmt = PROMPT;
	meta->tinput = NULL;
}

void	meta_dealloc_input(t_main_meta *meta)
{
	ft_dealloc_ptr((void **) &meta->line);
	ft_dealloc_ptr((void **) &meta->input);
	ft_dealloc_ptr((void **) &meta->tinput);
}
