/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:39:24 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/22 22:46:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c);

char	*ft_strchr(const char *s, int c)
{
	char	*ps;

	if (!*s && !c)
		return ((char *)s);
	if (*s)
	{
		ps = (char *)s;
		while (*ps)
		{
			if (*ps == (char)c)
				return (ps);
			ps++;
		}
		if (c == 0)
			return (ps);
	}
	return (NULL);
}
