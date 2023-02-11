/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_cmd_prep_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:28:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 11:15:35 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	chk_cmd_type(t_cmd *lst, t_cmd_lst *cmd, int idx, int *i)
{
	cmd->type = EXEC;
	if ((!ft_strncmp(lst->cmd[idx][*i], "(null)\0", 7)) || \
		(!ft_strncmp(lst->cmd[idx][*i], "||\0", 3)) || \
		(!ft_strncmp(lst->cmd[idx][*i], "&&\0", 3)) || \
		(!ft_strncmp(lst->cmd[idx][*i], "|\0", 2)))
	{
		if (!ft_strncmp(lst->cmd[idx][*i], "(null)\0", 7))
			cmd->type = EXEC;
		else if (!ft_strncmp(lst->cmd[idx][*i], "||\0", 3))
			cmd->type = OR;
		else if (!ft_strncmp(lst->cmd[idx][*i], "&&\0", 3))
			cmd->type = AND;
		else if (!ft_strncmp(lst->cmd[idx][*i], "|\0", 2))
			cmd->type = PIPE;
		*i += 1;
	}
}

void	get_cmd_argv(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	int		i;
	char	**argv;
	int		argc;

	i = 0;
	argv = NULL;
	chk_cmd_type(lst, cmd, idx, &i);
	while (lst->cmd[idx][i])
	{
		argc = arr2dsize(argv);
		if (!cmd->markout[i])
		{
			argv = ft_realloc_dstr(argv, argc + 1);
			argv[argc] = lst->cmd[idx][i];
			argv[argc + 1] = NULL;
		}
		i++;
	}
	cmd->argv = argv;
}

void	get_cmd_pipe(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	(void) lst;
	(void) idx;
	pipe(cmd->pfd);
}

void	get_cmd_envp(t_cmd *lst, t_cmd_lst *cmd, int idx)
{
	char	**lst_envp;

	lst_envp = NULL;
	(void) lst;
	(void) idx;
	if (cmd->argv && cmd->argv[0])
	{
		lst_envp = list_envp(environ, cmd->argv[0]);
		cmd->path = check_envp(lst_envp, cmd->argv[0]);
		if (lst_envp)
			free_split(lst_envp);
	}
}
