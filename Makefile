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

NAME = ft_malloc

CMAKE_DIR = ./cmake-build/

all: $(NAME)
	
$(NAME): $(CMAKE_DIR) $(CMAKE_DIR)Makefile
		$(MAKE) -C $(CMAKE_DIR) $(NAME)

debug: $(CMAKE_DIR) $(CMAKE_DIR)Makefile
		$(MAKE) -C $(CMAKE_DIR) debug --no-print-directory

$(CMAKE_DIR):
	mkdir -p $(CMAKE_DIR)

$(CMAKE_DIR)Makefile:
	cd $(CMAKE_DIR) && cmake ../

clean:
	rm -rf $(CMAKE_DIR)

fclean: clean
	rm -rf debug
	rm -rf $(NAME)

re: fclean all

.PHONY: fdf build debug re fclean clean all
