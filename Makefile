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

CC = gcc
CCFLAGS = -g3 # -Wall -Wextra -Werror
LIBFLAGS =

ifeq ($(UNAME_S),Linux)
    CCFLAGS += -pthread
endif

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
TEST_DIR = test/
TEST_OBJ_DIR = test/obj/

SRC = malloc.c calloc.c free.c realloc.c show_alloc_mem.c struct_utils.c
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
INC = $(addprefix $(INC_DIR), malloc.h)

TEST_SRC = test0.c test1.c test2.c test3-1.c test3-2.c test4.c
TEST_OBJ = $(TEST_SRC:%.c=test/obj/%.o)
TEST_EXE = $(addprefix $(TEST_DIR), $(basename $(TEST_SRC)))

CTEST_SRC = test5.c custom_test_1.c custom_test_2.c custom_mutex_test.c
CTEST_OBJ = $(CTEST_SRC:%.c=test/obj/%.o)
CTEST_EXE = $(addprefix $(TEST_DIR), $(basename $(CTEST_SRC)))

all: $(NAME)
	
$(NAME): $(OBJ) $(INC) Makefile
	$(CC) $(CCFLAGS) -fPIC -shared -I $(INC_DIR) -o $(NAME) $(OBJ)
	@rm -f $(LIBRARY)
	ln -s $(NAME) $(LIBRARY)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -fPIC -I $(INC_DIR) -c $^ -o $@

debug: $(OBJ) $(INC) debug.c Makefile
	$(CC) $(CCFLAGS) -I $(INC_DIR) debug.c $(OBJ) -o $@

test: $(NAME) $(TEST_OBJ) $(CTEST_OBJ)

$(CTEST_OBJ): LIBFLAGS := -L. -lft_malloc
$(CTEST_OBJ): CCFLAGS := -Wno-implicit-function-declaration -Wno-unused-result

test/obj/%.o: test/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CCFLAGS) -fpic -c $^ -o $@ -I $(INC_DIR)
	$(CC) $@ -o $(basename $^) $(LIBFLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf debug 
	@rm -rf $(TEST_DIR)$(OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(LIBRARY)
	@rm -f $(TEST_EXE)
	@rm -f $(CTEST_EXE)

re: fclean $(NAME)

.PHONY: all clean fclean re test