/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:08:20 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/30 19:20:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	if (argc < 5)
	{
		err_message("Not Enough Parameters\n");
		if (argc >= 2 && !ft_strncmp("here_doc", argv[1], 9))
			exit_message("./pipex here_doc LIMITER cmd cmd1 ... cmdn file\n");
		exit_message("./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
	}
	pipex_initial(argc, argv, envp);
	return (0);
}
