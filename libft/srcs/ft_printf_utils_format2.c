/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_format2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 20:00:14 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 20:05:10 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	ft_flgchk(char *ptr)
{
	if (*ptr == '-' || *ptr == '+' || *ptr == ' ' || *ptr == '#' || *ptr == '0')
		return (1);
	return (0);
}

size_t	ft_widthchk(char *ptr)
{
	if (*ptr == '*')
		return (1);
	if (ft_isdigit(*ptr))
	{
		return (ft_nbrcnt(ptr));
	}
	return (0);
}

size_t	ft_precisechk(char *ptr)
{
	if (*ptr == '.')
	{
		if (*(ptr + 1) == '*')
			return (2);
		else if (ft_isdigit(*(ptr + 1)))
			return (ft_nbrcnt(ptr + 1) + 1);
		else
			return (1);
	}
	return (0);
}

size_t	ft_specchk(char *ptr)
{
	if (*ptr == 'c' || *ptr == 's' || *ptr == 'd' || *ptr == 'i' || \
	*ptr == 'p' || *ptr == 'u' || *ptr == 'o' || *ptr == 'x' || *ptr == 'X')
		return (1);
	return (0);
}

void	ft_freeprefix(t_prefix *t_pf)
{
	t_pf->is_left = 0;
	t_pf->is_sign = 0;
	t_pf->is_space = 0;
	t_pf->is_preceed = 0;
	t_pf->is_iszero = 0;
	t_pf->width = 0;
	t_pf->precision = 0;
	t_pf->is_precision = 0;
}
