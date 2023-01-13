/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2_dealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:34:51 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 15:30:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini2.h"

t_main_meta	g_meta;

void	ft_dealloc_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_dealloc_dptr(void ***ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_dealloc_tptr(void ****ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
