/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:47:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 14:51:18 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	print_cmd_lst(t_cmd_lst *cmd)
{
	while (cmd)
	{
		printf("==========\n");
		printf("type: %d\n", cmd->type);
		printf("pid: %d\n", cmd->pid);
		printf("ppid: %d\n", cmd->ppid);
		printf("infile: \n");
		print2d(cmd->infile);
		printf(":::::\n");
		printf("outfile: \n");
		print2d(cmd->outfile);
		printf(":::::\n");
		printf("path: %s\n", cmd->path);
		printf("argv: \n");
		print2d(cmd->argv);
		printf(":::::\n");
		printf("==========\n");
		cmd = cmd->right;
	}
}
