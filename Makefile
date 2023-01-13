# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 01:24:09 by nnakarac          #+#    #+#              #
#    Updated: 2023/01/08 16:03:58 by nnakarac         ###   ########.fr        #
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
NAMET = testshell
NAMEM = mini2
NAMEMM = minimini

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

ifeq ($(ARCH), arm64)
	LDFLAGS	= -L${HOMEBREW_PREFIX}/opt/readline/lib
	CPPFLAGS	= -I${HOMEBREW_PREFIX}/opt/readline/include
else
	LDFLAGS	= -L/usr/local/opt/readline/lib
	CPPFLAGS	= -I/usr/local/opt/readline/include
endif

RM		= /bin/rm -rf

SRC_DIR	= srcs/
OBJ_DIR	= objs/
INC_DIR	= includes
LIB_DIR = libft/

LIBS	= -L$(LIB_DIR) -lft

INCS	= -I$(INC_DIR)\
		-I$(LIB_DIR)includes \

SRCS	= minishell.c \

SRCS_P	= pipex.c \
		pipex_error.c \
		pipex_envp.c \
		pipex_exec.c \
		pipex_utils.c \

SRCS_T	= test_sh.c \
		test_util1.c \
		test_util2.c \
		test_dealloc.c \
		test_err.c \
		test_meta.c \
		test_signal.c \
		ft_realloc.c \

SRCS_M	= mini2_sh.c \
		mini2_signal.c \
		mini2_util1.c \
		mini2_util2.c \
		mini2_dealloc.c \
		mini2_err.c \
		mini2_meta.c \
		mini2_terminal.c \
		mini2_tokenizer.c \
		mini2_realloc.c \

SRCS_MM = ms_cmd_split.c \
		ms_environ.c \
		ms_envp.c \
		ms_exec.c \
		ms_execve.c \
		ms_implement.c \
		ms_parse.c \
		ms_split.c \
		test.c \

OBJS	= $(SRCS:.c=.o)

OBJP	= $(SRCS_P:.c=.o)

OBJT	= $(SRCS_T:.c=.o)

OBJM	= $(SRCS_M:.c=.o)

OBJMM	= $(SRCS_MM:.c=.o)

.SILENT: credits anya norm

all: $(NAMEMM)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) -o $(NAME)

$(NAMEP): $(addprefix $(OBJ_DIR),$(OBJP))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJP)) $(LIBS) -o $(NAMEP)

$(NAMET): $(addprefix $(OBJ_DIR),$(OBJT))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) $(addprefix $(OBJ_DIR),$(OBJT)) $(LIBS) -o $(NAMET)

$(NAMEM): $(addprefix $(OBJ_DIR),$(OBJM))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) $(addprefix $(OBJ_DIR),$(OBJM)) $(LIBS) -o $(NAMEM)

$(NAMEMM): $(addprefix $(OBJ_DIR),$(OBJMM))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) $(addprefix $(OBJ_DIR),$(OBJMM)) $(LIBS) -o $(NAMEMM)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Ilibft $(CFLAGS) $(CPPFLAGS) -c $< $(INCS) -o $@

clean:
	@make -C $(LIB_DIR) clean --silent
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@$(RM) $(NAMEP)
	@$(RM) $(NAMET)
	@$(RM) $(NAMEM)
	@$(RM) $(NAMEMM)
	@$(RM) "$(NAME).dSYM"
	@$(RM) "$(NAMEP).dSYM"
	@$(RM) "$(NAMET).dSYM"
	@$(RM) "$(NAMEM).dSYM"
	@$(RM) "$(NAMEMM).dSYM"

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

.PHONY: fclean all clean re minishell norm credits anya sponsor mini2
