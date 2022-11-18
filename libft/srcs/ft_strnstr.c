/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:09:05 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/22 16:10:49 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strmatch(char *str, char *keyword, size_t len);
char		*ft_strnstr(const char	*big, const char *little, size_t len);

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	char	*p_big;
	char	*p_search;
	size_t	llen;

	if (*big && *little)
	{
		llen = len;
		p_big = (char *)big;
		while (*p_big && llen > 0)
		{
			p_search = (char *)little;
			if (*p_big == *p_search)
				if (ft_strmatch(p_big, p_search, llen))
					return (p_big);
			p_big++;
			llen--;
		}
		return (NULL);
	}
	if ((*big == 0 && *little == 0) || len == 0)
		return ((char *)big);
	if (*little == 0)
		return ((char *)big);
	return (NULL);
}

static int	ft_strmatch(char *str, char *keyword, size_t len)
{
	int	found;

	found = 0;
	if (ft_strlen(keyword) > len)
		return (0);
	while (*keyword && len > 0)
	{
		if (*str == *keyword)
			found = 1;
		else
			return (0);
		keyword++;
		str++;
		len--;
	}
	return (found);
}
