/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:57:29 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/03 17:58:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_append2str(char *buff, char c)
{
	size_t	buff_len;
	char	*new_buff;

	new_buff = NULL;
	if (buff)
		buff_len = ft_strlen(buff);
	else
		buff_len = 0;
	new_buff = malloc(sizeof(char) * (buff_len + 2));
	if (!new_buff)
		return (NULL);
	if (buff)
	{
		ft_memcpy(new_buff, buff, buff_len);
		free(buff);
	}
	*(new_buff + buff_len) = c;
	*(new_buff + buff_len + 1) = 0;
	return (new_buff);
}

char	*ft_append2str_ul(char *buff, char c, int shift)
{
	size_t	buff_len;
	char	*new_buff;

	if (shift)
	{
		if (c >= 'a' && c <= 'z')
			c -= 32;
	}
	new_buff = NULL;
	if (buff)
		buff_len = ft_strlen(buff);
	else
		buff_len = 0;
	new_buff = malloc(sizeof(char) * (buff_len + 2));
	if (!new_buff)
		return (NULL);
	if (buff)
	{
		ft_memcpy(new_buff, buff, buff_len);
		free(buff);
	}
	*(new_buff + buff_len) = c;
	*(new_buff + buff_len + 1) = 0;
	return (new_buff);
}

char	*ft_appendchr(char *buff, char *ptr, int *len)
{
	size_t	buff_len;
	char	*new_buff;

	new_buff = NULL;
	if (buff)
		buff_len = *len;
	else
		buff_len = 0;
	new_buff = malloc(sizeof(char) * (buff_len + 2));
	if (!new_buff)
		return (NULL);
	if (buff)
	{
		ft_memcpy(new_buff, buff, buff_len);
		free(buff);
	}
	ft_memcpy(new_buff + buff_len, ptr, 1);
	*(new_buff + buff_len + 1) = 0;
	*len += 1;
	return (new_buff);
}
