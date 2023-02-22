# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 11:31:03 by nhorta-g          #+#    #+#              #
#    Updated: 2023/02/22 09:21:58 by nuno             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(SRCS_DIR)/main.c \
			$(SRCS_DIR)/utils.c \
			$(SRCS_DIR)/routine.c \
			$(SRCS_DIR)/death_print.c
SRCS_DIR = ./

OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS:.c=.o))

OBJS_DIR = objs

NAME	= philo

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -pthread -I includes -g  -fsanitize=thread #-fsanitize=address
RM		= rm -rf

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
			mkdir -p $(OBJS_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(OBJS)

re: fclean all
