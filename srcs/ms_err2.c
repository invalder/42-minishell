/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 22:50:29 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/21 22:50:53 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	err_eenoent(char *msg, int is_exit)
{
	ft_putstr_fd(MSG_ENOENT, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (is_exit)
		exit(1);
}

void	err_general(char *msg, int is_exit)
{
	ft_putstr_fd(msg, 2);
	if (is_exit)
		exit(1);
}
