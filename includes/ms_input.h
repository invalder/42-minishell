/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 23:31:04 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_INPUT_H
# define MS_INPUT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include "libft.h"
# include "get_next_line.h"
# include "ms_error.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>

extern char	**environ;
// test_cmd = echo $HOME '"hello""world"' test &&ls -la|cat -e

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define AND 66
# define OR	77
# define BUILTIN 88
# define HEREDOC 99

typedef struct s_cmd_lst
{
	int					type;
	pid_t				pid;
	pid_t				ppid;
	int					pfd[2];
	char				**infile;
	int					*in_fd;
	int					*is_heredoc;
	char				**outfile;
	int					*out_fd;
	int					*o_mode;
	int					*markout;
	char				*path;
	char				**argv;
	int					argc;
	char				**envp;
	int					status;
	struct s_cmd_lst	*left;
	struct s_cmd_lst	*right;
}	t_cmd_lst;

typedef struct s_cmd
{
	char		***cmd;
	char		**tmp_envp;
	char		**new_envp;
	int			cmd_len;
	t_cmd_lst	*cmd_lst;
	char		*cwd;
	int			status;
}	t_cmd;

typedef struct s_parse
{
	int		start;
	int		end;
	char	*sub;
	char	*env;
}	t_parse;

// ms_split.c -> split from char* to char**
char		**cmd_split(char *line);
void		free_split(char **split);
void		skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
size_t		arr2dsize(char **ptr);

char		***create_cmd(char **cmd, t_cmd *lst);
void		free_3star(char ***cmd);

void		init_list(t_cmd *lst);

void		parse_cmd(char ***cmd);
int			print_env(void);

void		exec_main(t_cmd *lst);
int			*exec_cmd(t_cmd *lst, int idx, int token);
void		expander(t_cmd *lst, int idx, int is_pipe);
void		print_3star(char ***cmd);

void		**ft_realloc_d(void **ptr, size_t size);
void		ft_tokencpy(char **dest, char **src, size_t n);
char		**ft_realloc_tokens(char **ptr, size_t size);

void		dstrcpy(char **dest, char **src, int n);
char		**ft_realloc_dstr(char **ptr, size_t n);

char		*check_envp(char **list_envp, char *cmd);
char		**list_envp(char **envp, char *cmd);
void		free_lst(char **lst);

void		print2d(char **ptr);
void		free_cmd_lst(t_cmd_lst *cmd);

void		print_cmd_lst(t_cmd_lst *cmd);
void		cmd_lst_new_util1(t_cmd *lst, t_cmd_lst *cmd, int idx);

t_cmd_lst	*cmd_lst_new(t_cmd *lst, int idx);
void	cmd_lst_new_2(t_cmd_lst *new_lst, t_cmd *lst, int idx);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *cmd_lst);
t_cmd_lst	*cmd_lst_add_front(t_cmd_lst *cmd_lst, t_cmd_lst *new);
t_cmd_lst	*cmd_lst_add_back(t_cmd_lst *cmd_lst, t_cmd_lst *new);

size_t		arr2dsize(char **ptr);

char	**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx);
char	**get_rd_out(t_cmd *lst, t_cmd_lst *cmd, int idx);
void	get_cmd_argv(t_cmd *lst, t_cmd_lst *cmd, int idx);

void	get_cmd_pipe(t_cmd *lst, t_cmd_lst *cmd, int idx);
void	get_cmd_envp(t_cmd *lst, t_cmd_lst *cmd, int idx);

void	infile(t_cmd_lst *cmd);

#endif
