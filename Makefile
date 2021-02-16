# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <sxhondo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 16:26:49 by sxhondo           #+#    #+#              #
#    Updated: 2021/02/16 09:49:34 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LIBRARY = libft_malloc.so

CC = gcc -fpic
CCFLAGS = -Wall -Wextra -Werror
LIBFLAGS =

INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
TEST_DIR = test/
TEST_OBJ_DIR = test/obj/

SRC = malloc.c calloc.c free.c realloc.c show_alloc_mem.c struct_utils.c
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
INC = $(addprefix $(INC_DIR), malloc.h)

# test files and their rules
TEST_SRC = test0.c test1.c test2.c test3-1.c test3-2.c test4.c
TEST_OBJ = $(TEST_SRC:%.c=test/obj/%.o)
TEST_EXE = $(addprefix $(TEST_DIR), $(basename $(TEST_SRC)))

CTEST_SRC = test5.c custom_test_1.c custom_test_2.c custom_mutex_test.c
CTEST_OBJ = $(CTEST_SRC:%.c=test/obj/%.o)
CTEST_EXE = $(addprefix $(TEST_DIR), $(basename $(CTEST_SRC)))

$(TEST_OBJ): CCFLAGS :=
$(CTEST_OBJ): LIBFLAGS := -L. -lft_malloc -pthread
$(CTEST_OBJ): CCFLAGS := -Wno-implicit-function-declaration -Wno-unused-result

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) -shared -o $(NAME) $(OBJ)
	@rm -f $(LIBRARY)
	ln -s $(NAME) $(LIBRARY)

obj/%.o: src/%.c $(INC) Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -I $(INC_DIR) -c $< -o $@

debug: $(OBJ) $(INC) debug.c Makefile
	$(CC) -I $(INC_DIR) debug.c $(OBJ) -o $@

test: $(NAME) $(TEST_OBJ) $(CTEST_OBJ)

test/obj/%.o: test/%.c
	@mkdir -p $(TEST_OBJ_DIR)
	$(CC) $(CCFLAGS) -c $^ -o $@ -I $(INC_DIR)
	$(CC) $(CCFLAGS) $@ -o $(basename $^) $(LIBFLAGS)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf debug 
	@rm -rf $(TEST_DIR)$(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) $(LIBRARY)
	@rm -rf $(TEST_EXE)
	@rm -rf $(CTEST_EXE)
	@rm -rf $(TEST_DIR)

zip:
	zip -r test.zip $(TEST_DIR)
unzip:
	unzip -n test.zip

re: fclean $(NAME)

.PHONY: all clean fclean re test zip unzip debug