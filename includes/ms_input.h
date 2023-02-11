/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 21:47:11 by sthitiku         ###   ########.fr       */
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
# include <sys/param.h>
# include <dirent.h>
# include <signal.h>

extern char **environ;
// test_cmd = echo $HOME '"hello""world"' test &&ls -la|cat -e

typedef struct s_cmd
{
	char	***cmd;
	char	**tmp_envp;
	char	**new_envp;
	int		cmd_len;
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
void	skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
char	***create_cmd(char **cmd, t_cmd *lst);

void	init_list(t_cmd *lst);

void	parse_cmd(char ***cmd);
int		print_env(void);

// ms_directory.c
char	*get_pwd();
int		ms_cd(char *path_str);

// ms_token.c
void	skip_token(char *line, int *i, int mode);
int		check_close_quote(char *cmd);

void	free_main_loop(char *line, char **cmd, char ***cmd_3star);
void	*free_split(char **split);
void	free_3star(char ***cmd);

// ms_parser_helper.c
char	*cut_quote(char *str, char quote);
char	*parse_env_get_env(char *str, int str_len, char first, char last);

// ms_expander_helper.c
char	find_sep(char *str);
char	*ms_join_char(char *str, char c);
char	*ms_join_str(char *str1, char *str2);
char	*expand_env(char *env);
int		find_sep_index(char *str, char sep);

#endif
