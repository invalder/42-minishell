#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "libft.h"

typedef struct s_cmd
{
	char 			**cmd;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

void	skip_token(char *line, int *i, int mode)
{
	char	tmp;

	tmp = line[*i];
	if (mode == 1)
	{
		if (line[*i + 1] == tmp)
			*i += 2;
		else
			(*i)++;
	}
	else if (mode == 2)
	{
		(*i)++;
		while (line[*i] && line[*i] != tmp)
			(*i)++;
		if (line[*i])
			(*i)++;
	}
	else if (mode == 3)
	{
		while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '|' && \
				line[*i] != '<' && line[*i] != '>' && line[*i] != '&' && \
				line[*i] != '\'' && line[*i] != '\"')
			(*i)++;
	}
}

int	ms_count_words(char *line)
{
	int		chars;
	int		i;
	char	tmp;

	chars = 0;
	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
		{
			i++;
			continue;
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>' || line[i] == '&')
			skip_token(line, &i, 1);
		else if (line[i] == '\'' || line[i] == '\"')
			skip_token(line, &i, 2);
		else
			skip_token(line, &i, 3);
		chars++;
	}
	return (chars);
}

int	ms_count_chars(char *str)
{
	int		i;
	int		s_cmd;
	int		e_cmd;
	int		chars;
	char	tmp;

	chars = 0;
	i = 0;
	s_cmd = i;
	tmp = str[i];
	if (str[i] == '\'' || str[i] == '\"')
		skip_token(str, &i, 2);
	else if (str[i] == '|' || str[i] == '<' || str[i] == '>' || str[i] == '&')
	{
		if (str[i + 1] == tmp)
			return (2);
		else
			return (1);
	}
	else
		skip_token(str, &i, 3);
	return (i);
}

char	**cmd_split(char *line)
{
	int		cmd_count;
	int		char_count;
	int		i;
	int		j;
	char	**cmd;

	// printf("hello\n");
	cmd_count = ms_count_words(line);
	cmd = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	i = 0;
	j = 0;
	while (i < cmd_count)
	{
		while (line[j] && ft_isspace(line[j]))
			j++;
		char_count = ms_count_chars(&line[j]);
		cmd[i] = (char *)malloc(sizeof(char) * (char_count + 1));
		ft_strlcpy(cmd[i], &line[j], char_count + 1);
		i++;
		j += char_count;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

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
		// add_history(line);
		free_split(cmd);
		free(line);
		line = NULL;
	}
}
