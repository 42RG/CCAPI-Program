# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: #42 <#42@42.fr>                    		+#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#              											#+#    #+#             #
#    											      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = program.exe

SRC = main.c ccapi.c consoleinfo.c functions.c

OBJ = $(SRC:.c=.o)

CC = -O3 -std=c11 -Wall -Werror -Wextra

INCLUDE = includes

all: $(NAME)

$(NAME) : $(SRC)
	gcc $(CC) -c $(SRC) 
	gcc $(CC) -o $(NAME) $(OBJ) -I $(INCLUDE)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all