/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:40:04 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 01:01:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

// typedef struct s_pipe
// {
// 	t_cmd	*cmd;
// 	int		to_fd;
// }	t_pipe;

// typedef struct s_redir_l
// {
// 	t_cmd	*cmd;
// 	char	*file;
// 	int		to_fd;
// }	t_redir_l;

// typedef struct s_redir_r
// {
// 	t_cmd	*cmd;
// 	char	*file;
// 	char	*target_file;
// }	t_redir_r;

// typedef struct s_logic
// {
// 	t_cmd	*cmd;
// 	t_cmd	*cmd2;
// }	t_logic;

// typedef struct s_block
// {
// 	t_pipe		*pipe;
// 	t_redir_l	*redir_l;
// 	t_redir_r	*redir_r;
// 	t_logic		*logic;
// }	t_block;

int	g_status = 0;



void	print_2star(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		printf("cmd[%d] = %s\n", i, cmd[i]);
		i++;
	}
	printf("cmd[%d] = %s\n", i, cmd[i]);
	printf("==========\n");
}

void	free_main_loop(char *line, char **cmd, char ***cmd_3star)
{
	if (line)
		free(line);
	if (cmd)
		free_split(cmd);
	if (cmd_3star)
		free_3star(cmd_3star);
	line = NULL;
	cmd = NULL;
	cmd_3star = NULL;
}

int	main_loop(t_cmd *lst)
{
	char	*line;
	char	**cmd;

	while (1)
	{
		line = readline("minimini> ");
		if (line == NULL || !ft_strncmp(line, "exit\0", 5))
			return (0);
		if (*line && *line != '\0')
			add_history(line);
		// check quotes are closed, if not print error message free line and continue
		if (!ms_check_full_quotes(line))
		{
			printf("minishell: syntax error: quotes are not closed\n");
			free(line);
			continue ;
		}
		if (!ft_strncmp(line, "env\0", 4))
			print_env();

		// dak $?
		cmd = cmd_split(line);
		if (cmd != NULL)
		{
			lst->cmd = create_cmd(cmd, lst);
			parse_cmd(lst->cmd);
			exec_main(lst);
		}
		else
			lst->cmd = NULL;
		free_main_loop(line, cmd, lst->cmd);
	}
	return (0);
}

int	main(void)
{
	int				ret;
	struct termios	old_tio;
	struct termios	new_tio;
	t_cmd			lst;

	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag = new_tio.c_lflag & (~ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	init_list(&lst);
	sig_handler_main();
	ret = main_loop(&lst);
	if (!ret)
		printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
	environ = lst.tmp_envp;
	free_split(lst.new_envp);
	rl_clear_history();
	return (ret);
}
