# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soahn <soahn@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 00:17:03 by soahn             #+#    #+#              #
#    Updated: 2022/05/01 00:09:50 by soahn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

INCS_DIR		= ./include/
SRCS_DIR		= ./src/

SRC		= main.c action.c dinner.c helper.c init.c

SRCS	= $(addprefix $(SRCS_DIR), $(SRC))
OBJS	= $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) -I $(INCS_DIR) -o $@ -c $?

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I $(INCS_DIR) -lpthread

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

PHONY : all clean fclean re