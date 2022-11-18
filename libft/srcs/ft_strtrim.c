/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:46:45 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 15:03:04 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s1, char const *set);
static int	head_check(char const *s1, char const *set);
static int	tail_check(char const *s1, char const *set);
static int	set_check(char s1, char const *set);

// check if set existed

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_s_fwd;
	char	*p_s_bwd;
	char	*str;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	p_s_fwd = (char *) s1 + head_check(s1, set);
	p_s_bwd = (char *) s1 + tail_check(s1, set);
	len = p_s_bwd - p_s_fwd + 1;
	if (head_check(s1, set) > tail_check(s1, set))
		len = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	len = ft_strlcpy(str, p_s_fwd, (len + 1));
	return (str);
}

static int	head_check(char const *s1, char const *set)
{
	char	*p_s_fwd;
	int		len;

	p_s_fwd = (char *) s1;
	len = 0;
	while (*p_s_fwd != '\0')
	{
		if (set_check(*p_s_fwd++, set))
			len++;
		else
			return (len);
	}
	return (len);
}

static int	tail_check(char const *s1, char const *set)
{
	char	*p_s_bwd;
	int		len;

	p_s_bwd = (char *) s1;
	len = ft_strlen(s1) - 1;
	while (p_s_bwd + len != s1)
	{
		if (set_check(*(p_s_bwd + len), set))
			len--;
		else
			return (len);
	}
	return (len);
}

static int	set_check(char s1, char const *set)
{
	char	*p_s_chk;
	char	*p_set;

	p_set = (char *) set;
	p_s_chk = &s1;
	while (*p_set != '\0')
	{
		if (*p_set++ == *p_s_chk)
			return (1);
	}
	return (0);
}
