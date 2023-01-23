/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 08:36:58 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/22 08:40:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_input.h"

void	int_handler(void)
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(int signo, siginfo_t *s, void *old)
{
	(void) old;
	(void) s;
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_main(void)
{
	struct sigaction	s_int;
	struct sigaction	s_quit;

	s_int.sa_sigaction = sig_handler;
	s_quit.sa_handler = SIG_IGN;
	s_int.sa_flags = SA_SIGINFO;
	s_quit.sa_flags = SA_RESTART;
	sigemptyset(&s_int.sa_mask);
	sigemptyset(&s_quit.sa_mask);
	sigaction(SIGINT, &s_int, NULL);
	sigaction(SIGQUIT, &s_quit, NULL);
}
