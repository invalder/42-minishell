/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini2_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 00:15:07 by nnakarac          #+#    #+#             */
/*   Updated: 2022/12/30 15:53:08 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini2.h"

extern t_main_meta	g_meta;

void	sigint_handler(t_main_meta *meta)
{
	meta_dealloc_input(meta);
	meta->pmt = PROMPT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler(int signo, siginfo_t *info, void *other)
{
	static int	c_pid = 0;

	(void) other;
	if (!c_pid)
		c_pid = info->si_pid;
	if (signo == SIGINT)
		sigint_handler(&g_meta);
}

void	sa_initialize(void)
{
	struct sigaction	sa;
	struct sigaction	sq;

	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sq.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sigemptyset(&sq.sa_mask);
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}
