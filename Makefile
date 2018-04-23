# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nobrien <nobrien@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 19:25:11 by jbrown            #+#    #+#              #
#    Updated: 2018/04/22 10:43:28 by nobrien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
RM = /bin/rm -f

FLAGS = -Wall -Wextra -Werror


# lem_in
FILES = main
INCLUDE = -I ./includes/
SRC_DIR := ./srcs/
OBJ_DIR := ./objs/
CFILES = $(patsubst %, $(SRC_DIR)%.c, $(FILES))
OFILES = $(patsubst %, $(OBJ_DIR)%.o, $(FILES))

# libftprintf lib
LFT_DIR = ./libft/
LFT_LIB = $(addprefix $(LFT_DIR), ft.a)
LFT_INC = -I $(LFT_DIR)/include/
LFT_LINK = -L $(LFT_DIR) -l ft

.PHONY: all clean fclean re

all: $(LFT_LIB) $(NAME)

$(LFT_LIB):
	make -C $(LFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo [INFO] Lem-in Object Files Directory Created

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(FLAGS) $(INCLUDE) $(LFT_INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OFILES)
	@gcc $(FLAGS) $(OFILES) $(LFT_LINK) -o $(NAME)
	@echo [INFO] Lem-in Binary Created

clean:
	@rm -rf $(OBJ_DIR)
	@echo [INFO] Lem-in Object Files Directory Destroyed
	@make -C $(LFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@echo [INFO] Lem-in Binary Destroyed
	@make -C $(LFT_DIR) fclean

re: fclean all
