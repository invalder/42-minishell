/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 22:33:51 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/15 10:35:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_initial(int argc, char **argv, char **envp)
{
	int		fd_tmp;
	mode_t	mode;
	char	*line;
	char	*line_lim;

	(void) argc;
	(void) argv;
	(void) envp;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		fd_tmp = open("infile", O_RDWR | O_CREAT | O_TRUNC, mode);
		line_lim = ft_strjoin(argv[2], "\n");
		if (fd_tmp < 0)
			exit_message("Can not open file!!!\n");
		// loop for reading files

		// printf("%s", line);
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(0);
			if (write(fd_tmp, line, ft_strlen(line)) < 0)

			if (!ft_strncmp(line, line_lim, ft_strlen(line_lim)))
			{
				free(line);
				break;
			}
			// printf("%s\n", ft_strnstr(line, line_lim, ft_strlen(line)));
			free(line);
		}
		//
		if (unlink("infile") < 0)
			exit_message("Can not unlink file!!!\n");
	}
	else //using infile
	{
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	if (argc < 5)
	{
		err_message("Not Enough Parameters\n");
		if (argc >= 2 && !ft_strncmp("here_doc", argv[1], 9))
			exit_message("./pipex here_doc LIMITER cmd cmd1 file\n");
		exit_message("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	}
	//check if here_doc or command
	pipex_initial(argc, argv, envp);

	//get the command and arguments

	//check if command is absolute or relative

	//find the command list to be execute
	free_lst(list_envp(envp, "/ls"));
	return (0);
}
