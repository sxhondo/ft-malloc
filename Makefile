# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 16:26:49 by sxhondo           #+#    #+#              #
#    Updated: 2021/02/14 15:36:18 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBRARY = libft_malloc.so

CC = cc
CC_FLAGS = -pthread -g3 # -Wall -Wextra -Werror

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
TEST_DIR = test/
TEST_OBJ_DIR = test/obj/

SRC = malloc.c calloc.c free.c realloc.c show_alloc_mem.c struct_utils.c
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
INC = $(addprefix $(INC_DIR), malloc.h)

TEST_SRC = test0.c test1.c test2.c test3-1.c test3-2.c test4.c custom_test_1.c custom_test_2.c mutex_test.c test5.c
			
TEST_OBJ = $(TEST_SRC:%.c=test/obj/%.o)
TEST_EXE = $(addprefix $(TEST_DIR), $(basename $(TEST_SRC)))

all: $(NAME)
	
$(NAME): $(OBJ) $(INC) Makefile
	$(CC) $(CC_FLAGS) -fPIC -shared -I $(INC_DIR) -o $(NAME) $(OBJ)
	@rm -f $(LIBRARY)
	ln -s $(NAME) $(LIBRARY)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -fPIC -I $(INC_DIR) -c $^ -o $@

debug: $(OBJ) $(INC) debug.c Makefile
	$(CC) $(CC_FLAGS) -I $(INC_DIR) debug.c $(OBJ) -o $@

test: $(NAME) $(TEST_OBJ)

test/obj/%.o: test/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CC_FLAGS) -I $(INC_DIR) -fpic -c $^ -o $@
	$(CC) $(CC_FLAGS) -I $(INC_DIR) $@ -o $(basename $^) -L. -lft_malloc

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf debug 
	@rm -rf $(TEST_DIR)$(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(LIBRARY)
	@rm -f $(TEST_EXE)

re: fclean $(NAME)

.PHONY: all clean fclean re test