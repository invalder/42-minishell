/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:07:03 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 23:14:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	ft_tokencpy(char **dest, char **src, size_t n)
{
	char	**ptr_d;
	char	**ptr_s;

	ptr_d = dest;
	ptr_s = src;
	if (dest == NULL && src == NULL)
		return ;
	if (n)
		while (n-- > 0)
			*(ptr_d++) = *(ptr_s++);
}

void	dstrcpy(char **dest, char **src, int n)
{
	int		i;

	i = 0;
	if (dest == NULL && src == NULL)
		return ;
	if (n)
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
}

char	**ft_realloc_dstr(char **ptr, size_t n)
{
	char	**nptr;
	size_t	old_size;

	nptr = NULL;
	old_size = arr2dsize(ptr);
	if (!ptr)
		return (malloc(sizeof(char **) * (n + 1)));
	if (!n)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(sizeof(char **) * (n + 1));
	if (!nptr)
		return (NULL);
	if (old_size < n)
		n = old_size;
	ft_tokencpy(nptr, ptr, n);
	nptr[n] = NULL;
	free(ptr);
	return (nptr);
}
