/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_meta.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 00:45:56 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/17 01:00:01 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

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
