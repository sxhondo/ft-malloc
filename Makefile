# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 16:26:49 by sxhondo           #+#    #+#              #
#    Updated: 2020/03/02 16:26:59 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBRARY = libft_malloc.so

CC = gcc
CC_FLAGS = -O0 -g -W -Wall -Wextra
FLAGS_LIB = -shared

INC_DIR = inc
SRC_DIR = src
OBJ_DIR = obj

SOURCES = malloc.c libft_utils.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	
$(NAME): $(OBJECTS)
		$(CC) $(CC_FLAGS) $(FLAGS_LIB) -o $@ $(OBJECTS)
		@rm -f $(LIBRARY)
		ln -s $(NAME) $(LIBRARY)

debug: main.c $(OBJECTS)
	$(CC) $(CC_FLAGS) main.c -o $@ $(LIBRARY) -I $(INC_DIR)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c -o $@ $(CC_FLAGS) $^ -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(LIBRARY)

re: fclean $(NAME)

.PHONY: all clean fclean re
