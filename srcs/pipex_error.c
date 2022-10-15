/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 23:05:07 by nnakarac          #+#    #+#             */
/*   Updated: 2022/10/15 09:59:39 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(void)
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(1);
}

void	exit_message(char *errmsg)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(errmsg, 2);
	ft_putstr_fd(RESET, 2);
	exit(1);
}

void	err_message(char *errmsg)
{
	ft_putstr_fd(errmsg, 2);
}
