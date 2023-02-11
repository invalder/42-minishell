/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:01:34 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/13 02:30:52 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	char	*ps1;
	char	*ps2;

	ps1 = (char *)s1;
	ps2 = (char *)s2;
	while (n > 0 && (*ps1 && *ps2))
	{
		if (*ps1++ != *ps2++)
			return ((unsigned char)*(--ps1) - (unsigned char)*(--ps2));
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)*ps1 - (unsigned char)*ps2);
}
