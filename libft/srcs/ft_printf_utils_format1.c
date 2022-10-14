/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_format1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 19:00:25 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 19:58:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*ft_appendfmt2(char *ptr, t_prefix *t_pf, va_list ap);
static char	*ft_printf_spec(char *ptr, va_list ap, int *len, t_prefix *t_pf);

char	*ft_appendfmt(char *buff, char *ptr, int *len, va_list ap)
{
	char			*new_buff;
	char			*p_buff;
	int				p_len;
	static t_prefix	t_pf;

	ft_freeprefix(&t_pf);
	p_len = *len;
	if (*(ptr) == '%')
		return (ft_appendchr(buff, ptr, len));
	ptr = ft_appendfmt2(ptr, &t_pf, ap);
	if (ft_specchk(ptr))
	{
		p_buff = ft_printf_spec(ptr, ap, len, &t_pf);
		if (!p_buff)
			return (ft_freemem(buff));
		new_buff = ft_mymemjoin(buff, p_buff, p_len, *len);
		free(buff);
		free(p_buff);
		if (!new_buff)
			return (ft_freemem(new_buff));
		return (new_buff);
	}
	free(buff);
	return (NULL);
}

static char	*ft_appendfmt2(char *ptr, t_prefix *t_pf, va_list ap)
{
	while (!ft_specchk(ptr))
	{
		ptr += ft_is_left(ptr, t_pf);
		ptr += ft_is_sign(ptr, t_pf);
		ptr += ft_is_space(ptr, t_pf);
		ptr += ft_is_preceed(ptr, t_pf);
		ptr += ft_is_iszero(ptr, t_pf);
		ptr += ft_is_width(ptr, t_pf, ap);
		ptr += ft_is_precision(ptr, t_pf, ap);
	}
	return (ptr);
}

static char	*ft_printf_spec(char *ptr, va_list ap, int *len, t_prefix *t_pf)
{
	char	*spec;

	spec = NULL;
	if (*ptr == 'c')
		spec = (ft_print_c(ap, len, t_pf));
	if (*ptr == 's')
		spec = (ft_print_s(ap, len, t_pf));
	if (*ptr == 'd' || *ptr == 'i')
		spec = (ft_print_d(ap, len, t_pf));
	if (*ptr == 'p')
		spec = (ft_print_p(ap, len, t_pf));
	if (*ptr == 'u')
		spec = (ft_print_u(ap, len, t_pf));
	if (*ptr == 'x')
		spec = (ft_print_x(ap, 0, t_pf, len));
	if (*ptr == 'X')
		spec = (ft_print_x(ap, 1, t_pf, len));
	ft_freeprefix(t_pf);
	return (spec);
}
