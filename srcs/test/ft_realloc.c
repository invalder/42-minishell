/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:49:03 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 13:33:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*nptr;
	size_t	old_size;

	nptr = NULL;
	old_size = sizeof(ptr);
	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(size);
	if (!nptr)
		return (NULL);
	if (old_size < size)
		size = old_size;
	ft_memcpy(nptr, ptr, size);
	return (nptr);
}

void	**ft_realloc_d(void **ptr, size_t size)
{
	void	**nptr;
	size_t	old_size;

	nptr = NULL;
	old_size = sizeof(ptr);
	if (!ptr)
	{
		return (malloc(size));
	}
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(sizeof(void**) * size);
	if (!nptr)
		return (NULL);
	if (old_size < size)
		size = old_size;
	ft_memcpy(nptr, ptr, size);
	return (nptr);
}

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

char	**ft_realloc_tokens(char **ptr, size_t size)
{
	char	**nptr;
	size_t	old_size;

	nptr = NULL;
	old_size = sizeof(ptr);
	if (!ptr)
	{
		return (malloc(size));
	}
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	nptr = malloc(sizeof(char**) * size);
	if (!nptr)
		return (NULL);
	if (old_size < size)
		size = old_size;
	ft_tokencpy(nptr, ptr, size);
	return (nptr);
}
