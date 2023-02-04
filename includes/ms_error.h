/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:53:04 by nnakarac          #+#    #+#             */
/*   Updated: 2023/02/04 11:34:14 by nnakarac         ###   ########.fr       */
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
# define MSG_EEXEC	": command not found\n"
# define MSG_ENOENT	"no such file or directory: "

void	err_message(int err_code, int is_exit);
void	err_enomem(void);
void	err_epipe(void);
void	err_efork(void);
void	err_eexec(char *msg, int is_exit);
void	err_eenoent(char *msg, int is_exit);
void	err_general(char *msg, int is_exit, int err_code);
void	err_exit(char *argv, int is_exit);

#endif
