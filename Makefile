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
TEST_DIR = test/
SUBJ_TEST_DIR = $(TEST_DIR)subject_test/

SOURCES = malloc.c libft_utils.c print_utils.c list_utils.c free.c realloc.c
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)%.o)
HEADER = $(addprefix $(INC_DIR), malloc.h)

all: $(NAME)
	
$(NAME): $(OBJECTS) $(HEADER) Makefile
	$(CC) -shared $(CC_FLAGS) -o $(NAME) $(OBJECTS) -I $(INC_DIR)
	@rm -f $(LIBRARY)
	ln -s $(NAME) $(LIBRARY)

debug: re $(OBJECTS) $(HEADER) Makefile
	$(CC) $(CC_FLAGS) $(SRC_DIR)main.c $(OBJ_DIR)*.o -o $@ -I $(INC_DIR)

s_test: re $(SUBJ_TEST_OBJ)
	$(CC) $(SUBJ_TEST_DIR)test0.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test0 \
		&& ./run.sh /usr/bin/time -v $(SUBJ_TEST_DIR)test0
	$(CC) $(SUBJ_TEST_DIR)test1.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test1 \
		&& ./run.sh /usr/bin/time -v $(SUBJ_TEST_DIR)test1
	$(CC) $(SUBJ_TEST_DIR)test2.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test2 \
		&& ./run.sh /usr/bin/time -v $(SUBJ_TEST_DIR)test2
	$(CC) $(SUBJ_TEST_DIR)test3-1.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test3-1 \
		&& ./run.sh $(SUBJ_TEST_DIR)test3-1
	$(CC) $(SUBJ_TEST_DIR)test3-2.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test3-2 \
		&& ./run.sh $(SUBJ_TEST_DIR)test3-2
	$(CC) $(SUBJ_TEST_DIR)test4.c -I $(INC_DIR) -o $(SUBJ_TEST_DIR)test4 \
		&& ./run.sh $(SUBJ_TEST_DIR)test4

c_test: re $(OBJECTS) $(HEADER) Makefile
	$(CC) $(TEST_DIR)custom_test.c -I $(INC_DIR) -o $(TEST_DIR)custom_test \
		&& ./run.sh $(TEST_DIR)custom_test

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -fPIC -c -o $@ $(CC_FLAGS) $^ -I $(INC_DIR)

clean:
	@rm -rf $(OBJ_DIR) debug

fclean: clean
	@rm -f $(NAME) $(LIBRARY)
	@rm -f $(SUBJ_TEST_OBJ)

re: fclean $(NAME)

.PHONY: all clean fclean re s_test c_test
