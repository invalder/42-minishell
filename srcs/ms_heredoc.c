/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:40:54 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 23:58:35 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	unlink_heredoc(void)
{
	char	pathname[20];
	char	*number;
	int		i;

	i = 1;
	while (i < 65535)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/mini-", 20);
		ft_strlcat(pathname, number, 20);
		free(number);
		if (access(pathname, F_OK) != -1)
			unlink(pathname);
		i++;
	}
}

int	heredoc(t_cmd_lst *cmd, int cnt)
{
	int		fd_tmp;
	char	*line;
	char	*line_lim;
	char	*fd_tmp_path;

	fd_tmp_path = read_here_doc();
	fd_tmp = open(fd_tmp_path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	line_lim = ft_strjoin(cmd->infile[cnt], "\n");
	if (fd_tmp < 0)
		err_general("can not open file!!!\n", 1);
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
	free(line_lim);
	fd_tmp = open(fd_tmp_path, O_RDWR | O_CREAT, 0644);
	free(fd_tmp_path);
	return (fd_tmp);
}

char	*read_here_doc(void)
{
	char	pathname[20];
	char	*number;
	int		fd;
	int		i;

	i = 1;
	while (i < 65535)
	{
		number = ft_itoa(i);
		ft_strlcpy(pathname, "/tmp/mini-", 20);
		ft_strlcat(pathname, number, 20);
		free(number);
		if (access(pathname, F_OK) == -1)
		{
			fd = open(pathname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd != -1)
			{
				close(fd);
				return (ft_strdup(pathname));
			}
		}
		i++;
	}
	return (NULL);
}
