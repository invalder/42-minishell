/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_format3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:45:15 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 22:46:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	ft_is_left(char *ptr, t_prefix *t_pf)
{
	if (*ptr == '-')
	{
		t_pf->is_left = 1;
		return (1);
	}
	return (0);
}

int	ft_is_sign(char *ptr, t_prefix *t_pf)
{
	if (*ptr == '+')
	{
		t_pf->is_sign = 1;
		return (1);
	}
	return (0);
}

int	ft_is_space(char *ptr, t_prefix *t_pf)
{
	if (*ptr == ' ')
	{
		t_pf->is_space = 1;
		return (1);
	}
	return (0);
}

int	ft_is_preceed(char *ptr, t_prefix *t_pf)
{
	if (*ptr == '#')
	{
		t_pf->is_preceed = 1;
		return (1);
	}
	return (0);
}
