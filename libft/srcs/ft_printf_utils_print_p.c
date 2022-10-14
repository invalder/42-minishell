/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print_p.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:14:45 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:15:29 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_print_p(va_list ap, int *len, t_prefix *t_pf)
{
	char				*p_buff;
	unsigned long long	num;

	num = (unsigned long long)va_arg(ap, void *);
	p_buff = NULL;
	if (num)
	{
		p_buff = malloc(sizeof(char) * 3);
		if (!p_buff)
			return (NULL);
		ft_memcpy(p_buff, "0x", 3);
		p_buff = ft_print_nbru_b(num, p_buff, 16, 0);
	}
	else
	{
		p_buff = malloc(sizeof(char) * (P_EMPTY_L + 1));
		if (!p_buff)
			return (NULL);
		ft_memcpy(p_buff, P_EMPTY, (P_EMPTY_L + 1));
	}
	p_buff = ft_append_p(p_buff, t_pf);
	if (p_buff)
		*len += ft_strlen(p_buff);
	return (p_buff);
}

char	*ft_append_p(char *p_buff, t_prefix *t_pf)
{
	char	*ret_buff;
	char	*width_buff;
	size_t	len;

	len = ft_strlen(p_buff);
	if ((size_t)t_pf->width > len)
	{
		width_buff = ft_mycalloc(1, t_pf->width - len + 1, ' ');
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
