/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/08 16:18:44 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_INPUT_H
# define MS_INPUT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

extern char **environ;
// test_cmd = echo $HOME '"hello""world"' test &&ls -la|cat -e

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5
# define BUILTIN 88

# define HEREDOC 99

typedef struct s_cmd_lst
{
	int					type;
	pid_t				pid;
	pid_t				ppid;
	int					p[2];
	char				**infile;
	int					*in_fd;
	char				**outfile;
	int					*out_fd;
	int					*out_mode;
	char				*path;
	char				**argv;
	char				**envp;
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
char	**cmd_split(char *line);
void	free_split(char **split);
void	skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
char	***create_cmd(char **cmd, t_cmd *lst);
void	free_3star(char ***cmd);

void	 init_list(t_cmd *lst);

void	parse_cmd(char ***cmd);
int		print_env(void);

void	exec_main(t_cmd *lst);
int		*exec_cmd(t_cmd *lst, int idx, int token);
void	expander(t_cmd *lst, int idx, int is_pipe);
void	print_3star(char ***cmd);

void	*ft_realloc(void *ptr, size_t size);
void	**ft_realloc_d(void **ptr, size_t size);
void	ft_tokencpy(char **dest, char **src, size_t n);
char	**ft_realloc_tokens(char **ptr, size_t size);

char	*check_envp(char **list_envp, char *cmd);
char	**list_envp(char **envp, char *cmd);
void	free_lst(char **lst);

#endif
