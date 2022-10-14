/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print_x.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:14:57 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:16:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_print_x(va_list ap, int is_shift, t_prefix *t_pf, int *len)
{
	char			*p_buff;
	unsigned int	num;
	int				num_l;
	int				cur;

	num = (unsigned long long)va_arg(ap, void *);
	num_l = ft_nbrusize_base(num, 0, 16);
	p_buff = NULL;
	cur = 0;
	if (t_pf->is_precision && t_pf->precision - num_l > 0)
	{
		while (t_pf->precision - num_l++)
			p_buff = ft_appendchr(p_buff, "0", &cur);
	}
	if (num == 0 && (t_pf->is_precision && t_pf->precision == 0))
		p_buff = ft_mystrjoin(p_buff, "", 1, 0);
	else
		p_buff = ft_print_nbru_b(num, p_buff, 16, is_shift);
	p_buff = ft_append_x(p_buff, t_pf, is_shift, num);
	if (p_buff)
		*len += ft_strlen(p_buff);
	return (p_buff);
}

char	*ft_append_x(char *p_buff, t_prefix *t_pf, int up, unsigned int n)
{
	size_t	len;

	len = ft_strlen(p_buff);
	if ((size_t)t_pf->width > len)
	{
		return (ft_append_x_2(p_buff, t_pf, up, n));
	}
	else
		return (ft_append_zx(p_buff, t_pf, up, n));
}

char	*ft_append_x_2(char *p_buff, t_prefix *t_pf, int up, unsigned int n)
{
	char	*ret_buff;
	char	*width_buff;
	size_t	len;
	char	append_c;
	int		sharp_l;

	append_c = ' ';
	sharp_l = 0;
	if (t_pf->is_preceed)
		sharp_l = 2;
	len = ft_strlen(p_buff);
	if (t_pf->is_iszero && !t_pf->is_precision)
		append_c = '0';
	width_buff = ft_mycalloc(1, t_pf->width - len - sharp_l + 1, append_c);
	if (t_pf->is_left)
	{
		p_buff = ft_append_zx(p_buff, t_pf, up, n);
		ret_buff = ft_mystrjoin(p_buff, width_buff, 1, 1);
	}
	else
	{
		ret_buff = ft_mystrjoin(width_buff, p_buff, 1, 1);
		ret_buff = ft_append_zx(ret_buff, t_pf, up, n);
	}
	return (ret_buff);
}

char	*ft_append_zx(char *buff, t_prefix *t_pf, int up, unsigned int num)
{
	if (t_pf->is_preceed && num > 0)
	{
		if (up)
			buff = ft_mystrjoin("0X", buff, 0, 1);
		else
			buff = ft_mystrjoin("0x", buff, 0, 1);
	}
	return (buff);
}
