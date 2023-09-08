# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/09 11:50:09 by ayael-ou          #+#    #+#              #
#    Updated: 2023/07/12 20:57:50 by ayael-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

DIR_SRCS		=	srcs

DIR_OBJS		=	objs

SRCS_NAMES		=	main.c\
					outils.c\
					outils2.c\
					routine2.c\
					routine.c\
					thread.c\

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

HEAD			=	-Iincludes/

CC				=	cc

CFLAGS			=	-g3 -Wall -Werror -Wextra #-fsanitize=thread

MAKEFLAGS		=	--no-print-directory


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[34;5mphilo\033[0m"

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEAD)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean:
	rm -rf ${DIR_OBJS}
	rm -rf ${OBJS}

fclean :	clean
	rm -rf ${LIBFT}
	rm -rf ${NAME}

re:	fclean all

stop:
	rm ${NAME}

.PHONY:		all clean fclean re
