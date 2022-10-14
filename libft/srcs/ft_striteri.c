/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 17:25:17 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 15:12:37 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	char	*ps;
	int		len;

	if (!s)
		return ;
	ps = s;
	len = 0;
	if (!*ps)
		f(len, ps);
	while (*ps)
	{
		f(len++, ps++);
	}
}
