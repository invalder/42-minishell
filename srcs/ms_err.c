/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:43:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 16:00:33 by nnakarac         ###   ########.fr       */
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
	perror(MSG_ENOMEM);
}

void	err_epipe(void)
{
	perror(MSG_EPIPE);
}

void	err_efork(void)
{
	perror(MSG_EFORK);
}
