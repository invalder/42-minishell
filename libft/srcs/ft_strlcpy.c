/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:35:42 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/22 16:10:36 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen);

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (src_len + 1 < maxlen)
		ft_memcpy(dst, src, src_len + 1);
	else if (maxlen > 0)
	{
		ft_memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (ft_strlen(src));
}
