/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 00:56:08 by sthitiku         ###   ########.fr       */
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
void	free_split(char **split);
void	skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
char	***create_cmd(char **cmd, t_cmd *lst);
void	free_3star(char ***cmd);

void	 init_list(t_cmd *lst);

void	parse_cmd(char ***cmd);
int		print_env(void);

// ms_directory.c
char	*get_pwd();
int		ms_cd(char *path_str);

// ms_token.c
void	skip_token(char *line, int *i, int mode);

#endif
