/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 04:15:10 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/23 23:48:10 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static int	get_len(int n);
static void	insert_num(int n, int sign, int len, char *str);

static int	get_len(int n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	while (n > 0)
	{
		n = (n - (n % 10)) / 10;
		len++;
	}
	return (len);
}

static void	insert_num(int n, int sign, int len, char *str)
{
	int	num;

	num = 0;
	*(str + len) = 0;
	while (len > 0)
	{
		num = n % 10;
		n = (n - num) / 10;
		len--;
		*(str + len) = num + '0';
	}
	if (sign == -1)
		*str = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		sign;

	sign = 1;
	len = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		sign = -1;
		n *= -1;
		len++;
	}
	len += get_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	insert_num(n, sign, len, str);
	return (str);
}
