/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 20:52:44 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/30 19:20:19 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_heredoc(int argc, char **argv, char **envp)
{
	int		fd_tmp;
	char	*line;
	char	*line_lim;

	fd_tmp = open("fd_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	line_lim = ft_strjoin(argv[2], "\n");
	if (fd_tmp < 0)
		exit_message("Can not open file!!!\n");
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, line_lim, ft_strlen(line_lim)))
		{
			free(line);
			break ;
		}
		write(fd_tmp, line, ft_strlen(line));
		free(line);
	}
	close(fd_tmp);
	fd_tmp = open("fd_tmp", O_RDWR | O_CREAT, 0644);
	pipex_execution(argc, argv, envp, fd_tmp);
	if (unlink("fd_tmp") < 0)
		exit_message("Can not unlink file!!!\n");
}

void	pipex_normal(int argc, char **argv, char **envp)
{
	int		fd_tmp;

	fd_tmp = open(argv[1], O_RDWR | O_CREAT, 0644);
	if (fd_tmp < 0)
		exit_message("Can not open file!!!\n");
	pipex_execution(argc, argv, envp, fd_tmp);
	if (close(fd_tmp) < 0)
		exit_message("Can not close file!!!\n");
}

void	pipex_initial(int argc, char **argv, char **envp)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		pipex_heredoc(argc, argv, envp);
	}
	else
	{
		pipex_normal(argc, argv, envp);
	}
}
