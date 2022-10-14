/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 09:32:22 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 19:58:10 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
%[flags][width][.precision]specifier
[flags]
'-'	Left-justify within the given field width; Right
	justification is the default (see width sub-specifier).
'+'	Forces to preceed the result with a plus or minus sign
	(+ or -) even for positive numbers.
	By default, only negative numbers are preceded with a - sign.
' '	If no sign is going to be written, a blank space is inserted
	before the value.
'#' Used with o, x or X specifiers the value is preceeded with 0,
	0x or 0X respectively for values different than zero.
'0' Left-pads the number with zeroes (0) instead of spaces when
	padding is specified (see width sub-specifier).

[width]
(number)	Minimum number of characters to be printed. If the value
			to be printed is shorter than this number,
			the result is padded with blank spaces. The value is not
			truncated even if the result is larger.
'*'			The width is not specified in the format string, but as an
			additional integer value argument preceding the argument
			that has to be formatted.

[.precision]
.number		For integer specifiers (d, i, o, u, x, X): precision specifies
			the minimum number of digits to be written.
			If the value to be written is shorter than this number,
			the result is padded with leading zeros.
			The value is not truncated even if the result is longer.
			A precision of 0 means that no character is written for the value 0.
.*			The precision is not specified in the format string,
			but as an additional integer value argument preceding
			the argument that has to be formatted.
*/

static char		*ft_sub_printf(char *ptr, int *len, va_list ap);
static ssize_t	ft_formatchk(char *ptr);

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	char	*ptr;
	char	*buff;
	int		len;

	len = 0;
	va_start(ap, fmt);
	ptr = (char *)fmt;
	buff = NULL;
	buff = ft_sub_printf(ptr, &len, ap);
	if (buff)
	{
		ft_putnstr(buff, len);
		free(buff);
	}
	va_end(ap);
	return (len);
}

static char	*ft_sub_printf(char *ptr, int *len, va_list ap)
{
	char	*buff;
	int		cur;

	buff = NULL;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			cur = ft_formatchk(ptr);
			if (cur > 0)
				buff = ft_appendfmt(buff, ptr + 1, len, ap);
			else
				return (ft_freemem(buff));
		}
		else
		{
			buff = ft_appendchr(buff, ptr, len);
			cur = 1;
		}
		ptr += cur;
	}
	return (buff);
}

static ssize_t	ft_formatchk(char *ptr)
{
	ssize_t	len;

	len = 1;
	if (*(ptr + len) == '%')
		return (2);
	while (!ft_specchk(ptr + len))
	{
		len += ft_flgchk(ptr + len);
		len += ft_widthchk(ptr + len);
		len += ft_precisechk(ptr + len);
	}
	if (ft_specchk(ptr + len))
		len += 1;
	else
		len = -1;
	return (len);
}
