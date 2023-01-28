/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 22:05:42 by nnakarac         ###   ########.fr       */
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
# include <sys/param.h>
# include <sys/wait.h>
# include <dirent.h>
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
	char				**bargv;
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
void		skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
char		***create_cmd(char **cmd, t_cmd *lst);

void		init_list(t_cmd *lst);

void		parse_cmd(char ***cmd);
int			print_env(void);
void		parse_env_exit_status(t_parse *p, int str_len);

// ms_directory.c
char		*get_pwd(void);
int			ms_cd(char *path_str);

// ms_token.c
void		skip_token(char *line, int *i, int mode);
int			check_close_quote(char *cmd);

void		free_main_loop(char *line, char **cmd, char ***cmd_3star);
void		*free_split(char **split);
void		free_3star(char ***cmd);

// ms_envp.c
char		*check_envp(char **list_envp, char *cmd);
char		**list_envp(char **envp, char *cmd);
void		free_lst(char **lst);

// ms_exec_cmd_prep.c
void		chk_cmd_type(t_cmd *lst, t_cmd_lst *cmd, int idx, int *i);
void		get_cmd_argv(t_cmd *lst, t_cmd_lst *cmd, int idx);
void		get_cmd_pipe(t_cmd *lst, t_cmd_lst *cmd, int idx);
void		get_cmd_envp(t_cmd *lst, t_cmd_lst *cmd, int idx);
char		**rd_in_mark(t_cmd_lst *cmd, char **rd_in, int i, char *meta);
char		**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx);
char		**rd_out_mark(t_cmd_lst *cmd, char **rd_out, int i, char *meta);
char		**get_rd_out(t_cmd *lst, t_cmd_lst *cmd, int idx);

// ms_exec_child.c
void		child(t_cmd_lst *cmd, int *fd);

// ms_exec.c
void		exec_main(t_cmd *lst);
void		executor(t_cmd *lst);
void		exec(t_cmd_lst *cmd, int *fd);

// ms_heredoc.c
void		unlink_heredoc(void);
int			heredoc(t_cmd_lst *cmd, int cnt);
char		*read_here_doc(void);

// ms_expander.c
void		expander(t_cmd *lst, int idx, int is_pipe);

// ms_infile.c
void		infile(t_cmd_lst *cmd);
void		open_infile(t_cmd_lst *cmd);

// ms_outfile.c
void		open_outfile(t_cmd_lst *cmd);
void		outfile(t_cmd_lst *cmd);

// ms_arr_uitls.c
size_t		arr2dsize(char **ptr);

// ms_cmd_lst_utils.c
void		free_cmd_lst(t_cmd_lst *cmd);

// ms_exec_cmd_lst.c and ms_exec_cmd_lst_2.c
t_cmd_lst	*cmd_lst_new(t_cmd *lst, int idx);
void		cmd_lst_new_2(t_cmd_lst *new_lst, t_cmd *lst, int idx);
void		cmd_lst_new_util1(t_cmd *lst, t_cmd_lst *cmd, int idx);
t_cmd_lst	*cmd_lst_last(t_cmd_lst *cmd_lst);
t_cmd_lst	*cmd_lst_add_front(t_cmd_lst *cmd_lst, t_cmd_lst *new);
t_cmd_lst	*cmd_lst_add_back(t_cmd_lst *cmd_lst, t_cmd_lst *new);

// ms_exec_cmd_prep.c
char		**get_rd_in(t_cmd *lst, t_cmd_lst *cmd, int idx);
char		**get_rd_out(t_cmd *lst, t_cmd_lst *cmd, int idx);
void		get_cmd_argv(t_cmd *lst, t_cmd_lst *cmd, int idx);
void		get_cmd_pipe(t_cmd *lst, t_cmd_lst *cmd, int idx);
void		get_cmd_envp(t_cmd *lst, t_cmd_lst *cmd, int idx);

// ms_realloc.c
void		ft_tokencpy(char **dest, char **src, size_t n);
void		dstrcpy(char **dest, char **src, int n);
char		**ft_realloc_dstr(char **ptr, size_t n);

// ms_signals.c
void		sig_handler_main(void);

// ms_err.c & ms_err2.c
void		err_message(int err_code, int is_exit);
void		err_enomem(void);
void		err_epipe(void);
void		err_efork(void);
void		err_eexec(char *msg, int is_exit);
void		err_eenoent(char *msg, int is_exit);
void		err_general(char *msg, int is_exit);

// ms_debug.c
void		print_cmd_lst(t_cmd_lst *cmd);
void		print2d(char **ptr);

#endif
