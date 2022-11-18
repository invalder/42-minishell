/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_nbr1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:48:53 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:46:57 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

size_t	ft_nbrcnt(char *ptr)
{
	size_t	len;

	len = 0;
	while (ft_isdigit(*(ptr++)))
		len++;
	return (len);
}

size_t	ft_nbrsize(ssize_t n, ssize_t len)
{
	ssize_t	num;

	num = n;
	if (num < 0)
	{
		num *= -1;
	}
	if (num < 10)
		len++;
	else
	{
		len = ft_nbrsize((num - (num % 10)) / 10, len);
		len = ft_nbrsize((num % 10), len);
	}
	return (len);
}

char	*ft_print_nbr(ssize_t n, char *buff)
{
	ssize_t	num;

	num = n;
	if (num < 0)
		num *= -1;
	if (num < 10)
		buff = ft_append2str(buff, num + '0');
	else
	{
		buff = ft_print_nbr((num - (num % 10)) / 10, buff);
		buff = ft_print_nbr((num % 10), buff);
	}
	return (buff);
}

char	*ft_print_nbru_b(unsigned long long num, char *buff, int b, int shift)
{
	char	*base;

	base = ft_basenumber(b);
	if (b && num < (unsigned long long) b)
		buff = ft_append2str_ul(buff, base[num], shift);
	else if (b && num >= (unsigned long long) b)
	{
		buff = ft_print_nbru_b((num / b), buff, b, shift);
		buff = ft_print_nbru_b(num % b, buff, b, shift);
	}
	free(base);
	return (buff);
}

char	*ft_basenumber(int base)
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
