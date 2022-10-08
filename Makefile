# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/09 01:24:09 by nnakarac          #+#    #+#              #
#    Updated: 2022/10/09 02:28:54 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NORM = norminette -R CheckForbiddenSourceHeaderDefine | grep -c 'Error:' || true

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MEME = aplay easter_egg/meme2.mp3 &
	ANYA = aplay easter_egg/anya.mp3 &
else
	MEME = afplay easter_egg/meme2.mp3 -v 0.3 &
	ANYA = afplay easter_egg/anya.mp3 -v 0.7 &
endif

MEME2 = say -v kanya "กำลังรัน นอร์มิเน็ตโตะ"
ANYA2 = say -v kanya "วากุ วากุ"

MEME3 = ./easter_egg/credits.sh
ANYA3 = ./easter_egg/anya.sh

.SILENT: credits anya

ALL: anya

credits:
	@$(MEME)
	@$(NORM)
	@$(MEME2)
	@$(MEME3)

anya:
	@$(ANYA3)
	@$(ANYA)
	@$(ANYA2)

