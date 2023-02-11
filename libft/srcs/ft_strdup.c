/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:13:02 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/05 15:40:35 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s);

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ret;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		ft_memcpy(ret, s, len + 1);
	}
	else
		return (NULL);
	return (ret);
}
