#include "../includes/minishell.h"

typedef struct s_cmd
{
	char 			**cmd;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		i = 0;
		line = readline("minimini> ");
		if (line == NULL)
			break;
		cmd = cmd_split(line);
		while (cmd[i])
		{
			printf("%s\n", cmd[i]);
			i++;
		}
		free_split(cmd);
		free(line);
		line = NULL;
	}
}
