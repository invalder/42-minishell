/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:43:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/05 02:52:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	err_message(int err_code, int is_exit)
{
	if (err_code == ENOMEM)
		err_enomem();
	if (is_exit)
		exit(err_code);
}

void	err_enomem(void)
{
	ft_putstr_fd(MSG_ENOMEM, 2);
}

void	err_epipe(void)
{
	ft_putstr_fd(MSG_EPIPE, 2);
}

void	err_efork(void)
{
	ft_putstr_fd(MSG_EFORK, 2);
}

void	err_eexec(char *msg, int is_exit)
{
	ft_putstr_fd(msg, 2);
	if (!opendir(msg))
	{
		if (ft_strchr(msg, '/'))
			ft_putstr_fd(MSG_EEXEC_ENOENT, 2);
		else
			ft_putstr_fd(MSG_EEXEC, 2);
		if (is_exit)
			exit(127);
	}
	else
	{
		ft_putstr_fd(MSG_EEXEC_DIR, 2);
		if (is_exit)
			exit(126);
	}
}