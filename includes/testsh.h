/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testsh.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:17:08 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/12 20:39:27 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSH_H
# define TESTSH_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ucontext.h>
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

# define PROMPT "testshell>"
# define SPROMPT ">"
# define HPROMPT "heredoc>"

# define WHTSP " \t\r\n\v"
# define SYMBOLS "<|>&;()"

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	**argv;
	char	**eargv;
}	t_excmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_rdcmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_ppcmd;

typedef struct s_listcmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_lscmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}	t_bkcmd;

typedef struct s_pid
{
	pid_t	pid;
	pid_t	ppid;
}	t_pid;

typedef struct s_pid_meta
{
	t_pid	*pid_info;
	t_pid	*next;
	t_pid	*prev;
}	t_pmeta;

typedef struct s_main_meta
{
	t_pid	parent;
	t_pmeta	*child;
	char	*line;
	char	*subline;
	char	*input;
	char	*pmt;
}	t_main_meta;

void	ft_dealloc_ptr(void **ptr);
char	*ft_read_line(char **ptr, char *pmt);

int		fork_p(void);
void	panic(char *err);
void	runcmd(t_cmd *cmd);
int		getcmd(char	*buf);

t_cmd	*execcmd(void);
t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*pipecmd(t_cmd *left, t_cmd *right);
t_cmd	*listcmd(t_cmd *left, t_cmd *right);
t_cmd	*backcmd(t_cmd *subcmd);

t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsepipe(char **ps, char *es);
t_cmd	*parseexec(char **ps, char *es);
t_cmd	*nullterminate(t_cmd *cmd);

int		ft_gettoken(char **ps, char *es, char **q, char **eq);
int		ft_peek(char **ps, char *es, char *toks);

t_cmd	*parsecmd(char *s);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char **es);
t_cmd	*parseblock(char **ps, char *es);

#endif