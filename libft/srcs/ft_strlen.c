/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:04:09 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 17:52:11 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);

size_t	ft_strlen(const char *s)
{
	size_t		ret;
	const char	*ptr;

	ret = 0;
	ptr = s;
	if (s)
	{
		while (*ptr++)
			ret++;
	}
	return (ret);
}
