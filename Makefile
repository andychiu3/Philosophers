# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 12:27:54 by fiftyblue         #+#    #+#              #
#    Updated: 2024/07/07 15:25:06 by fiftyblue        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

SRC			= philo.c check.c init.c routine.c status.c
OBJ			= $(SRC:.c=.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
# -fsanitize=thread

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:	
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
