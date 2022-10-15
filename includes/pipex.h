/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:05:30 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/15 10:11:37 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include "color.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

void	exit_error(void);
void	exit_message(char *errmsg);
void	err_message(char *errmsg);

char	**list_envp(char **envp, char *cmd);
void	free_lst(char **lst);

int		pipex_initial(int argc, char **argv, char **envp);

#endif
