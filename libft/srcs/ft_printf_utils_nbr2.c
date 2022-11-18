/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_nbr2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:48:53 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:47:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	ft_nbrusize_base(size_t n, size_t len, size_t b)
{
	size_t	num;

	num = n;
	if (num < b)
		len++;
	else
	{
		len = ft_nbrusize_base((num - (num % b)) / b, len, b);
		len = ft_nbrusize_base((num % b), len, b);
	}
	return (len);
}
