/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:17:37 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/12 21:07:11 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testsh.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	char	*subline;
// 	char	*input;
// 	char	*pmt;

// 	(void) argc;
// 	(void) argv;
// 	(void) envp;

// 	line = NULL;
// 	input = NULL;
// 	subline = NULL;
// 	pmt = PROMPT;

// 	while (1)
// 	{
// 		while (ft_read_line(&line, pmt))
// 		{
// 			if (!ft_strncmp(line, "#", 1))
// 			{
// 				ft_dealloc_ptr((void **)&line);
// 				break ;
// 			}
// 			if ((size_t)(ft_strrchr(line, '\\') - line) != ft_strlen(line) - 1)
// 			{
// 				input = ft_mystrjoin(input, line, ft_strlen(input), ft_strlen(line));
// 				line = NULL;
// 				break ;
// 			}
// 			else
// 			{
// 				subline = ft_substr(line, 0, ft_strlen(line) - 1);
// 				input = ft_mystrjoin(input, subline, ft_strlen(input), ft_strlen(subline));
// 				ft_dealloc_ptr((void **) &line);
// 				pmt = SPROMPT;
// 			}
// 		}
// 		printf("outer: %s\n", input);
// 		ft_dealloc_ptr((void **) &line);
// 		ft_dealloc_ptr((void **) &input);
// 		pmt = PROMPT;
// 		break;
// 	}
// 	return (0);
// }

t_main_meta	g_meta;

int		is_heredoc(char **line, char **input)
{
	if ((size_t)(ft_strrchr(*line, '\\') - *line) != ft_strlen(*line) - 1)
	{
		*input = ft_mystrjoin(*input, *line, ft_strlen(*input), ft_strlen(*line));
		*line = NULL;
		return (0);
	}
	return (1);
}

int		is_comment_line(char *line)
{
	if(ft_strncmp(line, "#", 1))
		return (0);
	ft_dealloc_ptr((void **)&line);
	return (1);
}

int		cmd_loop(void)
{
	g_meta.line = NULL;
	g_meta.input = NULL;
	g_meta.subline = NULL;
	g_meta.pmt = PROMPT;

	while (1)
	{
		while (ft_read_line(&g_meta.line, g_meta.pmt))
		{
			if (is_comment_line(g_meta.line))
				break;
			if (!is_heredoc(&g_meta.line, &g_meta.input))
				break;
			else
			{
				g_meta.subline = ft_substr(g_meta.line, 0, ft_strlen(g_meta.line) - 1);
				g_meta.input = ft_mystrjoin(g_meta.input, g_meta.subline, \
					ft_strlen(g_meta.input), ft_strlen(g_meta.subline));
				ft_dealloc_ptr((void **) &g_meta.line);
				g_meta.pmt = SPROMPT;
			}
		}
		add_history(g_meta.input);
		ft_dealloc_ptr((void **) &g_meta.line);
		ft_dealloc_ptr((void **) &g_meta.input);
		g_meta.pmt = PROMPT;
	}
}

void	sigint_handler(void)
{
	ft_dealloc_ptr((void **) &g_meta.line);
	ft_dealloc_ptr((void **) &g_meta.input);
	g_meta.pmt = PROMPT;
	rl_replace_line(g_meta.pmt,0);
	rl_redisplay();
}

void	sig_handler(int signo, siginfo_t *info, void *other)
{
	static int	c_pid = 0;

	(void) other;
	if (!c_pid)
		c_pid = info->si_pid;
	if (signo == SIGINT)
		sigint_handler();
	if (signo == SIGQUIT)
		exit(0);
}

void	sa_initialize(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	g_meta.parent.pid = getpid();
	sa_initialize();
	cmd_loop();
}
