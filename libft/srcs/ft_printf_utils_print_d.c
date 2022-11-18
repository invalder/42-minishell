/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print_d.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:14:35 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:15:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_print_d(va_list ap, int *len, t_prefix *t_pf)
{
	char	*p_buff;
	ssize_t	num;

	p_buff = NULL;
	num = va_arg(ap, int);
	p_buff = ft_print_d_2(num, t_pf);
	if (num == 0 && (t_pf->is_precision && t_pf->precision == 0))
		p_buff = ft_mystrjoin(p_buff, "", 1, 0);
	else
		p_buff = ft_print_nbr(num, p_buff);
	p_buff = ft_append_d(p_buff, t_pf, ft_strlen(p_buff), num);
	if (p_buff)
		*len += ft_strlen(p_buff);
	return (p_buff);
}

char	*ft_print_d_2(ssize_t num, t_prefix *t_pf)
{
	char	*p_buff;
	int		num_l;
	int		neg;
	int		cur;

	cur = 0;
	neg = 0;
	p_buff = NULL;
	if (num < 0)
		neg = 1;
	num_l = ft_nbrsize(num, 0);
	if (t_pf->is_sign || t_pf->is_space)
	{
		if (t_pf->is_sign && !neg)
			p_buff = ft_appendchr(p_buff, "+", &cur);
		else if (t_pf->is_space && !neg)
			p_buff = ft_appendchr(p_buff, " ", &cur);
	}
	if (t_pf->is_precision && t_pf->precision - num_l > 0)
	{
		while (t_pf->precision - num_l++)
			p_buff = ft_appendchr(p_buff, "0", &cur);
	}
	return (p_buff);
}

char	*ft_append_d(char *p_buff, t_prefix *t_pf, size_t len, ssize_t num)
{
	int		neg;

	neg = 0;
	if (num < 0)
		neg = 1;
	if ((size_t)t_pf->width > len + neg)
	{
		return (ft_append_d_2(p_buff, t_pf, len, num));
	}
	else
	{
		if (neg)
			p_buff = ft_mystrjoin("-", p_buff, 0, 1);
		return (p_buff);
	}
}

char	*ft_append_d_2(char *p_buff, t_prefix *t_pf, size_t len, ssize_t num)
{
	char	*width_buff;
	char	*ret_buff;
	char	append_chr;
	int		neg;

	width_buff = NULL;
	ret_buff = NULL;
	append_chr = ' ';
	neg = 0;
	if (num < 0)
		neg = 1;
	if (t_pf->is_iszero && !t_pf->is_precision && !t_pf->is_left)
		append_chr = '0';
	if (neg && t_pf->is_precision)
		p_buff = ft_mystrjoin("-", p_buff, 0, 1);
	width_buff = ft_mycalloc(1, t_pf->width - (len + neg) + 1, append_chr);
	ret_buff = ft_append_d_3(p_buff, t_pf, width_buff, num);
	width_buff = NULL;
	return (ret_buff);
}

char	*ft_append_d_3(char *p_buff, t_prefix *t_pf, char *wbuff, ssize_t num)
{
	char	*ret_buff;
	char	append_chr;
	int		neg;

	append_chr = ' ';
	neg = 0;
	if (num < 0)
		neg = 1;
	if (t_pf->is_iszero && !t_pf->is_precision)
		append_chr = '0';
	if (t_pf->is_left)
	{
		ret_buff = ft_mystrjoin(p_buff, wbuff, 1, 1);
		if (neg && !t_pf->is_precision)
			ret_buff = ft_mystrjoin("-", ret_buff, 0, 1);
	}
	else
	{
		if (neg && !t_pf->is_precision && append_chr != '0')
			p_buff = ft_mystrjoin("-", p_buff, 0, 1);
		ret_buff = ft_mystrjoin(wbuff, p_buff, 1, 1);
		if (neg && append_chr == '0')
			ret_buff = ft_mystrjoin("-", ret_buff, 0, 1);
	}
	return (ret_buff);
}
