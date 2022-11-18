/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:47:55 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/22 16:10:53 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	char	*ps;

	if (*s)
	{
		ps = (char *)s;
		ps += ft_strlen(s) - 1;
		if (c == 0)
			return (ps + 1);
		while (*ps && ps >= s)
		{
			if (*ps == (char)c)
				return (ps);
			ps--;
		}
	}
	else
		if (*s == c)
			return ((char *)s);
	return (NULL);
}
