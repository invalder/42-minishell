/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:52:58 by nnakarac          #+#    #+#             */
/*   Updated: 2022/04/02 16:07:09 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_buffer
{
	char	*buff;
	size_t	len;
	size_t	cur;
	size_t	last;
	size_t	next;
}	t_buffer;

char	*ft_freebuff(t_buffer *p_buff);
char	*get_next_line(int fd);
char	*ft_gnl_buffer(t_buffer *p_buff, int read_cnt);
int		ft_gnl_add_buff(t_buffer *p_buff, int fd);
char	*ft_alloc_buffer(t_buffer *p_buff, size_t buff_size);
char	*ft_gnl_last(t_buffer *p_buff, int read_cnt);

#endif
