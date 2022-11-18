/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print_u.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:14:52 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:15:50 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_print_u(va_list ap, int *len, t_prefix *t_pf)
{
	char			*p_buff;
	unsigned int	num;
	int				num_l;
	int				cur;

	cur = 0;
	num = (unsigned long long)va_arg(ap, void *);
	num_l = ft_nbrsize(num, 0);
	p_buff = NULL;
	if (t_pf->is_precision && t_pf->precision - num_l > 0)
	{
		while (t_pf->precision - num_l++)
			p_buff = ft_appendchr(p_buff, "0", &cur);
	}
	if (num == 0 && (t_pf->is_precision && t_pf->precision == 0))
		p_buff = ft_mystrjoin(p_buff, "", 1, 0);
	else
		p_buff = ft_print_nbru_b(num, p_buff, 10, 0);
	p_buff = ft_append_u(p_buff, t_pf);
	if (p_buff)
		*len += ft_strlen(p_buff);
	return (p_buff);
}

char	*ft_append_u(char *p_buff, t_prefix *t_pf)
{
	char	*ret_buff;
	char	*width_buff;
	size_t	len;
	char	append_chr;

	append_chr = ' ';
	len = ft_strlen(p_buff);
	if (t_pf->is_iszero && !t_pf->is_precision)
		append_chr = '0';
	if ((size_t)t_pf->width > len)
	{
		width_buff = ft_mycalloc(1, t_pf->width - len + 1, append_chr);
		if (t_pf->is_left)
			ret_buff = ft_mystrjoin(p_buff, width_buff, 1, 1);
		else
			ret_buff = ft_mystrjoin(width_buff, p_buff, 1, 1);
		return (ret_buff);
	}
	else
	{
		return (p_buff);
	}
}
