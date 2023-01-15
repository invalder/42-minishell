/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:53:04 by nnakarac          #+#    #+#             */
/*   Updated: 2023/01/15 16:00:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>

# define MSG_ENOMEM	"minishell: malloc: out of memory\n"
# define MSG_EPIPE	"minishell: write error: Broken pipe\n"
# define MSG_EFORK	"minishell: fork: cannot create child process\n"

void	err_message(int err_code, int is_exit);
void	err_enomem(void);
void	err_epipe(void);
void	err_efork(void);

#endif
