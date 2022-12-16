#include "../includes/ms_input.h"

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

void	print_3star(char ***cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			printf("cmd[%d][%d] = %s\n", i, j, cmd[i][j]);
			j++;
		}
		printf("cmd[%d][%d] = %s\n", i, j, cmd[i][j]);
		i++;
		printf("==========\n");
	}
	printf("%p\n", cmd[i]);
}

void	free_main_loop(char *line, char **cmd, char ***cmd_3star)
{
	free(line);
	free_split(cmd);
	free_3star(cmd_3star);
	line = NULL;
	cmd = NULL;
	cmd_3star = NULL;
}

int	main_loop()
{
	char	*line;
	char	**cmd;
	t_cmd	lst;

	while (1)
	{
		line = readline("minimini> ");
		if (line == NULL || ft_strncmp(line, "exit\0", 5) == 0)
			return (0);
		cmd = cmd_split(line);
		lst.cmd = create_cmd(cmd);
		print_3star(lst.cmd);
		free_main_loop(line, cmd, lst.cmd);
	}
}

int main(void)
{
	int		ret;
	struct	termios	old_tio;
	struct	termios	new_tio;

	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	ret = main_loop();
	if (!ret)
		printf("exit\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
	return (ret);
}
