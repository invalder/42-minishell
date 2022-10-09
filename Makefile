# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 01:24:09 by nnakarac          #+#    #+#              #
#    Updated: 2022/10/09 12:41:14 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NORM = norminette -R CheckForbiddenSourceHeaderDefine
NORMCNT = $(shell cat ./norm.result | grep -c 'Error:')

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

MEME2 = say -v kanya "กำลังรัน นอร์มิเน็ตโตะ"
ANYA2 = say -v kanya "วากุ วากุ"
SPONSOR2 = say -v kanya "เอ่อ โค้ดนี้ก็ สปอนเซอร์นะครับ แก้ เขียน ครบ จบในที่เดียว ยังไงก็ ให้ผ่านนะครับ เค้าจะได้จ้างผมต่อ"

MEME3 = ./easter_egg/credits.sh
ANYA3 = ./easter_egg/anya.sh
SPONSOR3 = ./easter_egg/sponsor.sh

NAME = minishell

.SILENT: credits anya norm

ALL: $(NAME)
	@$(TIEIN)
	@$(SPONSOR)
	@$(SPONSOR3)

$(NAME):

norm:
ifeq ($(shell $(NORM) | grep -c "Error:"), 0)
	afplay easter_egg/victory.mp3 -v 1 &
else
	afplay easter_egg/fail.mp3 -v 0.7 &
endif
	@$(NORM)

credits:
	@$(MEME)
	@$(NORM)
	@$(MEME2)
	@$(MEME3)

anya:
	@$(ANYA3)
	@$(ANYA)
	@$(ANYA2)

sponsor:
	@$(SPONSOR3)
	@$(SPONSOR)
	@$(SPONSOR2)

