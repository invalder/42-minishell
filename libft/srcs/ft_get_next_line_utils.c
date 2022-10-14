/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:53:10 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 15:36:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*ft_freebuff(t_buffer *p_buff);

char	*ft_freebuff(t_buffer *p_buff)
{
	if (p_buff->buff)
	{
		free(p_buff->buff);
		p_buff->buff = 0;
	}
	p_buff->cur = 0;
	p_buff->len = 0;
	p_buff->next = 0;
	p_buff->last = 0;
	return (0);
}
