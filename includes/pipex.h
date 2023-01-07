/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:05:30 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/29 21:42:41 by nnakarac         ###   ########.fr       */
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

typedef struct s_meta
{
	int	*pipe_fd;
	int	fd_tmp;
	int	cnt;
	int	p[2];
}	t_meta;

void	exit_error(void);
void	exit_message(char *errmsg);
void	err_message(char *errmsg);

char	**list_envp(char **envp, char *cmd);
char	*check_envp(char **list_envp, char *cmd);
void	free_lst(char **lst);

void	pipex_initial(int argc, char **argv, char **envp);

void	pipex_exec_parent(int argc, char **argv, char **envp, t_meta *meta);
void	pipex_exec_child(int argc, char **argv, char **envp, t_meta *meta);
void	pipex_execution(int argc, char **argv, char **envp, int fd);

void	pipex_heredoc(int argc, char **argv, char **envp);
void	pipex_normal(int argc, char **argv, char **envp);
void	pipex_initial(int argc, char **argv, char **envp);

#endif
