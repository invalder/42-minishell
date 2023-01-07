/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_dealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:34:51 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/17 13:36:27 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

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
