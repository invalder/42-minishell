/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print_c.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:12:50 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 19:13:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_print_c(va_list ap, int *len, t_prefix *t_pf)
{
	char	*p_buff;

	p_buff = malloc(sizeof(char) * 2);
	if (!p_buff)
		return (NULL);
	*p_buff = (char) va_arg(ap, int);
	*(p_buff + 1) = 0;
	*len += 1;
	p_buff = ft_append_c(p_buff, t_pf, len);
	return (p_buff);
}

char	*ft_append_c(char *p_buff, t_prefix *t_pf, int *len)
{
	char	*ret_buff;
	char	append_chr;

	ret_buff = NULL;
	append_chr = ' ';
	if ((size_t)t_pf->width > 1)
	{
		ret_buff = ft_mycalloc(1, t_pf->width + 1, append_chr);
		if (!ret_buff)
			return (NULL);
		if (t_pf->is_left)
		{
			ft_memcpy(ret_buff, p_buff, 1);
			free(p_buff);
		}
		else
		{
			ft_memcpy(ret_buff + t_pf->width - 1, p_buff, 1);
			free(p_buff);
		}
		*len += t_pf->width - 1;
		return (ret_buff);
	}
	else
		return (p_buff);
}
