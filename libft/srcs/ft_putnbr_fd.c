/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:28:32 by nnakarac          #+#    #+#             */
/*   Updated: 2022/02/22 18:37:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	int	neg;
	int	num;

	neg = 0;
	num = n;
	if (num == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (num < 0)
		{
			num *= -1;
			neg = 1;
		}
		if (neg)
			ft_putchar_fd('-', fd);
		if (num < 10)
			ft_putchar_fd(num + '0', fd);
		else
		{
			ft_putnbr_fd((num - (num % 10)) / 10, fd);
			ft_putchar_fd((num % 10) + '0', fd);
		}
	}
}
