#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaimai <mamaimai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/13 13:50:36 by mamaimai          #+#    #+#              #
#    Updated: 2025/09/20 19:38:32 by mamaimai         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= philo
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -pthread -Iinc

# ----------------- Files -----------------

SRCDIR      = src
OBJDIR      = obj
INCDIR      = inc

SRCS        = actions.c \
              args.c \
              cleanup.c \
              death_print.c \
			  init.c \
			  main.c \
              monitor.c \
			  routine.c \
			  threads.c \
			  utils.c

SRCFILES    = $(addprefix $(SRCDIR)/, $(SRCS))
OBJS        = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

HEADERS     = $(INCDIR)/philo.h

# ----------------- Rules -----------------

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
