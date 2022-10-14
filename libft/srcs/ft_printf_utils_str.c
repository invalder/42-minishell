/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:53:35 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/04 01:16:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_mystrjoin(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str)
	{
		ft_memcpy(str, s1, s1_len);
		ft_memcpy(str + s1_len, s2, s2_len + 1);
	}
	else
	{
		if (free_s1)
			ft_freemem(s1);
		if (free_s2)
			ft_freemem(s2);
		return (NULL);
	}
	if (free_s1)
		ft_freemem(s1);
	if (free_s2)
		ft_freemem(s2);
	return (str);
}

char	*ft_mysubstr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	m_len;

	s_len = (unsigned int)ft_strlen(s);
	if ((start + len) > s_len && (start + 1) <= s_len)
		m_len = s_len - start;
	else if ((start + 1) > s_len)
		m_len = 0;
	else
		m_len = len;
	substr = (char *)malloc(sizeof(char) * (m_len + 1));
	if (!substr)
	{
		free(s);
		return (NULL);
	}
	if (m_len != 0)
		m_len = ft_strlcpy(substr, &s[start], (m_len + 1));
	else
		*substr = '\0';
	free(s);
	return (substr);
}
