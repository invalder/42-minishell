/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_exit_stat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:10:15 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/11 22:14:35 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern t_global	g_globe;

void	parse_env_exit_status(t_parse *p, int str_len, char *str)
{
	if (str_len == 2 && !ft_strncmp(str, "$?\0", 3))
	{
		if (p->env)
			free(p->env);
		p->env = ft_itoa(g_globe.status);
	}
}
