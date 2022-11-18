/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:07:43 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 12:00:59 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	if (!s)
		return ;
	if (n == 0)
	{
		*ptr = 0;
		return ;
	}
	while (n-- > 0)
		*ptr++ = 0;
}
