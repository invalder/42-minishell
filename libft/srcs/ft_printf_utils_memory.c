/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_memory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:42:03 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 17:43:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_freemem(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

char	*ft_mycalloc(size_t size, size_t len, char c)
{
	char	*buff;
	size_t	cnt;

	cnt = 0;
	if (len && size)
	{
		buff = malloc(size * len);
		if (!buff)
			return (NULL);
		while (cnt < len)
		{
			*(buff + cnt++) = c;
		}
		*(buff + cnt - 1) = 0;
		return (buff);
	}
	return (NULL);
}

char	*ft_mymemjoin(char *s1, char *s2, size_t len1, size_t len_t)
{
	char	*new_buff;

	new_buff = malloc(sizeof(char) * (len_t + 1));
	if (!new_buff)
		return (NULL);
	ft_memcpy(new_buff, s1, len1);
	ft_memcpy(new_buff + len1, s2, len_t - len1);
	*(new_buff + len_t) = 0;
	return (new_buff);
}
