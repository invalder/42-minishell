/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:46:11 by nnakarac          #+#    #+#             */
/*   Updated: 2022/08/21 21:19:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *nptr);

static int	ft_base_check(char *nptr)
{
	if (ft_strncmp(nptr, "0X", 2) || ft_strncmp(nptr, "0x", 2))
		return (16);
	else if (ft_strncmp(nptr, "0O", 2) || ft_strncmp(nptr, "0o", 2))
		return (8);
	else if (ft_strncmp(nptr, "0B", 2) || ft_strncmp(nptr, "0b", 2))
		return (2);
	else
		return (10);
}

static int	ft_strchr_idx(const char *s, int c)
{
	char	*ps;
	int		idx;

	idx = 0;
	if (!*s && !c)
		return (-1);
	if (*s)
	{
		ps = (char *)s;
		while (*ps)
		{
			if (*ps == (char)c)
				return (idx);
			idx++;
			ps++;
		}
		if (c == 0)
			return (-1);
	}
	return (-1);
}

static int	ft_is_valid_number(char *nptr, int base)
{
	char	sample;

	sample = ft_tolower(*nptr);
	if (base == 16)
		return (ft_strchr_idx("0123456789abcdef", sample));
	else if (base == 10)
		return (ft_strchr_idx("0123456789", sample));
	else if (base == 8)
		return (ft_strchr_idx("01234567", sample));
	else if (base == 2)
		return (ft_strchr_idx("01", sample));
	else
		return (-1);
}

static char	*ft_basenumber(int base)
{
	char	*bres;

	bres = malloc(sizeof(char) * 17);
	if (!bres)
		return (NULL);
	if (base == 2)
		ft_strlcpy(bres, "01", 3);
	else if (base == 8)
		ft_strlcpy(bres, "01234567", 9);
	else if (base == 10)
		ft_strlcpy(bres, "0123456789", 11);
	else if (base == 16)
		ft_strlcpy(bres, "0123456789abcdef", 17);
	else
		ft_strlcpy(bres, "", 2);
	return (bres);
}

int	ft_atoi_base(char *nptr)
{
	int		sign;
	int		result;
	int		base;
	char	*str;

	sign = 1;
	result = 0;
	base = ft_base_check(nptr);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (base != 10)
		nptr += 2;
	while (ft_is_valid_number(nptr, base) != -1 && *nptr)
	{
		str = ft_basenumber(base);
		result = result * base + ft_strchr_idx(str, ft_tolower(*(nptr++)));
		free(str);
	}
	return (result * sign);
}
