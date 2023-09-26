# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 21:48:24 by aqueiroz          #+#    #+#              #
#    Updated: 2023/09/25 17:09:53 by aqueiroz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = -I includes

FILES	+=	srcs/main.c \
			srcs/init.c \
			srcs/table.c \
			srcs/philosopher.c \
			srcs/clean.c \
			srcs/simulation.c \
			srcs/routine.c

FILES	+=	utils/utils.c \
			utils/time.c

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror $(INCLUDES) $(FILES) -o $(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

valgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 5 800 200 200

.PHONY: all clean fclean re