/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:11:17 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 14:35:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_d;
	unsigned char	*ptr_s;

	if (dest == NULL && src == NULL)
		return (dest);
	if (dest < src)
	{
		ptr_d = (unsigned char *)dest;
		ptr_s = (unsigned char *)src;
		while (n-- > 0)
			*ptr_d++ = *ptr_s++;
	}
	else
	{
		ptr_d = (unsigned char *)dest + (n - 1);
		ptr_s = (unsigned char *)src + (n - 1);
		while (n-- > 0)
		{
			*ptr_d-- = *ptr_s--;
		}
	}
	return (dest);
}
