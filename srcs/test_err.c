/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 13:33:46 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/17 13:40:07 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_sh.h"

t_main_meta	g_meta;

int	exit_err(char *msg, int err_code)
{
	meta_dealloc_input(&g_meta);
	rl_clear_history();
	perror(msg);
	exit(err_code);
}
