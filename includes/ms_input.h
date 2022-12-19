/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:48:20 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/20 01:08:32 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
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

// ms_split.c -> split from char* to char**
char	**cmd_split(char *line);
void	free_split(char **split);
void	skip_token(char *line, int *i, int mode);

// ms_cmd_split.c -> split from char** to char***
char	***create_cmd(char **cmd, t_cmd *lst);
void	free_3star(char ***cmd);

void	 init_list(t_cmd *lst);

void	parse_cmd(char ***cmd);

#endif
