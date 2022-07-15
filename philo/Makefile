# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 12:23:24 by yalthaus          #+#    #+#              #
#    Updated: 2022/06/06 11:47:07 by yalthaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################## Exec Name ###################################
NAME	= philo

################################# Compilation ##################################
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
HEADS		= -I$(INC)
LIBS		= -lpthread

##################################### SRC ######################################
SRCDIR 		= ./src/
INC			= ./inc/
BUILDDIR	= ./build/
SRCNAMES	= $(shell ls $(SRCDIR) | grep -E ".+\.c")
SRCS		= $(addprefix $(SRCDIR), $(SRCNAMES))

################################ command + OBJ #################################
RM		= rm -rf
MKDIR	= mkdir -p
MAKE	= make -C
OBJS	= $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

#################################### Action ####################################

all: $(NAME)

$(BUILDDIR):
			@mkdir -p $(BUILDDIR)

$(BUILDDIR)%.o:$(SRCDIR)%.c
			@$(CC) $(CFLAGS) $(HEADS) -o $@ -c $<

$(NAME): $(BUILDDIR) $(LIBFT) $(OBJS)
			$(CC) $(CFLAGS) -o $@ $(OBJS)
clean:
			rm -rf $(BUILDDIR)

fclean: clean
			rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all fclean clean debug re 
