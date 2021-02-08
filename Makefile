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
CC_FLAGS = -g3 # -Wall -Wextra -Werror

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/

SOURCES = malloc.c realloc.c libft_utils.c print_utils.c list_utils.c free.c main.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)
HEADER = $(addprefix $(INC_DIR), malloc.h)

all: $(NAME)
	
$(NAME): $(OBJECTS) $(HEADER) Makefile
	$(CC) -shared $(CC_FLAGS) -o $(NAME) $(OBJECTS) -I $(INC_DIR)
	@rm -f $(LIBRARY)
	ln -s $(NAME) $(LIBRARY)

debug: re $(OBJECTS) $(HEADER) Makefile
	$(CC) $(CC_FLAGS) $(OBJ_DIR)*.o -o $@ -I $(INC_DIR)
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -fPIC -c -o $@ $(CC_FLAGS) $^ -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR) debug

fclean: clean
	@rm -f $(NAME) $(LIBRARY)

re: fclean $(NAME)

.PHONY: all clean fclean re
