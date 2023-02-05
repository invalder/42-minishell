# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 01:24:09 by nnakarac          #+#    #+#              #
#    Updated: 2023/02/05 19:32:51 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NORM = norminette -R CheckForbiddenSourceHeaderDefine

UNAME = $(shell uname -s)
ARCH = $(shell arch)
ifeq ($(UNAME), Linux)
	MEME = aplay easter_egg/meme2.mp3 &
	ANYA = aplay easter_egg/anya.mp3 &
	SPONSOR = aplay easter_egg/sponsor.mp3 &
	TIEIN = aplay easter_egg/tir_in.wav &
else
	MEME = afplay easter_egg/meme2.mp3 -v 0.3 &
	ANYA = afplay easter_egg/anya.mp3 -v 0.7 &
	SPONSOR = afplay easter_egg/sponsor.mp3 -v 0.7 &
	TIEIN = afplay easter_egg/tie_in.wav -v 0.7 &
endif

MEME2 = say -v kanya "กำลังรัน นอร์มิเน็ตโตะ" &
MEME4 = say -v kanya "กำลังรัน MAKE RE" &
ANYA2 = say -v kanya "วากุ วากุ" &
SPONSOR2 = say -v kanya -r 0.8 "เอ่อ โค้ดนี้ก็ เขียนเองนะครับ    แก้  เขียน  ครบ    จบในที่เดียว ยังไงก็ให้ผ่านนะครับ ผมจะได้ไปต่อ" &
SPONSOR4 = say -v kanya -r 20 "เอ่อ โค้ดนี้ก็ ทำเองนะครับ" &
SPONSOR5 = say -v kanya -r 10 "เขียน  บั๊ก  ครบ    จบในที่เดียว" &
SPONSOR6 = say -v kanya -r 40 "มีบั๊กทุกบรรทัดแหละครับ    ไม่ต้องคิดมาก" &
SPONSOR7 = say -v kanya -r 20 "ให้ผ่านเถอะครับ ผมจะได้ไปต่อ" &

MEME3 = ./easter_egg/credits.sh
ANYA3 = ./easter_egg/anya.sh
SPONSOR3 = ./easter_egg/sponsor.sh

NAME = minishell
NAMEP = pipex
CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror

ifeq ($(ARCH), arm64)
	LDFLAGS	= -L${HOMEBREW_PREFIX}/opt/readline/lib
	CPPFLAGS	= -I${HOMEBREW_PREFIX}/opt/readline/include
else
	LDFLAGS	= -L/usr/local/opt/readline/lib
	CPPFLAGS	= -I/usr/local/opt/readline/include
endif

# CFLAGS	= -Wall -Wextra -Werror -g -I/opt/homebrew/opt/readline/include
# RL	= -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include
RM		= /bin/rm -rf

SRC_DIR	= srcs/
OBJ_DIR	= objs/
INC_DIR	= includes
LIB_DIR = libft/

LIBS	= -L$(LIB_DIR) -lft

INCS	= -I$(INC_DIR)\
		-I$(LIB_DIR)includes \

SRCS	=	test.c \
			ms_split.c \
			ms_cmd_split.c \
			ms_environ.c \
			ms_parse.c \
			ms_parse_exit_stat.c \
			ms_token.c \
			ms_free_input.c \
			ms_exec.c \
			ms_exec_child.c \
			ms_envp.c \
			ms_heredoc.c \
			ms_implement.c \
			ms_infile.c \
			ms_outfile.c \
			ms_expander.c \
			ms_exec_cmd_lst.c \
			ms_exec_cmd_lst_2.c \
			ms_exec_cmd_prep.c \
			ms_exec_cmd_prep_2.c \
			ms_cmd_lst_utils.c \
			ms_realloc.c \
			ms_builtin_cmd.c \
			ms_builtin_cmd_parent.c \
			ms_builtin_cmd_child.c \
			ms_signals.c \
			ms_debug.c \
			ms_err.c \
			ms_err2.c \
			ms_arr_utils.c \
			ms_string_utils.c \

# SRCS	= minishell.c \

# SRCS_P	= pipex.c \
# 		pipex_error.c \
# 		pipex_envp.c \
# 		pipex_exec.c \
# 		pipex_utils.c \

OBJS	= $(SRCS:.c=.o)

OBJP	= $(SRCS_P:.c=.o)

.SILENT: credits anya norm

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) $(CPPFLAGS) -lreadline $(LDFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Ilibft $(CFLAGS) $(CPPFLAGS) -c $< $(INCS) -o $@

clean:
	@make -C $(LIB_DIR) clean --silent
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) "$(NAME).dSYM"

fclean: clean
	@make -C $(LIB_DIR) fclean --silent

re: fclean all

norm:
ifeq ($(shell $(NORM) | grep -c "Error:"), 0)
	afplay easter_egg/victory.mp3 -v 1 &
else
	afplay easter_egg/fail.mp3 -v 0.7 &
endif
	@$(NORM)

credits:
	@$(MEME)
	@$(MEME3)

anya:
	@$(ANYA3)
	@$(ANYA)
	@$(ANYA2)

sponsor:
	@$(SPONSOR3)
	@$(SPONSOR)
	@sleep 2
	@$(SPONSOR4)
	@sleep 5
	@$(SPONSOR5)
	@sleep 6
	@$(SPONSOR6)
	@sleep 6
	@$(SPONSOR7)

.PHONY: fclean all clean re minishell norm credits anya sponsor
