/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:05:41 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 15:44:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI2_H
# define MINI2_H
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ucontext.h>
# include <sys/stat.h>
# include <signal.h>
# include "color.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

# define PROMPT "mini2>"
# define SPROMPT ">"
# define HPROMPT "heredoc>"

# define WHTSP " \t\r\n\v"
# define SYMBOLS "<|>&;()"

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define TOKENBUF 256

typedef struct s_main_meta
{
	char	*line;
	char	*subline;
	char	*input;
	char	*tinput;
	char	*pmt;
}	t_main_meta;

void	sa_initialize(void);
void	sig_handler(int signo, siginfo_t *info, void *other);
void	sigint_handler(t_main_meta *meta);

void	meta_init(t_main_meta *meta);
void	meta_dealloc_input(t_main_meta *meta);

int		exit_err(char *msg, int err_code);

void	ft_dealloc_ptr(void **ptr);
void	ft_dealloc_dptr(void ***ptr);
void	ft_dealloc_tptr(void ****ptr);
char	*ft_read_line(char **ptr, char *pmt);
void	ft_multiline_cmd(t_main_meta *meta);

int		is_comment_line(char *line);
int		is_heredoc(char **line, char **input);
void	exit_eof(t_main_meta *meta);

int		cmd_loop(t_main_meta *meta);

#endif
