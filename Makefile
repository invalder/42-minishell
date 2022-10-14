# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 01:24:09 by nnakarac          #+#    #+#              #
#    Updated: 2022/10/14 21:44:07 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NORM = norminette -R CheckForbiddenSourceHeaderDefine

UNAME = $(shell uname -s)
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
SPONSOR4 = say -v kanya -r 20 "เอ่อ โค้ดนี้ก็ เขียนเองนะครับ" &
SPONSOR5 = say -v kanya -r 10 "แก้  บั๊ก  ครบ    จบในที่เดียว" &
SPONSOR6 = say -v kanya -r 20 "ให้ผ่านเถอะครับ ผมจะได้ไปต่อ" &

MEME3 = ./easter_egg/credits.sh
ANYA3 = ./easter_egg/anya.sh
SPONSOR3 = ./easter_egg/sponsor.sh

NAME = minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= /bin/rm -rf

SRC_DIR	= srcs/
OBJ_DIR	= objs/
INC_DIR	= includes
LIB_DIR = libft/

LIBS	= -L$(LIB_DIR) -lft

INCS	= -I$(INC_DIR)\
		-I$(LIB_DIR)includes \

SRCS	= minishell.c \

OBJS	= $(SRCS:.c=.o)

.SILENT: credits anya norm

all: $(NAME)
	@$(SPONSOR3)
	@$(SPONSOR)
	@sleep 2
	@$(SPONSOR4)
	@sleep 5
	@$(SPONSOR5)
	@sleep 8
	@$(SPONSOR6)
	reset

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	@make -C $(LIB_DIR) --silent
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Ilibft $(CFLAGS) -c $< $(INCS) -o $@

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
	@$(MEME2)
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
	@sleep 8
	@$(SPONSOR6)

.PHONY: fclean all clean re minishell norm credits anya sponsor
