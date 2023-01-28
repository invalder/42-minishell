/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse_exit_stat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:10:15 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/28 15:11:59 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

extern int	g_status;

void	parse_env_exit_status(t_parse *p, int str_len)
{
	if (str_len == 2 && !ft_strncmp(p->sub, "?", 1))
		p->env = ft_itoa(g_status);
	else
		p->env = getenv(p->sub);
}
